#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> //  Both of these are potentially useless
#include <sys/stat.h>  //
#include "structs.h"
#include "img.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	// Transmission statements
	int piped[2];
	pid_t pid;

	// Image reading statements
	int fileDescr, dataStream, i = 0, j = 0;
	ssize_t pngFile;
	char str[128], fileName[255], data[4097];
	int imgNumber, threshold, skipAnalysis;
	Img imageFile;

	

	// Read args
	read(READ, str, 128);
	sscanf(str, "%d %d %d", &imgNumber, &threshold, &skipAnalysis);

	// Read kernel
	read(READ, str, 128);

	// Transmission start.
	pipe(piped);
	pid = fork();

	// Child section
	if (pid == 0)
	{
		close(piped[WRITE]);
		dup2(piped[READ], STDIN_FILENO);

		char *args[] = {(char *)"imageConvolution", NULL};
		execvp("./imageConvolution", args);
		perror("exec failed");
		return 1;
	}

	else
	{
		close(piped[READ]);

		// Send kernel.
		write(piped[WRITE], str, 128);

		// Send global args.
		sprintf(str, "%d %d %d", imgNumber, threshold, skipAnalysis);
		write(piped[WRITE], str, 128);
		
	}


	sprintf(fileName,"imagen_%d.png", imgNumber);//Generate the name of the file to be opened
	printf("Searching file '%s'....\n", fileName);
	fileDescr = open(fileName, O_RDONLY);
	if(fileDescr < 0)
	{
		printf("File '%s' not found\nClosing program...\n", fileName);
		exit(0);
	}
	else
	{
		imageFile = startLecture(fileName);
		printf("\n");
	}

	close(fileDescr);
	//Function number 1 goes here

	// Send image.

	sprintf(str, "%u %u %u %u", imageFile.width, imageFile.height, imageFile.dataSize, imageFile.bitDepth);
	write(piped[WRITE], str, 128);

	while (i < (imageFile.width * imageFile.height * 3))
	{	
		sprintf(str,"%c%c%c", imageFile.data[i], imageFile.data[i+1], imageFile.data[i+2]);
		write(piped[WRITE], str, 128);
		i = i + 3;
	}
	
	printf("Image 'imagen_%d' reading process ended successfully\n", imgNumber);
		


	return 0;
}
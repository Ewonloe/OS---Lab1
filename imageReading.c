#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <png.h>
#include <sys/types.h> //  Both of these are potentially useless
#include <sys/stat.h>  //
#include "structs.h"
#include "img.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	int fileDescr, dataStream, i = 0, j = 0;
	ssize_t pngFile;
	char str[128], fileName[255], data[4097];
	int imgNumber, threshold, skipAnalysis;
	Img imageFile;

	read(READ, str, 128);

	printf("Input: %s\n", str);
	sscanf(str, "%d %d %d", &imgNumber, &threshold, &skipAnalysis);
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

	read(READ, str, 128);
	close(fileDescr);
	//Function number 1 goes here
	printf("Kernel %s\n", str);
	printf("Image 'imagen_%d' reading process ended successfully\n", imgNumber);

	return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <png.h>
#include <sys/types.h> //  Both of these are potentially useless
#include <sys/stat.h>  //  

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	int fileDescr, dataStream, i = 0, j = 0;
	ssize_t pngFile;
	char str[128], fileName[255], data[4097];
	int imgNumber, threshold, skipAnalysis;
	//PNG files structures
	png_image image;

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
		printf("File found!\n");
		printf("This image reads: %d in decimal\n", fileDescr);
		while(dataStream = read(fileDescr, data, 4096) > 0)
		{
			for(j; j != dataStream; j++)
			{
				printf("%8x ", data[j]);
				if(i % 16 == 0)
				{
					printf("\n");
				}
				i++;
			}
		}
	printf("\n");
	}

	read(READ, str, 128);
	close(fileDescr);
	//Function number 1 goes here
	printf("Kernel %s\n", str);
	printf("Image 'imagen_%d' reading process ended successfully\n", imgNumber);

	return 1;
}
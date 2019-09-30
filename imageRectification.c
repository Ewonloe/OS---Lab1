#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "img.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	// Transmission statements
	int piped[2];
	pid_t pid;

	// Image rectification statements
	int i, j;
	char str[128];
	int imgNumber, threshold, skipAnalysis;
	Img imageFile;
	float **imgMatrix = (float**) malloc(sizeof(float*) * imageFile.height);
	for(i = 0; i < imageFile.width; i++)
	{
		imgMatrix[i] = (float*) malloc(sizeof(float) * imageFile.width);
	}

	imageFile.image2 = (float**)malloc(sizeof(float*) * imageFile.height);
	for(i = 0; i < imageFile.width; i++)
	{
		imageFile.image2[i] = (float*) malloc(sizeof(float) * imageFile.width);
	}

	// Read global args.
	read(READ, str, 128);
	sscanf(str, "%d %d %d", &imgNumber, &threshold, &skipAnalysis);

	// Read image params.
	read(READ, str, 128);
	sscanf(str, "%u %u %u", &imageFile.width, &imageFile.height, &imageFile.dataSize);

	imageFile.data = (char*) malloc(sizeof(char) * imageFile.dataSize);

	i = 0;
	/*
	while (i < (imageFile.dataSize))
	{	
		read(READ, str, 128);
		sscanf(str,"%c", &imageFile.data[i]);
		i = i + 1;
	}
	*/
	for(i = 0; i < imageFile.height; i++)
	{
		for(j = 0; j < imageFile.width; j++)
		{
			read(READ, str, 128);
			sscanf(str, "%lf", &imageFile.image2[i][j]);
		}
	}
	rectification(&imageFile);

	printf("Data = %d\n", imageFile.height);

	return 0;
}
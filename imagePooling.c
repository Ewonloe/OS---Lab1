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

	// Image pooling statements
	int i, j;
	char str[128];
	int tempN = 0;
	int imgNumber, threshold, skipAnalysis;
	Img imageFile;


	// Read global args.
	read(READ, str, 128);
	sscanf(str, "%d %d %d", &imgNumber, &threshold, &skipAnalysis);



	while(tempN < imgNumber)
	{
		// Read image params.
		read(READ, str, 128);
		sscanf(str, "%u %u %u", &imageFile.width, &imageFile.height, &imageFile.dataSize);

		imageFile.image2 = (float**)malloc(sizeof(float*) * imageFile.height);
		for(i = 0; i < imageFile.height; i++)
		{
			imageFile.image2[i] = (float*) malloc(sizeof(float) * imageFile.width);
		}

		// Read image.
		for(i = 0; i < imageFile.height; i++)
		{
			for(j = 0; j < imageFile.width; j++)
			{
				read(READ, str, 128);
				sscanf(str, "%f", &imageFile.image2[i][j]);
			}
		}

		tempN++;
	}

	printf("Pooling Finished\n");

	return 0;
}
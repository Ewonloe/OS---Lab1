#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	// Transmission statements
	int piped[2];
	pid_t pid;

	// image convolving statements
	char str[128];
	double kernel[3][3];
	int imgNumber, threshold, skipAnalysis;
	Img imageFile;

	// Read kernel;
	read(READ, str, 128);
	sscanf(str, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &kernel[0][0], &kernel[0][1], &kernel[0][2],
												&kernel[1][0], &kernel[1][1], &kernel[1][2],
												&kernel[2][0], &kernel[2][1], &kernel[2][2]);


	// Read global args.
	read(READ, str, 128);
	sscanf(str, "%d %d %d", &imgNumber, &threshold, &skipAnalysis);



	// Read image params.
	read(READ, str, 128);
	printf("Parameters: %s\n", str);
	sscanf(str, "%u %u %u %u", &imageFile.width, &imageFile.height, &imageFile.dataSize, &imageFile.bitDepth);


	// Read image pixels.

	read(READ, str, 128);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{

	int opt;
	int flags = 0;

	int imgNumber;        // Number of images received.
	int binaryThreshold;  // Binarization threshold.
	int clssThreshold;    // Classification threshold.
	int skipAnalysis = 0;    // Boolean. 1 for showing 'nearly black' analysis, 0 for skipping it.

	while ((opt = getopt(argc, argv, ":c:u:n:b")) != -1)
	{
		switch(opt)
		{
			// Number of images flag.
			case 'c':
				if ((imgNumber = validateCFlag(optarg)) == -1)
				{
					printf("Invalid input in: Number of images (-c)\n");
					exit(1);
				}

				flags++;
				break;

			// Binarization threshold flag.
			case 'u':
				if ((binaryThreshold = validateUFlag(optarg)) == -1)
				{
					printf("Invalid input in: Binarization threshold (-u)\n");
					exit(1);
				}

				flags++;
				break;

			// Classification threshold flag.
			case 'n':
				if ((clssThreshold = validateNFlag(optarg)) == -1)
				{
					printf("Invalid input in: Classification threshold (-n)\n");
					exit(1);
				}

				flags++;
				break;

			// Skipping analysis flag.
			case 'b':
				skipAnalysis = 1;
				break;

			// Missing argument.
			case ':':
				printf("Option needs an argument\n");
				exit(1);

			// Unknown flag.
			case '?':
				printf("Unknown option: %c\n", optopt);
				exit(1);
		}
	}

	if (flags != 3)
	{
		printf("Incorrect number of arguments. Terminating...\n");
		exit(1);
	}

	printf("Success\n");
}
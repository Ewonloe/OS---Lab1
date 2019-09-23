#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	int opt;
	int flags = 0;

	int piped[2];
	pid_t pid;

	int imgNumber;        // Number of images received.
	double kernel[3][3];
	int clssThreshold;    // Classification threshold.
	int skipAnalysis = 0;    // Boolean. 1 for showing 'nearly black' analysis, 0 for skipping it.

	while ((opt = getopt(argc, argv, ":c:m:n:b")) != -1)
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

			// Kernel.
			case 'm':
				
				readKernelFile(optarg, kernel);

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


	pipe(piped);
	pid = fork();

	// Child section
	if(pid == 0)
	{
		close(piped[WRITE]);
		char *args[] = {(char *) "imageReading", NULL};
		execvp("imageReading", args);
		perror("exec failed");
		return 1;
	}

	else
	{
		close(piped[READ]);
		write(piped[WRITE], "Test string", 128);
	}

	return 0;
}
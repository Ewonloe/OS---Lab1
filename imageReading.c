#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	char str[128];
	read(0, str, 128);
	printf("%s\n", str);

	printf("Image reading process ended successfully\n");

	return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"


// Input: char* (string) str: argument of the -c flag.
// Function: Validates the input and converts it to int.
// Output: int: -1 if input is not valid, int converted str if valid.
int validateCFlag(char* str)
{
	if (isNumeric(str) == -1)
		return -1;

	int num = atoi(str);

	if (num == 0)
		return -1;

	return num;
}

// Input: char* (string) str: argument of the -u flag.
// Function: Validates the input and converts it to int.
// Output: int: -1 if input is not valid, int converted str if valid.
int validateUFlag(char* str)
{
	if (isNumeric(str) == -1)
		return -1;

	int num = atoi(str);

	if ((num < 0) || (num > 255))
		return -1;

	return num;
}

// Input: char* (string) str: argument of the -u flag.
// Function: Validates the input and converts it to int.
// Output: int: -1 if input is not valid, int converted str if valid.
int validateNFlag(char* str)
{
	if (isNumeric(str) == -1)
		return -1;

	int num = atoi(str);

	if ((num < 0) || (num > 100))
		return -1;

	return num;
}

// Input: char* (string) str: argument of the -u flag.
// Function: Checks if the input is a number.
// Output: int: -1 if input is not a number, 1 if number.
int isNumeric(char* str)
{
	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		if (isdigit(str[i]) == 0)
			return -1;
	}

	return 1;
}
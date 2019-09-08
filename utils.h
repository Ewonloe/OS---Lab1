#ifndef _utils_h
#define _utils_h
 
 
// Input: char* (string) str: argument of the -u flag.
// Function: Checks if the input is a number.
// Output: int: -1 if input is not a number, 1 if number.
int isNumeric(char* str);

// Input: char* (string) str: argument of the -c flag.
// Function: Validates the input and converts it to int.
// Output: int: -1 if input is not valid, int converted str if valid.
int validateCFlag(char* str);

// Input: char* (string) str: argument of the -u flag.
// Function: Validates the input and converts it to int.
// Output: int: -1 if input is not valid, int converted str if valid.
int validateUFlag(char* str);

// Input: char* (string) str: argument of the -u flag.
// Function: Validates the input and converts it to int.
// Output: int: -1 if input is not valid, int converted str if valid.
int validateNFlag(char* str);

 
#endif
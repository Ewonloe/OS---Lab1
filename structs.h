//Img struct
#ifndef _structs_h
#define _structs_h
typedef struct
{
    unsigned int width;
    unsigned int height;
    unsigned int dataSize;
    unsigned char *data;
    unsigned int bitDepth;
}Img;
#endif
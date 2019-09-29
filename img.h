#ifndef _img_h
#define _img_h

int powOf(int a, int b);

unsigned int hexToDec(unsigned char hex[], int length);

void stringToHex(unsigned char* str, unsigned int realSize);

void getDimensions(char *buffer, Img *imgFile);

void getData(unsigned char* buffer, Img *imgFile, int lenght);

char* readChunk(int fd, Img *imgFile);

void readPNG(int fd);

int startLecture(char* fileName);

#endif

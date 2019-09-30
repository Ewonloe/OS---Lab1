#ifndef _img_h
#define _img_h

int powOf(int a, int b);

unsigned int hexToDec(unsigned char hex[], int length);

void stringToHex(unsigned char* str, unsigned int realSize);

void getDimensions(char *buffer, Img *imgFile);

void getData(unsigned char* buffer, Img *imgFile, int lenght);

char* readChunk(int fd, Img *imgFile);

Img readPNG(int fd);

Img startLecture(char* fileName);

void convolution(float **imgMatrix, float **imgMatrix2, double kernel[3][3], Img *imgFile);

void setImage(float **imgMatrix, Img *imgFile);

void printMat(float** imgMatr, Img *imgFile);

void rectification(float **imgMatrix, Img *imgFile);

#endif

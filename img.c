//Image test
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "img.h"

void stringToHex(unsigned char* str, unsigned int realSize);

//Function
int powOf(int a, int b)
{
    int i, result = 1;
    if(b == 0)
    {
        return 1;
    }
    else if(b > 0)
    {
        for(i = 0; i < b; i++)
        {
            result *= a;
        }
    }
    else
    {
        for(i = b; i < 0; i++)
        {
            result /= a;
        }
    }
    
    return result;
}

unsigned int hexToDec(unsigned char hex[], int length)
{
    int  i, result = 0, exp = 0;
    unsigned int tempHex;
    result = 0;
    exp = length - 1;
    for(i = 0; i < length; i++)
    {
        tempHex = (int)hex[i];
        result += tempHex * powOf(256, exp);
        exp -= 1;
    }
    return result;
}

void setImage(float **imgMatrix, Img *imgFile)
{
    int i, j, pos = 0;
    char pixel[3];
    for(i = 0; i < imgFile->height; i++)
    {
        for(j = 0; j < imgFile->width; j++)
        {
            pixel[0] = imgFile->data[pos];
            pixel[1] = imgFile->data[pos + 1];
            pixel[2] = imgFile->data[pos + 2];
            imgMatrix[i][j] = (float) hexToDec(pixel, 3);
            printf("its %lf and\n", imgMatrix[i][j]);
            stringToHex(pixel, 3);
            pos += 3;
        }
    }
}

void convolution(float **imgMatrix, float **imgMatrix2, double kernel[3][3], Img *imgFile)
{
    int i, j;    
    for(i = 0; i < imgFile->height; i++)
    {
        for(j = 0; j < imgFile->width; j++)
        {
            if(i == 0 || j == 0)
            {
                imgMatrix2[i][j] = 0;
            }
            else
            {
                imgMatrix2[i][j] = (imgMatrix[i-1][j-1] * kernel[0][0] + imgMatrix[i-1][j] * kernel[0][1] + imgMatrix[i-1][j+1] * kernel[0][2]
                                  + imgMatrix[i][j-1] * kernel[1][0] + imgMatrix[i][j] * kernel[1][1] + imgMatrix[i+1][j] * kernel[1][2]
                                  + imgMatrix[i+1][j-1] * kernel[2][0] + imgMatrix[i+1][j] * kernel[2][1] + imgMatrix[i+1][j+1] * kernel[2][2]
                                   ) / 9;
            }
        }
    }
}

void printMat(float** imgMatr, Img *imgFile)
{
    int i,j;
    for(i = 0; i < imgFile->height; i++)
    {
        for(j = 0; j < imgFile->width; j++)
        {
            printf("%lf ", imgMatr[i][j]);
        }
        printf("\n");
    }
}

void stringToHex(unsigned char* str, unsigned int realSize)
{
    int i;
    printf("| ");
    for(i = 0; i < realSize; i++)
    {        
        printf("%x ", (unsigned int)str[i]);
        if(i % 16 == 0 && i != 0) printf("\n  ");
    }
    printf("|\n");
}

void getDimensions(char *buffer, Img *imgFile)
{
    unsigned char strWidth[4], strHeight[4], bitDepth[1], cType[1], cMethod[1];
    int i;
    for(i = 0; i < 4; i++)
    {
        strWidth[i] = buffer[i];
        strHeight[i] = buffer[i + 4];           
    }
    bitDepth[0] = buffer[8];
    cType[0] = buffer[9];
    cMethod[0] = buffer[10];
    imgFile->width = hexToDec(strWidth, 4);
    imgFile->height = hexToDec(strHeight, 4);
    imgFile->bitDepth = hexToDec(bitDepth, 1);
    imgFile->colorType = hexToDec(cType, 1);
    imgFile->cMethod = hexToDec(cMethod, 1);
}

void getData(unsigned char* buffer, Img *imgFile, int lenght)
{
    int i;
    imgFile->data = (char*) malloc(sizeof(char) * lenght);
    for(i = 0; i < lenght; i++)
    {
        imgFile->data[i] = buffer[i];
    }
    imgFile->dataSize = lenght;
    //stringToHex(buffer, lenght);
    //stringToHex(imgFile->data, lenght);
}

char* readChunk(int fd, Img *imgFile)
{
    int size, lenght;
    unsigned char lenStr[10], *chunkName, *buffer,  crc[4];

    chunkName = (char*) malloc(sizeof(char) * 4);
    size = read(fd, lenStr, 4);//First, get the chunk data's lenght
    lenght = hexToDec(lenStr, 4);
    
    if((unsigned int)lenStr[0] == 0 && (unsigned int)lenStr[1] == 0 && (unsigned int)lenStr[2] == 0 && (unsigned int)lenStr[3] == 0)
    {
        strcpy(chunkName, "IEND");
        return chunkName;
    }

    size = read(fd, chunkName, 4);//Get the chunk name

    if(lenght > 0)
    {
        buffer = (char*) malloc(sizeof(char) * (lenght));
        size = read(fd, buffer, lenght);//Store chunk data

        size = read(fd, crc, 4);//Get crc
        printf("\n");
        if(strcmp(chunkName, "IHDR") == 0)
        {
            getDimensions(buffer, imgFile);
        }
        if(strcmp(chunkName, "IDAT") == 0)
        {
            getData(buffer, imgFile, lenght);
        }
        free(buffer);
    }
    
    return chunkName;
}

Img readPNG(int fd)
{
    unsigned char *chunkName = (unsigned char*) malloc(sizeof(char) * 4);
    unsigned int width, height;
    Img imgFile;
    
    imgFile.dataSize = 0;
    
    while(strcmp(chunkName, "IEND") != 0)
    {
        chunkName = readChunk(fd, &imgFile);
        if(strcmp(chunkName, "IEND") == 0)
        {
            break;
        }
    }
    free(chunkName);
    return imgFile;
}

Img startLecture(char *filename)
{
    int fd, i = 0;
    char buffer[256];
    int size;
    Img imageFile;

    fd = open(filename, O_RDONLY);

    //First 8 bytes of header
    for(i; i < 8; i++)
    {
        size = read(fd, buffer, 1);
        buffer[0] = 0;
    }

    imageFile = readPNG(fd);
    close(fd);
    
    return imageFile;
}


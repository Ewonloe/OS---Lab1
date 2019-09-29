//Image test
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <png.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

#define BYTES 8
#define L2 100

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

int hexToDec(char hex[], int length)
{
    int  i, result = 0, exp = 0, tempHex;
    for(i = length - 1; i >= 0 && hex[i] != '\0'; i--)
    {
        tempHex = (int)hex[i];
        result += tempHex * powOf(256, exp);
        exp++;
    }
    return result;
}

void stringToHex(unsigned char* str, unsigned int realSize)
{
    int i;
    printf("The real size is %x\n", realSize);
    printf("| ");
    for(i = 0; i < realSize; i++)
    {        
        printf("%x ", (unsigned int)str[i]);
        if(i % 16 == 0 && i != 0) printf("\n  ");
    }
    printf("|\n");
}

char* readChunk(int fd)
{
    int size, lenght;
    char lenStr[4], *chunkName, *buffer,  crc[4];
    chunkName = (char*) malloc(sizeof(char) * 4);
    size = read(fd, lenStr, 4);//First, get the chunk data's lenght
    lenght = hexToDec(lenStr, 4);
    //printf("\nlenStr = %d\n", size);

    size = read(fd, chunkName, 4);//Get the chunk name

    buffer = (char*) malloc(sizeof(char) * (lenght));
    size = read(fd, buffer, lenght);//Store chunk data
    //if(strcmp(chunkName, "tEXt") == 0) printf("|Size of tEXt data is %d\n|And data is %s\n", size, buffer);

    size = read(fd, crc, 4);//Get crc
    
    printf("|Lenght = %d\n|Chunk = %s\n|crc = %s\n+-------------\n", lenght, chunkName, crc);
    
    printf("DATA\n");
    stringToHex(buffer, lenght);
    printf("\n");
    /*
    if(strcmp(chunkName, "IDAT") == 0)
    {
        printf("HERE COMES IDAAAAAT\nlenght = %d", lenght);
        stringToHex(buffer, lenght);
    }
    */
    free(buffer);
    return chunkName;
}

void readPNG(int fd)
{
    unsigned char *chunkName = (unsigned char*) malloc(sizeof(char) * 4);
    
    while(strcmp(chunkName, "IDAT") != 0)
    {
        printf("+-------------\n");
        chunkName = readChunk(fd);
    }
    printf("IDAT!\n");
    free(chunkName);
}

int main(int argc, char* argv[])
{
    int fd, i = 0;
    char buffer[256], buff2[256];
    int size;

    fd = open("imagen_1.png", O_RDONLY);
    if(fd == -1)
    {
        printf("File not found!\n");
        exit(0);
    }
    
    printf("File found, now it can be read\n");

    size = read(fd, buffer, 8); //4 Extracts 'PNG' as a string

    //printf("Size is %d bytes\nFormat is: %s\n", size, buffer);
    close(fd);

    fd = open("imagen_1.png", O_RDONLY);
    for(i; i < BYTES; i++)
    {
        size = read(fd, buff2, 1);
        //printf("Byte #%d is: %s\n", i + 1, buff2);
        buff2[0] = 0;
    }

    readPNG(fd);

    /*
    readChunk(fd);
    readChunk(fd);
    readChunk(fd);
    readChunk(fd);
    readChunk(fd);
    readChunk(fd);
    */

    /*

    //Extract width and height of the png file
    char width[4], length[4], nothing[4], buff3[256], dummy[33];
    int realWidth, realHeight, dumby;
    size = read(fd, nothing, 4);//Size of IHDR chunk
    printf("Size of IHDR data: %d\n", hexToDec(nothing, 4));
    size = read(fd, width, 4);//IHDR
    size = read(fd, length, 4);//Actual width
    int j = 0;
    printf("PNG file actual chunk is %s\n", width);
    //printf("Supposedly, width and height are %s and %s\n", width, length);
    //printf("It's numbers are %d %d %d %d\n", (int)width[0], (int)width[1], (int)width[2], (int)width[3]);//Decimal
    //printf("It's numbers are %x %x %x %x\n", (int)width[0], (int)width[1], (int)width[2], (int)width[3]);//Hex
    //printf("It's numbers are %x %x %x %x\n", (int)length[0], (int)length[1], (int)length[2], (int)length[3]);//Hex
    //printf("It's numbers are %d %d %d %d\n", (int)length[0], (int)length[1], (int)length[2], (int)length[3]);//Decimal
    printf("Width %d\n", hexToDec(length, 4));
    size = read(fd, buff3, 4);//Actual height
    printf("Height %d\n", hexToDec(buff3, 4));
    buff3[0] = 0;
    size = read(fd, buff3, 1);//Bit depth?
    printf("Bit depth = %d\n", hexToDec(buff3, 1));
    buff3[0] = 0;
    size = read(fd, buff3, 1);//Bit depth
    printf("Color type = %d\n", hexToDec(buff3, 1));//Debe ser 6 para tener Alpha, Red, Green, Blue
    buff3[0] = 0;
    size = read(fd, buff3, 1);//Bit depth
    printf("Compress method = %d\n", hexToDec(buff3, 1));//Debe ser 6 para tener Alpha, Red, Green, Blue

    
    /*
    for(i = 0; i < 2; i++)
    {
        size = read(fd, buff3, 4);
        printf("Chunk #%d: Next 4 byte chunk: %s\n", i + 1, buff3);

        buff3[0] = 0;
    }
    printf("\n");
    for(i = 0; i < L2; i++)
    {
        size = read(fd, buff3, 4);
        printf("Chunk #%d: Next 4 byte chunk: %s\n", i + 1, buff3);

        buff3[0] = 0;
    }
    */
   
    close(fd);
    
    return 0;
}
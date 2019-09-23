main: main.c utils.o imageReading.c imageReading
	gcc -o main main.c utils.o

imageReading: imageReading.c
	gcc -o imageReading imageReading.c
utils.o: utils.c utils.h
	gcc -c utils.c
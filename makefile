main: main.c utils.o imageReading.c imageReading
	gcc -o main main.c utils.o

imageReading: imageReading.c img.o imageConvolution
	gcc -o imageReading imageReading.c img.o

imageConvolution: imageConvolution.c
	gcc -o imageConvolution imageConvolution.c

utils.o: utils.c utils.h
	gcc -c utils.c

img.o: img.c img.h
	gcc -c img.c
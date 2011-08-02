poi: threefish.o ubi.o bitbyteoperations.o main.o
	gcc -o poi -lm threefish.o main.o ubi.o bitbyteoperations.o
threefish.o: threefish.c threefish.h
	gcc -O2 -I$(HOME)/include -c -lm threefish.c
main.o: main.c threefish.h ubi.h bitbyteoperations.h
	gcc -O2 -I$(HOME)/include -c main.c
ubi.o: ubi.c threefish.h ubi.h bitbyteoperations.h
	gcc -O2 -I$(HOME)/include -c ubi.c
bitbyteoperations.o: bitbyteoperations.c bitbyteoperations.h
	gcc -O2 -I$(HOME)/include -c bitbyteoperations.c  


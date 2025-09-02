decoder: main.o decoder.o
	gcc -o decoder main.o decoder.o

main.o: main.c
	gcc -c -Wall main.c

decoder.o: decoder.c decoder.h
	gcc -c -Wall decoder.c


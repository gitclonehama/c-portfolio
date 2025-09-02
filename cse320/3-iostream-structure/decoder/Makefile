CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = decoder
OBJS = main.o stack.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c stack.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f $(TARGET) $(OBJS)
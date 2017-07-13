CC = avr-gcc
DEPS = linuxgpio.h bitbang.h
OBJ = linuxgpio.o bitbang.o
SRC = linuxgpio.c bitbang.c
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

format: $(SRC)
	astyle $@ --style=bsd --indent=tab

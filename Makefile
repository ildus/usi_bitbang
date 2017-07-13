CC = gcc
DEPS = linuxgpio.h bitbang.h
OBJ = linuxgpio.o bitbang.o controller.o
SRC = linuxgpio.c bitbang.c controller.c
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

controller: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

format: $(SRC) $(DEPS)
	astyle $^ --style=bsd --indent=tab

clean:
	rm -f *.o *~ *.c.orig *.orig

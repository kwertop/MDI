CC=gcc
CFLAGS=-I.
DEPS = mdi.h
OBJ = main.o mdi.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mdi: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -O2

LIBNAMES = matrix queue
LIBFILES = $(addprefix libs/, $(LIBNAMES))
HEADERS = $(addsuffix .h, $(LIBFILES))
SOURCES = $(addsuffix .c, $(LIBFILES))

EP1: EP1.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) EP1.c $(SOURCES) -o $@

clean:
	rm -rf EP1 libs/*.gch *.o

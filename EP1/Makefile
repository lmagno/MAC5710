CC = gcc
CFLAGS = -g -Wall

LIBNAMES = input graph stack queue
LIBFILES = $(addprefix libs/, $(LIBNAMES))
HEADERS = $(addsuffix .h, $(LIBFILES))
SOURCES = $(addsuffix .c, $(LIBFILES))

EP1: EP1.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) EP1.c $(SOURCES) -o $@

test: test.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) test.c $(SOURCES) -o $@

clean:
	rm -rf EP1 test libs/*.gch

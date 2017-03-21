CC = gcc
CFLAGS = -g -Wall

LIBS = matrix stack queue
HEADERS = $(addsuffix .h, $(LIBS))
SOURCES = $(addsuffix .c, $(LIBS))

EP1: EP1.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) EP1.c $(SOURCES) -o $@

test: test.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) test.c $(SOURCES) -o $@

clean:
	rm -rf EP1 test *.gch

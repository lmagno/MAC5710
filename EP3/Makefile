CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -O2

LIBNAMES = queue
# LIBFILES = $(addprefix libs/, $(LIBNAMES))
LIBFILES = $(LIBNAMES)
HEADERS = $(addsuffix .h, $(LIBFILES))
SOURCES = $(addsuffix .c, $(LIBFILES))

EP3: EP3.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) EP3.c $(SOURCES) -o $@


clean:
	rm -rf EP3 \
	*.o

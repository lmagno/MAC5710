CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -O2

LIBNAMES = bst queue
# LIBFILES = $(addprefix libs/, $(LIBNAMES))
LIBFILES = $(LIBNAMES)
HEADERS = $(addsuffix .h, $(LIBFILES))
SOURCES = $(addsuffix .c, $(LIBFILES))

EP2: EP2.c $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) EP2.c $(SOURCES) -o $@

gen: gen.c gen.h $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) gen.c $(SOURCES) -o $@

clean:
	rm -rf EP2 gen \
	*.aux \
	*.fdb_latexmk \
	*.fls \
	*.log \
	*.synctex.gz \
	*.gch \
	*.o

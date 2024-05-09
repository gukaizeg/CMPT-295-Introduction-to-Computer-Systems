IDIR =./include
CC=gcc
CFLAGS= -ggdb -I$(IDIR)

ODIR=obj
LDIR =./lib
OPTS =-DLINE_COUNT
LIBS=-lm

_DEPS = acutest.h  hash-table.h  vector_char.h str_cmp.h vector_string.h table_string.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

all: test_strcmp.bin tokenize.bin dictionary.bin linecount.bin duplicate.bin

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) ${OPTS} -c -o $@ $< $(CFLAGS)

test_strcmp.bin: obj/test_strcmp.o obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

tokenize.bin: obj/tokenize.o obj/vector_char.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

dictionary.bin: obj/dictionary.o obj/vector_char.o obj/vector_string.o obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

wordcount.bin: obj/wordcount.o obj/vector_char.o obj/table_string.o obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

linecount.bin: obj/linecount.o obj/vector_char.o obj/table_string.o obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

duplicate.bin: obj/dedup.o obj/vector_char.o obj/table_string.o obj/duplicate.o obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


unit_test_vector_char.bin: obj/unit_test_vector_char.o obj/vector_char.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

unit_test_vector_string.bin: obj/unit_test_vector_string.o obj/vector_string.o	obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

unit_test_table_string.bin: obj/unit_test_table_string.o obj/table_string.o obj/vector_char.o	obj/str_cmp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ *.bin


IDIR =./include
CC=gcc
CFLAGS= -ggdb -I$(IDIR)

ODIR=obj
LDIR =./lib

LIBS=-lm

all: arraylist.bin

_DEPS = arraylist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = arraylist.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

arraylist.bin: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
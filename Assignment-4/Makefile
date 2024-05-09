#
# Makefile for Cache Lab
# Requires a 64-bit x86-64 system 
#
CC = gcc
CFLAGS_TEST = -Wall -no-pie
CFLAGS_TRANS = -g -Wall -Werror -std=c99 -m64

all: test-trans tracegen

test-trans: support/test-trans.c trans.o support/cachelab.c support/cachelab.h
	$(CC) $(CFLAGS_TRANS) -o test-trans support/test-trans.c support/cachelab.c trans.o 

tracegen: support/tracegen.c trans.o support/cachelab.c
	$(CC) $(CFLAGS_TRANS) -O0 -o tracegen support/tracegen.c trans.o support/cachelab.c

trans.o: trans.c
	$(CC) $(CFLAGS_TRANS) -O0 -c trans.c

.FORCE:

cache-test: .FORCE cache-test-skel.c $(TEST_CACHE)
#	ifndef TEST_CACHE
#	$(error You did not define TEST_CACHE!)
#	endif

	$(CC) $(CFLAGS_TEST) cache-test-skel.c $(TEST_CACHE) -o $@    
    
#
# Clean the src dirctory
#
clean:
#    rm -rf *.o
	rm -f *.tar
#    rm -f csim
	rm -f test-trans tracegen
	rm -f trace.all trace.f*
#    rm -f .csim_results .marker
	rm -f trace.tmp
	rm -f trans.o
	rm -f .csim_results
	rm -f .marker
	rm -f cache-test

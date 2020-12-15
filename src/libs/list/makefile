.PHONY: lib test

LD_LIBRARY_PATH=/usr/local/lib/
GCC_OPT = -Wall -ggdb -std=gnu99


lib: liblist.o

liblist.o:
	gcc ${GCC_OPT} -Wall -o liblist.o -c liblist.c

test: liblist.o
	gcc ${GCC_OPT} -o test test.c liblist.o -lcriterion
	./test

clean:
	rm -rf liblist.o
	rm -rf ./test

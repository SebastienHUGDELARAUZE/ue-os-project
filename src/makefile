# Enable tracing
FLEX_OPT = # -d

# Enable color | .dot | .output which report lookhead / conflict solution / counter-examples
BISON_OPT = --color --graph --report=all

# Enable all warnings | Debug output | Use gnu99 Standard
GCC_OPT = -Wall -ggdb -std=gnu99

.PHONY: build_shell build_parser build_scanner clean realclean
build_shell: shell clean
build_parser: parser.c
build_scanner: scanner.c

# <BUILD>

OBJECTS = parser.o scanner.o shell.o list.o

parser.c:  # OUTPUT> parser.h parser.dot parser.output
	bison parser.y ${BISON_OPT} -o parser.c

parser.o: parser.c
	gcc ${GCC_OPT} -c parser.c

scanner.c:
	flex ${FLEX_OPT} -o scanner.c scanner.flex

scanner.o: scanner.c
	gcc ${GCC_OPT} -c scanner.c

shell.o:
	gcc ${GCC_OPT} -c shell.c

libs/list/liblist.o:
	cd libs/list/; make

variable.o:
	gcc ${GCC_OPT} -c variable.c

commands.o:
	gcc ${GCC_OPT} -c commands.c

tools.o:
	gcc ${GCC_OPT} -c tools.c

shell: parser.o scanner.o libs/list/liblist.o variable.o tools.o commands.o shell.o
	gcc ${GCC_OPT} -o shell parser.o scanner.o libs/list/liblist.o variable.o tools.o commands.o shell.o

# <CLEAN>

clean:
	rm -rf parser.c parser.h
	rm -rf scanner.c
	rm -rf *.o

clean_libs:
	cd libs/list/; make clean

clean_debug:
	rm -rf parser.output parser.dot

realclean: clean clean_libs clean_debug
	rm -rf shell

# Scanner Compilation (Enable tracing)
LEX		= flex
LFLAGS	= # -d

# Parser Compilation (Enable color | .dot | .output which report lookhead / conflict solution / counter-examples)
YACC 	= bison
YFLAGS	= --color --graph --report=all

# C Compilation (Enable all warnings | Debug output | Use gnu99 Standard)
CC 		= gcc
CFLAGS 	= -Wall -ggdb -std=gnu99

###############################################################################

.PHONY: build_shell build_parser build_scanner clean realclean

build_shell: shell
build_parser: parser.c
build_scanner: scanner.c

OBJECTS = parser.o scanner.o variable.o tools.o internal_cmd.o commands.o shell.o

###############################################################################

parser.c:
	${YACC} ${YFLAGS} -o parser.c parser.y

scanner.c:
	${LEX} ${LFLAGS} -o scanner.c scanner.flex

libs/list/liblist.o:
	cd libs/list/; make

shell: libs/list/liblist.o ${OBJECTS}

#########################################################################################

# OUTPUT> parser.h parser.dot parser.output

clean:
	rm -rf shell ${OBJECTS} parser.c parser.h scanner.c

clean_debug:
	rm -rf parser.output parser.dot

clean_libs:
	cd libs/list/; make clean

realclean: clean clean_debug clean_libs

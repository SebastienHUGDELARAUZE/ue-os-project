BISON_OPT = -Wcex --graph

.PHONY: build build_parser build_scanner clean realclean
build_shell: shell
build_parser: parser.c
build_scanner: scanner.c

# <BUILD>

parser.c: # OUTPUT> parser.h parser.dot parser.output
	bison parser.y --defines=parser.h -o parser.c ${BISON_OPT}

parser.o: parser.c
	gcc -c parser.c

scanner.c:
	flex -o scanner.c scanner.flex

scanner.o: scanner.c
	gcc -c scanner.c

shell.o:
	gcc -c shell.c

shell: parser.o scanner.o shell.o
	gcc -o shell parser.o scanner.o shell.o

# <CLEAN>

clean:
	rm -rf parser.c parser.h parser.dot parser.output
	rm -rf scanner.c
	rm -rf *.o

realclean: clean
	rm -rf shell
build: main
build_parser: syntax.c

# COMPILATION

main.c:
	bison grammar.y --defines=main.h -o main.c

main.o: main.c
	gcc -c main.c

syntax.c:
	flex -o syntax.c syntax.flex

syntax.o: syntax.c
	gcc -c syntax.c

shell.o:
	gcc -c shell.c

main: main.o syntax.o shell.o
	gcc -o main shell.o syntax.o main.o

# MAINTENANCE

clean:
	rm -rf main.c syntax.c
	rm -rf *.o
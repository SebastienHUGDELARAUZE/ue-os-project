.PHONY: build

all: build run_test soft_clean
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

# INSTALL

install_deps:
	pip install -r test/requirements.txt

# TEST

run_all_test:
	pytest test/ -vs

run_unit_test:
	pytest test/ -vs -m unit_test

run_funtional_test:
	pytest test/ -vs -m functional_test

# CLEAN

soft_clean:
	rm -rf main main.c syntax.c
	rm -rf *.o

clean: soft_clean
	rm -rf main
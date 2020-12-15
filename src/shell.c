#include <stdio.h>
#include "shell.h"

void initShell() {
    initVariableTable();
	printPrompt();
}

void printPrompt() {
	printf("%s > ", getWD());
}

void destroyShell() {
	freeVariableTable();
}

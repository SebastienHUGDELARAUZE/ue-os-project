#include <stdio.h>
#include "shell.h"
#include "tools.h"
#include "variable.h"

void initShell() {
    initVariableTable();
	printPrompt();
}

void destroyShell() {
	// TODO: free each variable
	freeVariableTable();
}

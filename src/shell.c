#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include "tools.h"
#include "variable.h"
#include "internal_cmd.h"

void initShell() {
    initVariableTable();
	initPath();
	printPrompt();
}

void destroyShell() {
	// TODO: free each variable
	freeVariableTable();
}

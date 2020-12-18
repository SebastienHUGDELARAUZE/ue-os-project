#include <stdio.h>
#include "shell.h"
#include "tools.h"
#include "variable.h"
#include "internal_cmd.h"

void initShell() {
    initVariableTable();
	addPath("/bin");
	printPrompt();
}

void destroyShell() {
	// TODO: free each variable
	freeVariableTable();
}

#ifndef OS_PROJECT_SHELL_H
#define OS_PROJECT_SHELL_H

#include "variable.h"
#include "commands.h"
#include "tools.h"

extern void initShell();
extern void printPrompt();
extern void destroyShell();

extern void setVariable(char* name, char* value);
extern char* getVariable(char* name);

#endif /* OS_PROJECT_SHELL_H */

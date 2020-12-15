#ifndef OS_PROJECT_SHELL_H
#define OS_PROJECT_SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

extern void initShell();
extern void printPrompt();
extern void destroyShell();

extern void setVariable(char* name, char* value);
extern char* getVariable(char* name);

extern void echo(char *);
extern void printWD();
extern void printPath();
extern void addPath(char*);
extern void deletePath();

extern void stripFL(char* str);

#endif /* OS_PROJECT_SHELL_H */

#ifndef OS_PROJECT_TOOL_H
#define OS_PROJECT_TOOL_H

#include <stdbool.h>

extern bool istty;

void stripFL(char* str);
void printPrompt();

#endif /* OS_PROJECT_TOOL_H */
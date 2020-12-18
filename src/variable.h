#ifndef OS_PROJECT_VAR_H
#define OS_PROJECT_VAR_H

#include <stdbool.h>

#define ERROR_VAR_UNKNOWN "[ERROR] Unknown variable: %s\n"

typedef struct variable {
    char* name;
    char* value;
} Variable;
typedef Variable* VariablePtr;


void initVariableTable();
void freeVariableTable();

void setVariable(char* name, char* value);
char* getVariable(char* name);
void deleteVariable(char* name);

#endif /* OS_PROJECT_VAR_H */

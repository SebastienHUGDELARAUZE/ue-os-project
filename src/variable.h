#ifndef OS_PROJECT_VAR_H
#define OS_PROJECT_VAR_H

#include <stdbool.h>

typedef struct variable {
    char* name;
    char* value;
} Variable;
typedef Variable* VariablePtr;

VariablePtr initVariable(char* name, char* value);
bool isVariable(VariablePtr var, char* name);

#define ERROR_VAR_UNKNOWN "[ERROR] Unknown variable: %s\n"

#endif /* OS_PROJECT_VAR_H */

#include "variable.h"

#include <stdlib.h>
#include <string.h>

VariablePtr initVariable(char* name, char* value) {
	VariablePtr var = malloc(sizeof(Variable));
	var->name = strdup(name);
	var->value = strdup(value);

	return var;
}

bool isVariable(VariablePtr var, char* name) {
    return (strcmp(var->name, name) == 0) ? true : false;
}
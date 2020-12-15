#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.h"
#include "libs/list/liblist.h"

ListPtr var_list;

bool isVariable(VariablePtr var, char* name);

void initVariableTable() {
	var_list = newList();
}

void freeVariableTable() {
	freeList(var_list);  // FIXME: Check for memory leaks
}

VariablePtr newVariable(char* name, char* value) {
	VariablePtr var = malloc(sizeof(Variable));
	var->name = strdup(name);
	var->value = strdup(value);

	return var;
}

void setVariable(char* name, char* value) {
	VariablePtr new_var = newVariable(name, value);
	addListNode(var_list, new_var);
}

char* getVariable(char* name) {
	VariablePtr requestedVar = getListNode(var_list, (fctCmp) isVariable, name);
	
	if (requestedVar == NULL) {
		fprintf(stderr, ERROR_VAR_UNKNOWN, name);
		return NULL;
	} else {
		return requestedVar->value;
	}
}

bool isVariable(VariablePtr var, char* name) {
    return (strcmp(var->name, name) == 0) ? true : false;
}

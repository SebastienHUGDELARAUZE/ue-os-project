#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.h"
#include "libs/list/liblist.h"

ListPtr var_list;

void freeVariable(VariablePtr var);
bool isVariable(VariablePtr var, char* name);

// VARIABLE ARRAY

void initVariableTable() {
	var_list = newList();
}

void freeVariableTable() {  // FIXME: Check for memory leaks
	freeItemList(var_list, (fctFree) freeVariable);
	freeList(var_list);
}

// VARIABLE UNIT

VariablePtr newVariable(char* name, char* value) {
	VariablePtr var = malloc(sizeof(Variable));
	var->name = strdup(name);
	var->value = strdup(value);

	return var;
}

void freeVariable(VariablePtr var) {
	free(var->name);
	free(var->value);
	free(var);
}

void setVariable(char* name, char* value) {
	NodePtr requestedVarNode = getListNode(var_list, (fctCmp) isVariable, name);
	
	if (requestedVarNode) {  // Found a var node matching
		VariablePtr requestedVar = (VariablePtr) requestedVarNode->item;
		free(requestedVar->value);
		requestedVar->value = strdup(value);
	} else {  // Need to create a new one
		VariablePtr new_var = newVariable(name, value);
		addListNode(var_list, new_var);
	}
	
}

char* getVariable(char* name) {
	NodePtr requestedVarNode = getListNode(var_list, (fctCmp) isVariable, name);

	if (requestedVarNode == NULL) {
		fprintf(stderr, ERROR_VAR_UNKNOWN, name);
		return NULL;
	} else {
		VariablePtr requestedVar = (VariablePtr) requestedVarNode->item;
		return requestedVar->value;
	}
}

void deleteVariable(char* name) {
	NodePtr requestedVarNode = getListNode(var_list, (fctCmp) isVariable, name);

	if (requestedVarNode) {
		VariablePtr requestedVar = requestedVarNode->item;
		freeVariable(requestedVar);
	}
}

bool isVariable(VariablePtr var, char* name) {
    return (strcmp(var->name, name) == 0) ? true : false;
}

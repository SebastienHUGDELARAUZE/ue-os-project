#include "shell.h"
#include "list.h"
#include "variable.h"

char GlobalPath[BUFFER_SIZE] = "";
ListPtr var_list;

/* **************************************** */

char* getWD();

/* **************************************** */
/* PUBLIC METHODS						    */
/* **************************************** */

void initShell() {
	var_list = newList();
    
	printPrompt();
}

void printPrompt() {
	printf("%s > ", getWD());
}

void destroyShell() {
	freeList(var_list);
}

/* **************************************** */

void setVariable(char* name, char* value) {
	VariablePtr new_var = initVariable(name, value);
	addListNode(var_list, new_var);
}

char* getVariable(char* name) {
	NodePtr nodeLookup = var_list->first;

	while (nodeLookup) {
		VariablePtr varLookup = nodeLookup->item;
		if (isVariable(varLookup, name)) return varLookup->value;
		
		nodeLookup = nodeLookup->next;
	}
	fprintf(stderr, ERROR_VAR_UNKNOWN, name);
	return NULL;
}

/* **************************************** */

void echo(char *text) {
	if (text != NULL)
		printf("%s\n", text);
}

void printWD() {
	printf("PWD=%s\n", getWD());
}

void printPath() {
	printf("PATH=%s\n", GlobalPath);
}

void addPath(char *path) {
	if (GlobalPath[0] != '\0')
		strcat(GlobalPath, ":");
	strcat(GlobalPath, path);
}

void deletePath() {
	GlobalPath[0]='\0';
}

/* **************************************** */

void stripFL(char* str) {
	memmove(str, str+1, strlen(str));
	str[strlen(str)-1] = '\0';
}

/* **************************************** */
/* PRIVATE METHODS						    */
/* **************************************** */

char* getWD() {
	return getcwd(NULL, 0);
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tools.h"

void stripFL(char* str) {
	memmove(str, str+1, strlen(str));
	str[strlen(str)-1] = '\0';
}

char* getWD() {
	return getcwd(NULL, 0);
}

void printPrompt() {
	printf("%s > ", getWD());
}
// TODO: char* formatPath(); | return "PATH=%s", GlobalPath
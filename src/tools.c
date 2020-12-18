#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tools.h"

bool istty = true;

void stripFL(char* str) {
	memmove(str, str+1, strlen(str));
	str[strlen(str)-1] = '\0';
}

void printPrompt() {
	if (istty) printf("%s > ", getcwd(NULL, 0));
}

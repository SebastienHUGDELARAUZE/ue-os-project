#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "internal_cmd.h"


#define BUFFER_SIZE 1024
char GlobalPath[BUFFER_SIZE] = "\0";

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

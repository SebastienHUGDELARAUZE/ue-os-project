#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "internal_cmd.h"


char GlobalPath[BUFFER_SIZE];

void initPath() {
	strcpy(GlobalPath, "PATH=\0");
	// addPath("/bin");
}

void echo(char *text) {
	if (text != NULL)
		printf("%s\n", text);
}

void printWD() {
	printf("PWD=%s\n", getenv("PWD"));
}

void printPath() {
	printf("%s\n", GlobalPath);
}

void addPath(char *path) {
	if (GlobalPath[5] != '\0')
		strcat(GlobalPath, ":");
	strcat(GlobalPath, path);
}

void deletePath() {
	initPath();
}

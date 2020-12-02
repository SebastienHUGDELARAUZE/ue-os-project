#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"

char GlobalPath[BUFFER_SIZE] = "";

void showPath()
{
	printf("PATH=%s\n", GlobalPath);
	displayPrompt();
}

void deletePath()
{
	GlobalPath[0]='\0';
	displayPrompt();
}

void addPath(char *path)
{
	if (GlobalPath[0] != '\0')
		strncat(GlobalPath, ":", 100);
	strncat(GlobalPath, path, 100);
	printf("PATH=%s\n",GlobalPath);
	displayPrompt();
}

void displayPwd()
{
	char buf[BUFFER_SIZE] = "";
	getcwd(buf, BUFFER_SIZE);
	printf("PWD=%s\n", buf);
	displayPrompt();
}

void displayPrompt()
{
	printf("> ");
}

void echo(char *text) {
	printf("echo> %s\n", text);
	displayPrompt();
}
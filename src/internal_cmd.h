#ifndef OS_PROJECT_INT_CMD_H
#define OS_PROJECT_INT_CMD_H

#define BUFFER_SIZE 2048
extern char GlobalPath[BUFFER_SIZE];

void echo(char*);
void printWD();
void printPath();
void addPath(char*);
void deletePath();

#endif /* OS_PROJECT_INT_CMD_H */

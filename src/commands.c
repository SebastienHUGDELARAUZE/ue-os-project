#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "internal_cmd.h"

extern char** environ;


void executeExternalCommand(CmdReqPtr cr);
void setupProcess(CmdReqPtr cr);
bool isValid(CmdReqPtr cr);

// COMMANDS

void cmd_orchestrator(CmdReqPtr command_request) {
	
	cmd_debug(command_request);
	
	switch (command_request->type) {
		case EXTERNAL:
			executeExternalCommand(command_request);
			break;

		case ECHO:
			echo(command_request->argv[0]);
			break;
			
		case PWD:
			printWD();
			break;
			
		case SHOW_PATH:
			printPath();
			break;
			
		case ADD_PATH:
			addPath(command_request->argv[0]);
			break;
			
		case DELETE_PATH:
			deletePath();
			break;
			
		default:
			fprintf(stderr, ERROR_CMDREQ_UNDEFINED_TYPE, command_request->type);
			break;
	}
}

void cmd_debug(CmdReqPtr cr) {
	printf("#-------------------------#\n");
	printf("| CMD DEBUG\n");
	printf("| >Type=%d\n", cr->type);
	printf("| >Count=%ld\n", cr->argc);
	for (size_t arg_index = 0; arg_index < cr->argc; arg_index++) {
		printf("| >Argv[%ld]=%s\n", arg_index, cr->argv[arg_index] ? cr->argv[arg_index] : "NULL");
	}
	printf("| >Flag REDIRECTION=%s\n", cr->flag_redir ? "YES" : "NO");
	printf("| >Flag OVERWRITE=%s\n", cr->flag_overw ? "YES" : "NO");
	printf("| >STDOUT FILE=%s\n", cr->file_output ? cr->file_output : "NULL");
	printf("| >Flag BACKGROUND=%s\n", cr->flag_backg ? "YES" : "NO");
	printf("| >Check=%s\n", isValid(cr) ? "OK" : "KO");
	printf("#-------------------------#\n");
}

void executeExternalCommand(CmdReqPtr cr) {
	pid_t cpid = fork();
	if (cpid == -1) {
		perror("Fork failed\n");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {  	// CHILD PROCESS
		char* nenv[] = { GlobalPath, NULL };
		environ = nenv;
		setupProcess(cr);
		execvp(cr->argv[0], cr->argv);
		perror("(External command failed)");
		_exit(EXIT_FAILURE);
	} else  {  			// PARENT PROCESS
		wait(NULL);
	}
}

void setupProcess(CmdReqPtr cr) {
	if (cr->flag_redir) {
		freopen(cr->file_output, cr->flag_overw ? "w" : "a", stdout);
	}
}

// COMMANDS REQUESTS

CmdReqPtr newInternalCmdReq(CmdType type) {
	CmdReqPtr cr = malloc(sizeof(CmdReq));
	
	cr->type = type;
	cr->argc = 0;
	cr->argv = NULL;

	cr->flag_redir = false;
	cr->flag_overw = false;
	cr->file_output = NULL;

	cr->flag_backg = false;

	return cr;
}

CmdReqPtr newInternalCmdReqWithArg(CmdType type, char* arg) {
	CmdReqPtr cr = newInternalCmdReq(type);
	
	cr->argc = 1;
	cr->argv = calloc(sizeof(char*), cr->argc);
	cr->argv[0] = arg;

	return cr;
}

CmdReqPtr newExternalCmdReq(CmdType type, char* command, ListPtr args) {
	CmdReqPtr cr = newInternalCmdReq(type);
	
	addListNode(args, NULL);

	cr->type = type;
	cr->argc = args->count;
	cr->argv = (char**) getItemsTable(args);
	cr->argv[0] = command;

	return cr;
}

void freeCmdReq(CmdReqPtr cr) {
	free(cr->argv);
	free(cr);
}

void addArgumentToCmdReq(CmdReqPtr cr, char* arg) {
	cr->argv[cr->argc++] = arg;
	cr->argv = realloc(cr->argv, cr->argc);
	cr->argv[cr->argc] = NULL;
}

void setRedirectionToCmdReq(CmdReqPtr cr, char* file_output, bool overwrite) {
	cr->flag_redir = true;
	cr->flag_overw = overwrite;
	cr->file_output = file_output;
}

void setBackgroundToCmdReq(CmdReqPtr cr) {
	cr->flag_backg = true;
}

bool isValid(CmdReqPtr cr) {
	if (cr->type == EXTERNAL)
		return (cr->argv[cr->argc-1] == NULL);
	else
		return true;
}

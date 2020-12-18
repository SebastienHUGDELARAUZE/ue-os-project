#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "internal_cmd.h"

bool isValid(CmdReqPtr cr);

// COMMANDS

void cmd_orchestrator(CmdReqPtr command_request) {
	
	// execvpe(FILE, ARGV, ENVP);
	// FILE = "FILE"
	// ARGV [ARG0="FILE", ARG1, ..., NULL]
	// ENVP ["PATH=...", NULL]

	cmd_debug(command_request);
	
	switch (command_request->type) {
		case EXTERNAL:
			printf("External command: %s (%ld args)\n", command_request->argv[0], command_request->argc-1);
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
	printf("CMD>Type=%d\n", cr->type);
	printf("CMD>Count=%ld\n", cr->argc);
	for (size_t arg_index = 0; arg_index < cr->argc; arg_index++) {
		char* argv = cr->argv[arg_index];
		if (argv) {
			printf("CMD>ARGV[%ld]=%p\n", arg_index, argv);
		} else {
			printf("CMD>ARGV[%ld]=NULL\n", arg_index);
		}
	}
	printf("CMD>Check=%s\n", isValid(cr) ? "OK" : "KO");
}

// COMMANDS REQUESTS

CmdReqPtr newInternalCmdReq(CmdType type) {
	CmdReqPtr cr = malloc(sizeof(CmdReq));
	
	cr->type = type;
	cr->argc = 0;

	return cr;
}

CmdReqPtr newInternalCmdReqWithArg(CmdType type, char* arg) {
	CmdReqPtr cr = malloc(sizeof(CmdReq));
	
	cr->type = type;
	cr->argc = 1;
	cr->argv = calloc(sizeof(char*), cr->argc);
	cr->argv[0] = arg;

	return cr;
}

CmdReqPtr newExternalCmdReq(CmdType type, char* command, ListPtr args) {
	CmdReqPtr cr = malloc(sizeof(CmdReq));
	
	addListNode(args, NULL);

	cr->type = type;
	cr->argc = args->count;  // COMMAND | ARGS | ... | NULL
	// cr->argv = calloc(sizeof(char*), cr->argc);
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

bool isValid(CmdReqPtr cr) {
	if (cr->type == EXTERNAL)
		return (cr->argv[cr->argc-1] == NULL);
	else
		return true;
}

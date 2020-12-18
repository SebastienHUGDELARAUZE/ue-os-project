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


void forkHandler(CmdReqPtr cr, fctCmdReq parent, fctCmdReq child);
void MainThread(CmdReqPtr cr);
void ExternalCmdProcess(CmdReqPtr cr);
void ExternalCmdBackgProcess(CmdReqPtr cr);

// EXTERNAL COMMAND FORK HANDLER

void executeExternalCommand(CmdReqPtr cr) {
	forkHandler(cr, MainThread, ExternalCmdProcess);
}

void setupExternalCommandProcess(CmdReqPtr cr) {
	putenv(GlobalPath);
	
	if (cr->flag_redir) {
		freopen(cr->file_output, cr->flag_overw ? "w" : "a", stdout);
	}
}

// FORK HANDLER

void forkHandler(CmdReqPtr cr, fctCmdReq parentHandler, fctCmdReq childHandler) {
	pid_t cpid = fork();
	if (cpid == -1) {
		perror("Fork failed\n");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {  	// CHILD PROCESS
		childHandler(cr);
	} else {  			// PARENT PROCESS
		parentHandler(cr);
	}
}

void MainThread(CmdReqPtr cr) {
	// if (!cr->flag_backg)
	wait(NULL);
}

void ExternalCmdProcess(CmdReqPtr cr) {
	setupExternalCommandProcess(cr);

	execvp(cr->argv[0], cr->argv);
	
	perror("(External command failed)");
	_exit(EXIT_FAILURE);
}

void ExternalCmdBackgProcess(CmdReqPtr cr) {

}

// COMMAND ROUTER

void cmd_router(CmdReqPtr command_request) {
	
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

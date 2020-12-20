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

void MainProcess(pid_t PID, CmdReqPtr cr);
void ExternalCmdProcess(pid_t PID, CmdReqPtr cr);
void ExternalCmdBackgProcess(pid_t PID, CmdReqPtr cr);
void ExternalCmdBackgMonitor(pid_t PID, CmdReqPtr cr);

// EXTERNAL COMMAND FORK HANDLER

void executeExternalCommand(CmdReqPtr cr) {
	forkHandler(cr, MainProcess, (cr->flag_backg) ? ExternalCmdBackgProcess : ExternalCmdProcess);
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
		childHandler(cpid, cr);
	} else {  			// PARENT PROCESS
		parentHandler(cpid, cr);
	}
}

void MainProcess(pid_t PID, CmdReqPtr cr) {
	if (!cr->flag_backg)
		wait(NULL);
}

void ExternalCmdProcess(pid_t PID, CmdReqPtr cr) {
	setupExternalCommandProcess(cr);

	execvp(cr->argv[0], cr->argv);

	perror("(External command failed)");
	_exit(EXIT_FAILURE);
}

void ExternalCmdBackgProcess(pid_t PID, CmdReqPtr cr) {
	forkHandler(cr, ExternalCmdBackgMonitor, ExternalCmdProcess);
}

void ExternalCmdBackgMonitor(pid_t PID, CmdReqPtr cr) {
	printf("[+ %d]\n", PID);
	waitpid(PID, NULL, 0);
	printf("[- %d]\n", PID);
	_exit(EXIT_SUCCESS);
}

// COMMAND ROUTER

void cmd_router(CmdReqPtr command_request) {
	
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

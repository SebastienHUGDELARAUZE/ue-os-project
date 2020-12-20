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
	
	if (cr->flag_redir == REDIR_OVERWRITE) {
		freopen(cr->redir_output.pathname, "w", stdout);
	} else if (cr->flag_redir == REDIR_APPEND) {
		freopen(cr->redir_output.pathname, "a", stdout);
	} else if (cr->flag_redir == REDIR_PIPE_R) {
		// printf("%d->Input\n", cr->redir_output.pipefd[0]);
		close(cr->redir_output.pipefd[1]);
		dup2(cr->redir_output.pipefd[0], STDIN_FILENO);
	} else if (cr->flag_redir == REDIR_PIPE_W) {
		// printf("Output->%d\n", cr->redir_output.pipefd[1]);
		close(cr->redir_output.pipefd[0]);
		dup2(cr->redir_output.pipefd[1], STDOUT_FILENO);
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
	if (cr->flag_redir == REDIR_PIPE_R) {
		close(cr->redir_output.pipefd[0]);  // Close READ
		close(cr->redir_output.pipefd[1]);  // Close WRITE

		wait(NULL);
		wait(NULL);
	}
	else if (!cr->flag_backg) {
		wait(NULL);
	}
}

void ExternalCmdProcess(pid_t PID, CmdReqPtr cr) {
	setupExternalCommandProcess(cr);

	execvp(cr->argv[0], cr->argv);

	perror(cr->argv[0]);
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
	
	if (command_request == NULL) {
		return;
	} else {
		// printf("Executing cmd [%d]...\n", command_request->type);
	}

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

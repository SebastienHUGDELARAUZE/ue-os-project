#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmd_request.h"

CmdReqPtr newInternalCmdReq(CmdType type) {
	CmdReqPtr cr = malloc(sizeof(CmdReq));
	
	cr->type = type;
	cr->argc = 0;
	cr->argv = NULL;

	cr->flag_redir = NONE;

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
	cr->flag_redir = overwrite ? REDIR_OVERWRITE : REDIR_APPEND;
	cr->redir_output.pathname = file_output;
}

void setPipeToCmdReq(CmdReqPtr cr_left, CmdReqPtr cr_right) {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
	
	cr_right->flag_redir = REDIR_PIPE_R;
	cr_right->redir_output.pipefd[0] = pipefd[0];
	cr_right->redir_output.pipefd[1] = pipefd[1];

	cr_left->flag_redir = REDIR_PIPE_W;
	cr_left->redir_output.pipefd[0] = pipefd[0];
	cr_left->redir_output.pipefd[1] = pipefd[1];
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

void cmd_debug(CmdReqPtr cr) {
	printf("\n\t| >Type=%d\n", cr->type);
	printf(  "\t| >Count=%ld\n", cr->argc);
	for (size_t arg_index = 0; arg_index < cr->argc; arg_index++) {
		printf("\t|  >Argv[%ld]=%s\n", arg_index, cr->argv[arg_index] ? cr->argv[arg_index] : "NULL");
	}
	printf(  "\t| >Flag REDIRECTION=%d\n", cr->flag_redir);
	if (cr->flag_redir == REDIR_OVERWRITE || cr->flag_redir == REDIR_APPEND)
		printf(  "\t|  >STDOUT path=%s\n", cr->redir_output.pathname ? cr->redir_output.pathname : "NULL");
	else if (cr->flag_redir == REDIR_PIPE_W || cr->flag_redir == REDIR_PIPE_R)
		printf(  "\t|  >STDOUT fd[0]=%d|fd[1]=%d\n", cr->redir_output.pipefd[0], cr->redir_output.pipefd[1]);
	printf(  "\t| >Flag BACKGROUND=%s\n", cr->flag_backg ? "YES" : "NO");
	printf(  "\t| >Check=%s\n", isValid(cr) ? "OK" : "KO");
}


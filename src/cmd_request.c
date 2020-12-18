#include <stdlib.h>
#include <stdio.h>
#include "cmd_request.h"

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

void cmd_debug(CmdReqPtr cr) {
	printf("\n\t| >Type=%d\n", cr->type);
	printf(  "\t| >Count=%ld\n", cr->argc);
	for (size_t arg_index = 0; arg_index < cr->argc; arg_index++) {
		printf("\t|  >Argv[%ld]=%s\n", arg_index, cr->argv[arg_index] ? cr->argv[arg_index] : "NULL");
	}
	printf(  "\t| >Flag REDIRECTION=%s\n", cr->flag_redir ? "YES" : "NO");
	printf(  "\t| >Flag OVERWRITE=%s\n", cr->flag_overw ? "YES" : "NO");
	printf(  "\t|  >STDOUT FILE=%s\n", cr->file_output ? cr->file_output : "NULL");
	printf(  "\t| >Flag BACKGROUND=%s\n", cr->flag_backg ? "YES" : "NO");
	printf(  "\t| >Check=%s\n", isValid(cr) ? "OK" : "KO");
}


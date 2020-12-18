#ifndef OS_PROJECT_CMD_H
#define OS_PROJECT_CMD_H

#include <stdbool.h>
#include "libs/list/liblist.h"


enum cmd_type {
    EXTERNAL, ECHO, PWD, SHOW_PATH, ADD_PATH, DELETE_PATH
};
typedef enum cmd_type CmdType;

typedef struct cmd_request {
    CmdType         type;
    size_t          argc;
    char**          argv;
    // bool            background;
} CmdReq;
typedef CmdReq* CmdReqPtr;

#define ERROR_CMDREQ_UNDEFINED_TYPE "ERROR: Command request type is not recognized (%d)\n"

void cmd_orchestrator(CmdReqPtr command_request);
void cmd_debug(CmdReqPtr cr);

CmdReqPtr newInternalCmdReq(CmdType type);
CmdReqPtr newInternalCmdReqWithArg(CmdType type, char* arg);
CmdReqPtr newExternalCmdReq(CmdType type, char* command, ListPtr args);
void freeCmdReq(CmdReqPtr cr);
void addArgumentToCmdReq(CmdReqPtr cr, char* arg);

#endif /* OS_PROJECT_CMD_H */

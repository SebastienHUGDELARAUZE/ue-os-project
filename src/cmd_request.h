#ifndef OS_PROJECT_CMD_REQ_H
#define OS_PROJECT_CMD_REQ_H

#include <stddef.h>
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

    bool            flag_redir;
    bool            flag_overw;
    char*           file_output;

    bool            flag_backg;
} CmdReq;
typedef CmdReq* CmdReqPtr;

typedef void (*fctCmdReq)(CmdReqPtr cr);

#define ERROR_CMDREQ_UNDEFINED_TYPE "ERROR: Command request type is not recognized (%d)\n"

CmdReqPtr newInternalCmdReq(CmdType type);
CmdReqPtr newInternalCmdReqWithArg(CmdType type, char* arg);
CmdReqPtr newExternalCmdReq(CmdType type, char* command, ListPtr args);
void freeCmdReq(CmdReqPtr cr);
void addArgumentToCmdReq(CmdReqPtr cr, char* arg);
void setRedirectionToCmdReq(CmdReqPtr cr, char* file_output, bool overwrite);
void setBackgroundToCmdReq(CmdReqPtr cr);
bool isValid(CmdReqPtr cr);
void cmd_debug(CmdReqPtr cr);

#endif /* OS_PROJECT_CMD_REQ_H */
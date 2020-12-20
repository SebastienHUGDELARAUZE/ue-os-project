#ifndef OS_PROJECT_CMD_REQ_H
#define OS_PROJECT_CMD_REQ_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include "libs/list/liblist.h"

enum redir_type {
    NONE, REDIR_OVERWRITE, REDIR_APPEND, REDIR_PIPE_W, REDIR_PIPE_R
};
typedef enum redir_type RedirType;

enum cmd_type {
    EXTERNAL, ECHO, PWD, SHOW_PATH, ADD_PATH, DELETE_PATH
};
typedef enum cmd_type CmdType;

typedef struct cmd_request {
    CmdType         type;
    size_t          argc;
    char**          argv;

    RedirType       flag_redir;
    union redir_output
    {
        char*       pathname;
        int         pipefd[2];
    } redir_output;
    
    bool            flag_backg;
} CmdReq;
typedef CmdReq* CmdReqPtr;

typedef void (*fctCmdReq)(pid_t PID, CmdReqPtr cr);

#define ERROR_CMDREQ_UNDEFINED_TYPE "ERROR: Command request type is not recognized (%d)\n"

CmdReqPtr newInternalCmdReq(CmdType type);
CmdReqPtr newInternalCmdReqWithArg(CmdType type, char* arg);
CmdReqPtr newExternalCmdReq(CmdType type, char* command, ListPtr args);
void freeCmdReq(CmdReqPtr cr);
void addArgumentToCmdReq(CmdReqPtr cr, char* arg);
void setRedirectionToCmdReq(CmdReqPtr cr, char* file_output, bool overwrite);
void setPipeToCmdReq(CmdReqPtr cr_left, CmdReqPtr cr_right);
void setBackgroundToCmdReq(CmdReqPtr cr);
bool isValid(CmdReqPtr cr);
void cmd_debug(CmdReqPtr cr);

#endif /* OS_PROJECT_CMD_REQ_H */
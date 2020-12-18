%{
#include <string.h>
#include "shell.h"

int yylex();
%}

%defines "parser.h"

%verbose
%define parse.trace
%define parse.error detailed

%code requires {
    #include "tools.h"
    #include "commands.h"
    #include "variable.h"
    #include "internal_cmd.h"
    #include "libs/list/liblist.h"
}

%union {
  char*         str;
  CmdReqPtr     cmd_req;
  ListPtr       list;
}


%token <str> VAR
%token ACCESS ASSIGN BLANK EOL
%token <str> ARG PATH WORD STRING COMMAND
%token REDIR_OVER REDIR_APP REDIR_CMD BACKG
%token CMD_ECHO CMD_PWD CMD_SHOWPATH CMD_ADDPATH CMD_DELPATH

%type <str> variable_access
%type <cmd_req> cmd cmd_internal cmd_external handlers
%type <list> external_cmd_arg

%printer { fprintf(yyoutput, "%s", $$); } <str>
%printer { fprintf(yyoutput, "%d (%ld)", $$->type, $$->argc); } <cmd_req>

%destructor { free($$); }           <str>
%destructor { freeCmdReq($$); }     <cmd_req>
%destructor { freeList($$); }       <list>

%code provides {
    void yyerror(const char* msg);
}

%%

shell: %empty
     | shell variables // FIXME: variables_assign
     | shell cmd                                            { cmd_orchestrator($2); }
     | shell handlers                                       { cmd_orchestrator($2); }
     | shell EOL                                            { printPrompt(); }
;

handlers: cmd REDIR_APP PATH                                { setRedirectionToCmdReq($1, $3, false); $$ = $1; }
        | cmd REDIR_OVER PATH                               { setRedirectionToCmdReq($1, $3, true);  $$ = $1; }
        | cmd REDIR_CMD cmd                                 { printf("[WIP] PIPE"); }
        | cmd BACKG                                         { setBackgroundToCmdReq($1);             $$ = $1; }
;

cmd: cmd_internal
   | cmd_external
;

variables: variable_assign
         | variable_access
;

variable_assign: VAR ASSIGN                                 { deleteVariable($1); }
               | VAR ASSIGN WORD                            { setVariable($1, $3); }
               | VAR ASSIGN STRING                          { setVariable($1, $3); }
;

variable_access: ACCESS VAR                                 { $$ = getVariable($2); }
;

cmd_internal: CMD_ECHO PATH                                 { $$ = newInternalCmdReqWithArg(ECHO, $2); }
            | CMD_ECHO STRING                               { $$ = newInternalCmdReqWithArg(ECHO, $2); }
            | CMD_ECHO variable_access                      { $$ = newInternalCmdReqWithArg(ECHO, $2); }
            | CMD_PWD                                       { $$ = newInternalCmdReq(PWD); }
            | CMD_SHOWPATH                                  { $$ = newInternalCmdReq(SHOW_PATH); }
            | CMD_ADDPATH PATH                              { $$ = newInternalCmdReqWithArg(ADD_PATH, $2); }
            | CMD_DELPATH                                   { $$ = newInternalCmdReq(DELETE_PATH); }
;

cmd_external: PATH external_cmd_arg                         { $$ = newExternalCmdReq(EXTERNAL, $1, $2); }
;

external_cmd_arg: %empty                                    { $$ = newList(); addListNode($$, NULL); }
                | external_cmd_arg ARG                      { addListNode($1, $2); $$ = $1; }
                | external_cmd_arg PATH                     { addListNode($1, $2); $$ = $1; }
                | external_cmd_arg variable_access          { addListNode($1, $2); $$ = $1; }
;

%%

int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        yydebug = 1;
        printf("DEBUG");
    }

    initShell();
    int parser_result = yyparse();
    destroyShell();

    return parser_result;
}

void yyerror(const char *msg) {
    fprintf(stderr, "!> yyerror: %s\n", msg);
}

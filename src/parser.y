%{
#include "shell.h"

int yylex();
%}

%defines "parser.h"

%verbose
%define parse.trace
%define parse.error detailed

%union {
  char* str;
}


%token <str> VAR
%token ACCESS ASSIGN BLANK EOL
%token <str> ARG PATH WORD STRING COMMAND
%token REDIR_OVER REDIR_APP REDIR_CMD BACKG
%token CMD_ECHO CMD_PWD CMD_SHOWPATH CMD_ADDPATH CMD_DELPATH

%type <str> cmd 
/* %type <str> internal_cmd */
/* %type <str> external_cmd external_cmd_arg */
%type <str> variables_access



%printer { fprintf(yyoutput, "%s", $$); } <str>

%destructor { free($$); } <str>

%code provides {
    void yyerror(const char* msg);
}

%%

shell: %empty
     | shell variables
     | shell cmd
     | shell handlers
     | shell EOL                                            { printPrompt(); }
;

handlers: cmd REDIR_APP PATH                                { printf("[WIP-REDIR A: %s]", $3); }
        | cmd REDIR_OVER PATH                               { printf("[WIP-REDIR O: %s]", $3); }
        | cmd REDIR_CMD cmd                                 { printf("[WIP-%s PIPE to %s]", $1, $3); }
        | cmd BACKG                                         { printf("[WIP-BACKGROUND: %s]", $1); }
;

cmd: internal_cmd
   | external_cmd
;

variables: variables_assign
         | variables_access
;

variables_assign: VAR ASSIGN WORD                           { setVariable($1, $3); }
                | VAR ASSIGN STRING                         { setVariable($1, $3); }
;

variables_access: ACCESS VAR                                { $$ = getVariable($2); }
;

internal_cmd: CMD_ECHO PATH                                 { echo($2); }
            | CMD_ECHO STRING                               { echo($2); }
            | CMD_ECHO variables_access                     { echo($2); }
            | CMD_PWD                                       { printWD(); }
            | CMD_SHOWPATH                                  { printPath(); }
            | CMD_ADDPATH PATH                              { addPath($2); }
            | CMD_DELPATH                                   { deletePath(); }
;

external_cmd: PATH external_cmd_arg                         { printf("[WIP-EXTCMD]"); }
;

external_cmd_arg: %empty
                | external_cmd_arg ARG                      { printf("[WIP-EXTCMD-ARG A: %s]", $2); }
                | external_cmd_arg PATH                     { printf("[WIP-EXTCMD-ARG P: %s]", $2); }
                | external_cmd_arg variables_access         { printf("[WIP-EXTCMD-ARG V]"); }
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

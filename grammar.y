%{
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

#define YYSTYPE char *

extern char * yytext;

void yyerror(const char *s);
int yyparse();
int yylex();
%}

%define parse.error detailed
%start input

//Symboles terminaux qui seront fournis par yylex()
%token ARG
%token PATH
%token STRING
%token INTEGER

%token CMD_ECHO
%token CMD_PWD
%token CMD_SHOWPATH
%token CMD_ADDPATH
%token CMD_DELPATH
%%

input: 
      %empty
    | input internal_cmd
    | input external_cmd
;

internal_cmd:
      CMD_ECHO PATH         { echo(yytext); }
    | CMD_ECHO STRING       { echo(yytext); }
    | CMD_PWD               { displayWD(); }
    | CMD_SHOWPATH          { displayPath(); }
    | CMD_ADDPATH PATH      { addPath(yytext); }
    | CMD_DELPATH           { deletePath(); }
;

external_cmd: 
      PATH
    | external_cmd ARG      { printf("ARG\n"); }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "!> yyerror: %s\n", s);
    exit(EXIT_FAILURE);
}

void main(void) {
    displayPrompt();
    yyparse();
    exit(EXIT_SUCCESS);
}

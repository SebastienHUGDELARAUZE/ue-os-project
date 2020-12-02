%{
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE char*
void yyerror(char *s);
int yyparse();
int yylex();

#include "shell.h"

extern char * yytext;
%}

//Symboles terminaux qui seront fournis par yylex()
%token ENTIER
%token PATH
%token STRING

%token CMDECHO

%token CMDPWD
%token CMDPATH
%token DELPATH
%token SHOWPATH
%token ADDPATH
%%

commande: 
	| commande DELPATH          {deletePath();}
	| commande SHOWPATH         {showPath();}
	| commande CMDPWD           {displayPwd();}
	| commande ADDPATH PATH     {addPath(yytext);}
    | commande CMDECHO PATH     {echo(yytext);}
    | commande CMDECHO STRING   {echo(yytext);}
;

%%

void yyerror(char *s) {
    printf("yyerror : %s\n",s);
    exit(EXIT_FAILURE);
}

void main(void) {
    displayPrompt();
    yyparse();
    exit(EXIT_SUCCESS);
}

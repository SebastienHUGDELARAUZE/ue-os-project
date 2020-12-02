%{
#include <stdio.h>
#define YYSTYPE char*
int yyparse();
int yylex();
int yyerror(char *s);

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

int yyerror(char *s) {
    printf("yyerror : %s\n",s);
    return 0;
}

int main(void) {
    displayPrompt();
    yyparse();
    return 0;
}

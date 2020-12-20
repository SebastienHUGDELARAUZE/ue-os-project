%{

#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "shell.h"

%}

%option noinput nounput noyywrap nodefault

%s S_GET S_SET

assign          "="
access          "$"
redir_over      ">"
redir_app       ">>"
redir_cmd       "|"
backg           "&"
eol             \n

cmd_exit        exit
cmd_echo        echo
cmd_pwd         pwd
cmd_showpath    showpath
cmd_addpath     addpath
cmd_delpath     delpath

var_start       [[:alpha:]_]
letter          [[:alnum:]_]
multi_word      [[:alnum:][:blank:]/_\.]+

id              {var_start}{letter}*
word            {letter}+ 
string          \"{multi_word}\"
command         \`{multi_word}\`

path            [[:alnum:]_/.\-\*\+]+
arg             -[[:alpha:]]+

blank           [[:blank:]]

%%

<INITIAL>{blank}                    { /* Empty */ }
<S_GET,S_SET>{blank}                { BEGIN(INITIAL); return(BLANK); }

{access}                            { BEGIN(S_GET); return(ACCESS); }
<S_GET>{id}                         { yylval.str = strdup(yytext); BEGIN(INITIAL); return(VAR); }

{id}/{assign}                       { yylval.str = strdup(yytext); BEGIN(S_SET); return(VAR); }
{assign}                            { return(ASSIGN); }
<S_SET>{word}                       { yylval.str = strdup(yytext); BEGIN(INITIAL); return(WORD); }

{redir_over}                        { return(REDIR_OVER); }
{redir_app}                         { return(REDIR_APP); }
{redir_cmd}                         { return(REDIR_CMD); }
{backg}                             { return(BACKG); }

{cmd_exit}                          { return(CMD_EXIT); }
{cmd_echo}                          { return(CMD_ECHO); }
{cmd_pwd}                           { return(CMD_PWD); }
{cmd_showpath}                      { return(CMD_SHOWPATH); }
{cmd_addpath}                       { return(CMD_ADDPATH); }
{cmd_delpath}                       { return(CMD_DELPATH); }

<INITIAL>{path}                     { yylval.str = strdup(yytext); return(PATH); }
{string}                            { yylval.str = strdup(yytext); stripFL(yylval.str); BEGIN(INITIAL); return(STRING); }
{command}                           { yylval.str = strdup(yytext); stripFL(yylval.str); return(COMMAND); }

{arg}                               { yylval.str = strdup(yytext); return(ARG); }

{eol}                               { BEGIN(INITIAL); return(EOL); }
<*>.                                { BEGIN(INITIAL); return *yytext; }

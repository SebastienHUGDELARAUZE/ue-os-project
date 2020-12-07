%{
#include "main.h"
#define YYSTYPE char*
%}

%option noyywrap

cmdecho     echo

cmdpwd	    pwd
cmdaddpath  addpath
cmddelpath  delpath
cmdshowpath showpath

blanks      [ \t\n]+
integer     [0-9]+
path        [a-zA-Z0-9\/]+
argument    -[a-zA-Z0-9\/]+
string	    \"[ a-zA-Z0-9\/]+\"

%%

{blanks}        { /* ignore */ }

{cmdecho}       { return CMD_ECHO; }
{cmdpwd}    	{ return CMD_PWD; }
{cmddelpath}	{ return CMD_DELPATH; }
{cmdshowpath} 	{ return CMD_SHOWPATH; }
{cmdaddpath}    { return CMD_ADDPATH; }

{integer}    	{ return INTEGER; }
{path}		    { return PATH; }
{argument}      { return ARG; }
{string}        { return STRING; }

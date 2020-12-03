%{
#include "main.h"
#define YYSTYPE char*
%}

%option noyywrap

blanks      [ \t\n]+
integer     [0-9]+
path        [a-zA-Z0-9\/]+
string	    \"[ a-zA-Z0-9\/]+\"

cmdecho     echo

cmdpwd	    pwd
cmdaddpath  addpath
cmddelpath  delpath
cmdshowpath showpath

%%

{blanks}        { /* ignore */ }

{cmdecho}       { return(CMDECHO); } 

{cmdpwd}    	{ return(CMDPWD); }
{cmddelpath}	{ return(DELPATH); }
{cmdshowpath} 	{ return(SHOWPATH); }
{cmdaddpath}    { return(ADDPATH); } 

{integer}    	{ return(INTEGER); }
{path}		    { return(PATH); }
{string}        { return(STRING); }

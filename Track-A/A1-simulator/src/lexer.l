%option noyywrap nodefault

%{
#include "parser.tab.h"
%}

%%
[ \t\r\n]+  ;
.           ;
%%

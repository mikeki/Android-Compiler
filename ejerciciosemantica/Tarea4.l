%{
#include <stdlib.h>
#include "Tarea4.tab.h"
%}

%%
"program"          {return PROGRAM;}
"var"           		{return VAR;}
"int"           {return INT;}
"float"           {return FLOAT;}
"write"           {return PRINT;}
"if"           { return IF;}
"else"           {return ELSE;}
\".*\"           {yylval.str = strdup(yytext);return CTES;}
[0-9]+           {yylval.integer = atoi(yytext);return CTEI;}
[0-9]+[.][0-9]+           {yylval.float_n = atof(yytext);return CTEF;}
[A-Za-z]+[0-9]*([_][A-Za-z0-9]+|[A-Za-z0-9]*)           {yylval.str = strdup(yytext);return ID;}
";"		{return PC;}
","		{return COMA;}
":"		{return DOSPUNTOS;}
"{"		{return ALLAVE;}
"}"		{return CLLAVE;}
"="		{return IGUAL;}
">"		{return MAYOR;}
"<"		{return MENOR;}
"<>"		{return DIFERENTE;}
"("		{return APARENTESIS;}
")"		{return CPARENTESIS;}
"+"		{return MAS;}
"-"		{return MENOS;}
"*"		{return POR;}
"/"		{return DIVISION;}




%%

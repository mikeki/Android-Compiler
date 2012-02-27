%{
#include <stdlib.h>


%}

id		[a-zA-Z]([a-zA-Z0-9]|[_])*
ctei		[0-9]+
ctef		[0-9]+"."[0-9]+

%%

"**"[^*]*"**" {printf("comments1");}
"//".*	{printf("comments2");}

"adelante" {printf( "ADELANTE");}
"atras" {printf( "ATRAS");}
"rotaderecha" {printf( "ROTADERECHA");}
"rotaizquierda" {printf( "ROTAIZQUIERDA");}
"tomartesoro" {printf( "TOMARTESORO");}
"topa" {printf( "TOPA");}
"verpista" {printf( "VERPISTA");}
"si" {printf( "SI");}
"sino" {printf( "SINO");}
"mientras" {printf( "MIENTRAS");}
"funcion" {printf( "FUNCION");}
"entero" {printf( "ENTERO");}
"flotante" {printf( "FLOTANTE");}
"selecciona" {printf( "SELECCIONA");}
"cuando" {printf( "CUANDO");}
"regresa" {printf( "REGRESA");}
"logico" {printf( "LOGICO");}
"palabra" {printf( "PALABRA");}
"escribe" {printf( "ESCRIBE");}
"lee" {printf( "LEE");}
"principal" {printf( "PRINCIPAL");}
"vacio" {printf( "VACIO");}
"verdadero" {printf( "VERDADERO");}
"falso" {printf( "FALSO");}
"y" {printf( "Y");}
"o" {printf( "O");}
"no" {printf( "NO");}
"programa" {printf( "PROGRAMA");}
"caracter" {printf( "CARACTER");}

{ctei} {printf("CTE");}
{ctef} {
        printf("CTEF");}
\"[^\"]*\" {
                    printf("CTESTRING");}
"'"[A-Za-z]"'" {
          printf("CARACTER");}
{id} {
      printf("ID");}


"," {printf( "COMA");}
";" {printf( "PUNTOCOMA");}
":" {printf( "IGUALP");}
"{" {printf( "ALLAVE");}
"}" {printf( "CLLAVE");}
"=" {printf( "IGUALR");}
">" {printf( "MAYORQUE");}
"<" {printf( "MENORQUE");}
"<>" {printf( "DIFERENTE");}
"(" {printf( "APARENTESIS");}
")" {printf( "CPARENTESIS");}
"+" {printf( "MAS");}
"-" {printf( "MENOS");}
"*" {printf( "POR");}
"/" {printf( "ENTRE");}
"." {printf( "CONCA");}

. {printf("RARO");};

%%


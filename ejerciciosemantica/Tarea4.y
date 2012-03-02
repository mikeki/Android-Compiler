%{
#include <stdio.h>
#include <string.h>
#include <glib.h>




int i = 1;
int j = 0;
//static GList *var_table;
static GHashTable *var_table;

typedef struct{
//char *tipo;
char *nombre;
}vars;


void create_var_table(){
	var_table = g_hash_table_new(g_str_hash, g_str_equal);
}

void insert_var_to_table(char *name){
	if(g_hash_table_lookup(var_table,(gpointer)name) != NULL){
		printf("Error de Semantica variable %s redeclarada\n",name);
		exit(1);
	}else{
	vars *temp = g_slice_new(vars);
	temp->nombre= name;
	g_hash_table_insert(var_table,(gpointer)name,(gpointer)temp);
	}
}	
	

void imprime(GHashTable *var_table2){
	printf("Lista:");
	g_hash_table_foreach(var_table,(GHFunc)printf,NULL);
	printf("\n");
	
	
}


%}
%union{
int integer; 
float float_n;
char *str; 
}
%token PROGRAM VAR INT FLOAT PRINT IF ELSE PC COMA DOSPUNTOS ALLAVE CLLAVE IGUAL MAYOR MENOR DIFERENTE
%token APARENTESIS CPARENTESIS MAS MENOS POR DIVISION
%token <float_n> CTEF
%token <str> CTES
%token <str> ID
%token <integer> CTEI
%start programa
%%
programa : PROGRAM ID PC programap bloque;
programap : /*vacio */ | vars;

vars : VAR varspp ;
varspp : varsp DOSPUNTOS tipo PC varsppp;
varsppp : /*vacio */ | varspp;
varsp : ID {//variables = variables + yylval.str);
		//printf("%s \n",yylval.str);
		insert_var_to_table(yylval.str)		
		} 
	| ID COMA varsp;

tipo : INT | FLOAT;

bloque : ALLAVE bloquep CLLAVE;
bloquep :  /*vacio*/ | estatuto bloquep;

estatuto : asignacion | condicion | escritura;

asignacion : ID IGUAL expresion PC;

escritura : PRINT APARENTESIS escriturap CPARENTESIS PC;
escriturapp : expresion | CTES;
escriturap : escriturapp | escriturapp COMA escriturap;

expresion : exp expresionp;
expresionp : /*vacio*/ | MAYOR exp | MENOR exp | DIFERENTE exp;

exp : termino expp;
expp : /*vacio*/ |MAS exp | MENOS exp;

termino : factor terminop;
terminop : /* vacio*/ |POR termino | DIVISION termino ;

condicion : IF APARENTESIS expresion CPARENTESIS bloque condicionp PC;
condicionp : /*vacio*/ | ELSE bloque;

factor : APARENTESIS expresion CPARENTESIS | factorp varcte;
factorp : /* vacio */ | MAS | MENOS;

varcte : ID | CTEI | CTEF;


%%


yyerror (s) /* Llamada por yyparse ante un error */
     char *s;
{
 
  printf("%s\n", s); /* Esta implementación por defecto nos valdrá */
  /* Si no creamos esta función, habrá que enlazar con –ly en el
momento de compilar para usar una implementación por defecto */
}

main() {
	create_var_table();
  yyparse();
	imprime(var_table);
	free(var_table);
}



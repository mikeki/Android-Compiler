%{
#include <stdio.h>
#include <string.h>
#include <glib.h>

static GHashTable *dir_procs;
static char *proc_actual;
static char *tipo_actual;
/*
Estructuras para las tabalase de procedimientos y tabla de variables
*/
typedef struct{
GHashTable *var_table;
}funcion;

typedef struct{
char *tipo;
char *nombre;
}variable;

/*
CUBO SEMANTICO
*/
char cubo[6][6][19] =
	{
		{//SUMA(+)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//RESTA(-)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MULTIPLICACION(*)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//DIVISION(/)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//CONCATENACION(.)
			{'E','E','S','S','E','E'},
			{'E','E','S','S','E','E'},
			{'S','S','S','S','E','E'},
			{'S','S','S','S','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MAYORQUE(>)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MENORQUE(<)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//DIFERENTE(<>)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MASMAS(++)
			{'E','E','E','E','E','I'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MENOSMENOS(--)
			{'E','E','E','E','E','I'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MAYORIGUAL(>=)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MENORIGUAL(<=)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MASIGUAL(+=)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//MENOSIGUAL(-=)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//Y(Y)
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','L','E'},
			{'E','E','E','E','E','E'}
		},
		{//O(O)
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','L','E'},
			{'E','E','E','E','E','E'}
		},
		{//NOT(NO)
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','L'},
			{'E','E','E','E','E','E'}
		},
		{//IGUAL(=)
			{'I','I','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','S','S','E','E'},
			{'E','E','S','C','E','E'},
			{'E','E','E','E','L','E'},
			{'E','E','E','E','E','E'}
		},
		{//IGUALIGUAL(==)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','E','E','L','E'},
			{'E','E','E','E','E','E'}
		}
	} 

/*
Descripcion: Inicializa la tabla de dir_procs (directorio de procedimientos)

Parametros: void
Salida:void
*/
void create_dir_table(){
	dir_procs = g_hash_table_new(g_str_hash, g_str_equal);
}

/*
Descripcion: Funcion que se encarga de insetrar un procedimiento, programa global
y la rutina principal

Parametros: char * name
Salida:void
*/
void insert_proc_to_table(char *name){
	if(g_hash_table_lookup(dir_procs,(gpointer)name) != NULL){
		printf("Error de Semantica funcion %s redeclarada\n",name);
		exit(1);
	}else{
	funcion *temp = g_slice_new(funcion);
	temp->var_table = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(dir_procs,(gpointer)name,(gpointer)temp);
	proc_actual = name;
	}
}	
/*
Descripcion: Inserta una variable en el proceso actual en su tabla de 
variables correspondiente.

Parametros: char *name
Salida:void
*/	
void insert_var_to_table(char *name){
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	//printf("%s", tabla->var_table);
	if(g_hash_table_lookup(tabla->var_table,(gpointer)name) != NULL){
		printf("Error de Semantica variable %s redeclarada\n",name);
		exit(1);
	}else{
		variable *temp = g_slice_new(variable);
		temp->tipo = tipo_actual;
		temp->nombre = name;
		g_hash_table_insert(tabla->var_table,(gpointer)name,(gpointer)temp);
		g_hash_table_foreach(tabla->var_table,(GHFunc)printf,NULL);
	}
	
}
/*
Descripcion: Verificar en la tabla de variablas del procedimiento actual 
si existe la variable declarada(en la tabla).Regresa error de semantica
si no cumple.

Parametros: char *name
Salida: void
*/
void verifica_existe_var(char *name){
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	if(g_hash_table_lookup(tabla->var_table,(gpointer)name) == NULL){
		funcion *tabla = g_hash_table_lookup(dir_procs,"programa");
		if(g_hash_table_lookup(tabla->var_table,(gpointer)name) == NULL){
			printf("Error de Semantica variable %s no declarada\n",name);
			exit(1);
		}
	}
	
	
}

/*
Descripcion: Verificar en el directorio de procedimientos si existe el procedimiento
mandado como parametro.Regresa error de semantica si no cumple.

Parametros: char *name
Salida: void
*/
void verifica_existe_procs(char *name){
	if(g_hash_table_lookup(dir_procs,(gpointer)name) == NULL){
		printf("Error de Semantica funcion %s no declarada\n",name);
		exit(1);
	}
	
}
/*
Descripcion: Imprime el resultado de lo que se guardo en una tabla

Parametros: GHashTable *a
Salida:void
*/
void imprime(GHashTable *a){
	printf("Lista:");
	g_hash_table_foreach(a,(GHFunc)printf,NULL);
	
	
	printf("\n");
	
	
}

%}
%union{ 
int integer; 
float float_n;
char *str; 
} 
%token ADELANTE ATRAS ROTADERECHA ROTAIZQUIERDA TOMARTESORO TOPA
%token VERPISTA SI SINO MIENTRAS FUNCION ENTERO FLOTANTE SELECCIONA CUANDO
%token REGRESA LOGICO PALABRA ESCRIBE LEE PRINCIPAL VACIO VERDADERO FALSO
%token Y O NO PROGRAMA CARACTER COMA PUNTOCOMA IGUALP ALLAVE CLLAVE
%token IGUALR MAYORQUE MENORQUE DIFERENTE APARENTESIS CPARENTESIS
%token MAS MENOS POR ENTRE CONCA
%token <float_n> CTF
%token <str> CTESTRING
%token <str> ID
%token <str> CAR
%token <integer> CTE

%start programa

%% 
programa: PROGRAMA ID{insert_proc_to_table("programa");} IGUALP programap main;
programap: programapp programappp;
programapp: 	vars programapp
		| ;
programappp: funcion programappp
		| ;

vars: tipo ID{insert_var_to_table(yylval.str);} varsp;
varsp: lva
	|varid;
lva: IGUALR lvap;
lvap: lectura PUNTOCOMA
	| mmexp PUNTOCOMA;
varid: COMA ID{insert_var_to_table(yylval.str);} varidp
	| PUNTOCOMA;
varidp: varid 
	| ;

funcion: FUNCION ID{insert_proc_to_table(yylval.str);} APARENTESIS funcionpp CPARENTESIS ALLAVE funcionp CLLAVE;
funcionp: estatutofuncion funcionp
	| ;
funcionpp: params 
	| ;

main: PRINCIPAL{insert_proc_to_table(yylval.str);} ALLAVE bloque CLLAVE;

bloque: estatuto bloque
	| ;

tipo:	 ENTERO {tipo_actual= "entero";}
	|FLOTANTE {tipo_actual= "flotante";}
	| CARACTER {tipo_actual= "caracter";}
	| PALABRA {tipo_actual= "string";}
	| LOGICO {tipo_actual= "logico";};

varcte: ID{verifica_existe_var(yylval.str);}
	| CTE
	| CTESTRING
	| CTF
	| CAR
	| VACIO
	| VERPISTA
	| VERDADERO
	| FALSO
	| accionsi;

estatutofuncion: asignacion
		|condicion
		|escritura
		|ciclo
		|accion
		|vars
		|regresa;

estatuto: asignacion
		|condicion
		|escritura
		|ciclo
		|accion
		|vars;


regresa: REGRESA mmexp PUNTOCOMA;

asignacion: 	ID{verifica_existe_var(yylval.str);} asignacionp;
asignacionp: 	asigp
		| asigpp;
asigp: 		IGUALR lea;
lea: 		lectura PUNTOCOMA
		|mmexp PUNTOCOMA;
asigpp:		ap 
		| app;
ap:		MAS MAS PUNTOCOMA
		|MENOS MENOS PUNTOCOMA;
app:		MAS IGUALR atipo PUNTOCOMA
		| MENOS IGUALR atipo PUNTOCOMA;
atipo:		CTE
		| CTF
		| ID{verifica_existe_var(yylval.str);};

condicion: c
	|  cp;
c:	SI APARENTESIS mmexp CPARENTESIS ALLAVE bloque CLLAVE sip;
sip:	SINO sipp
	| ;
sipp: 	condicion
	| ALLAVE bloque CLLAVE;
cp: 	SELECCIONA APARENTESIS exp CPARENTESIS ALLAVE cuandop CLLAVE;
cuandop: CUANDO varselecciona IGUALR MAYORQUE ALLAVE bloque CLLAVE cuandopp;
cuandopp: cuandop 
	| ;

escritura: ESCRIBE APARENTESIS escriturap CPARENTESIS PUNTOCOMA;
escriturap: escriturapp;
escriturapp: varcte e 
	| exp e;
e: 	CONCA escriturapp
	| ;

lectura: LEE APARENTESIS CPARENTESIS;

ciclo: MIENTRAS APARENTESIS mmexp CPARENTESIS ALLAVE bloque CLLAVE;

accion: acciones APARENTESIS accionp CPARENTESIS PUNTOCOMA;
accionp: params2 
	| ;
accionsi: acciones APARENTESIS accionp CPARENTESIS;
acciones: ADELANTE
	| ATRAS
	| ROTADERECHA
	| ROTAIZQUIERDA
	| TOMARTESORO
	| TOPA
	| ID{verifica_existe_procs(yylval.str);};

params: tipo paramsp;
paramsp: ID{insert_var_to_table(yylval.str);} paramspp;
paramspp: COMA paramsp
	| params
	| ;
params2: exp params2p;
params2p: COMA params2
	| ;

mmexp: nop mexp mmexpp;
nop: 	NO
	| ;
mmexpp: O mexp 
	| ;
mexp: nop expresion mexpp;
mexpp: Y expresion
	| ;
expresion: nop exp expresionp;
expresionp: ep exp 
		| ;
ep: 	MAYORQUE epp
	|MENORQUE epp
	| DIFERENTE;
epp: IGUALR 
	| ;
exp: termino expp;
expp: MAS exp
	| MENOS exp 
	| ;

termino: factor terminop;
terminop: POR termino
	| ENTRE termino
	| ;

factor: factorp 
	| factorpp;
factorp: APARENTESIS mmexp CPARENTESIS;
factorpp: f varcte;
f: 	MENOS 
	| ;

varselecciona: ID{verifica_existe_var(yylval.str);}
		|CTE
		|CAR;
 

%% 
main() { 
create_dir_table();
  yyparse(); 
imprime(dir_procs);
free(dir_procs);
}

yyerror(char *s){
       printf("%s \n", s);
}

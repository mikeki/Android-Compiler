%{
#include <stdio.h>
#include <string.h>
#include <glib.h>

static GHashTable *dir_procs;
static char *proc_actual;
static char *tipo_actual;
static char *id_a_verificar;
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
	};

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

vars: tipo vars_id PUNTOCOMA;
vars_id: ID{insert_var_to_table(yylval.str);} varsip;
varsip: COMA vars_id
        | IGUALR var_init var_initp
        | ;
var_init: lectura
          | mmexp;
var_initp: COMA vars_id
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

varcte: CTE
	| CTESTRING
	| CTF
	| CAR
	| VACIO
	| VERPISTA
	| VERDADERO
	| FALSO;

estatutofuncion: estatuto
		|regresa;

estatuto: empieza_id
		|condicion
		|escritura
		|ciclo
		|accion
		|vars;
		
empieza_id: ID{id_a_verificar=yylval.str;} empieza_idp;
empieza_idp: ejecuta_funcion
            | asignacion;

ejecuta_funcion:  APARENTESIS paramsf CPARENTESIS{verifica_existe_procs(id_a_verificar);} PUNTOCOMA;

paramsf: params2
          | ;

regresa: REGRESA mmexp PUNTOCOMA;

asignacion:  asignacionp{verifica_existe_var(id_a_verificar);} PUNTOCOMA;
asignacionp: 	asigp
		| asigpp;
asigp: 		IGUALR lea;
lea: 	lectura
		  |mmexp;
asigpp:		ap 
		| app;
ap:		MAS MAS
		|MENOS MENOS;
app:		MAS IGUALR atipo
		| MENOS IGUALR atipo;
atipo:		CTE
		| CTF
		| ID{verifica_existe_var(yylval.str);};

condicion: c
	|  cp;
c:	SI APARENTESIS condicion_exp CPARENTESIS ALLAVE bloque CLLAVE sip;
condicion_exp: mmexp
               | accionsi;
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
	| TOPA;

params: tipo paramsp;
paramsp: ID{insert_var_to_table(yylval.str);} paramspp;
paramspp: COMA paramsp
	| params
	| ;
params2: exp params2p;
params2p: COMA params2
	| ;

mmexp: mexp mmexpp;

mmexpp: O mmexp 
	| ;
	
mexp: expresion mexpp;
mexpp: Y mexp
	| ;
	
expresion: exp expresionp;
expresionp: ep expresion 
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
	| factorpp
	| factorppp;
factorp: APARENTESIS mmexp CPARENTESIS;
factorpp: f varcte;
f: 	MENOS 
	| NO
	| ;
factorppp: ID{id_a_verificar=yylval.str;} fun_var;
fun_var: APARENTESIS paramsf CPARENTESIS{verifica_existe_procs(id_a_verificar);}
         | {verifica_existe_var(id_a_verificar);};
	
varselecciona: ID{verifica_existe_var(yylval.str);}
		|CTE
		|CAR;
 

%% 
main() { 
create_dir_table();
  yyparse(); 
imprime(dir_procs); 

/*
printf("Proc3");
g_hash_table_get_values(dir_procs);
printf("Proc2");
GQueue *tablas = g_hash_table_get_values(dir_procs);
printf("Proc1");
funcion *tabla = g_queue_pop_head(tablas);

//g_queue_foreach(tablas,(GFunc)printf,NULL);

while(tabla != NULL){
	printf("Proc");
	imprime(tabla->var_table);
	tabla = g_queue_pop_head(tablas);
}

g_list_free(tablas);
free(tabla);
*/

free(dir_procs);
}

yyerror(char *s){
       printf("%s \n", s);
}

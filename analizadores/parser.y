%{
#include <stdio.h>
#include <string.h>
#include <glib.h>

static GHashTable *dir_procs;
static GHashTable *tabla_constantes;
static char *proc_actual;
static char tipo_actual;
static char *id_a_verificar;
static int exp_operador_actual;

//Declaracion de las pilas.
static GQueue *POperandos;
static GQueue *POperadores;
static GQueue *PTipos;
static GQueue *PSaltos;

//Declaracion de rangos de memoria
//Globales
	int enterosglobales = 110000;
	int flotantesglobales = 120000;
	int stringsglobales = 130000;
	int caracteresglobales = 140000;
	int logicosglobales = 150000;
//Locales
	int enteroslocales = 210000;
	int flotanteslocales = 220000;
	int stringslocales = 230000;
	int caractereslocales = 240000;
	int logicoslocales = 250000;

//Temporales
	int enterostemporales = 310000;
	int flotantestemporales = 320000;
	int stringstemporales = 330000;
	int caracterestemporales = 340000;
	int logicostemporales = 350000;

//Constantes
	int enterosconstantes = 410000;
	int flotantesconstantes = 420000;
	int stringsconstantes = 430000;
	int caracteresconstantes = 440000;
	int logicosconstantes = 450000;
//Declaracion del archivo objeto
FILE *objeto;

/*
Estructuras para las tabalase de procedimientos y tabla de variables
*/
typedef struct{
GHashTable *var_table;
}funcion;

typedef struct{
char tipo;
char *nombre;
int dir_virtual;
}variable;

typedef struct{
int dir_virtual;
}constante;

/*
CUBO SEMANTICO
*/
char cubo[6][6][20] =
	{
		{//SUMA(+)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
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
		{//MASIGUAL(+=)
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
		{//MENOSMENOS(--)
			{'E','E','E','E','E','I'},
			{'E','E','E','E','E','E'},
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
		{//MENORIGUAL(<=)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
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
		{//MAYORIGUAL(>=)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		},
		{//IGUALIGUAL(==)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','E','E','L','E'},
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
		}
		,
		{//NEGATIVO(-)
			{'E','E','E','E','E','I'},
			{'E','E','E','E','E','F'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'}
		}
	};

/*
Descripcion: Inicializa la tabla de dir_procs (directorio de procedimientos)

Parametros: void
Salida:void
*/
void crear_pilas_tablas(){
	dir_procs = g_hash_table_new(g_str_hash, g_str_equal);
	POperandos = g_queue_new();
	POperadores = g_queue_new();
	PTipos = g_queue_new();
	PSaltos = g_queue_new();
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
		int virtual;
		switch(tipo_actual){
			case 'I': if(strcmp(proc_actual,"programa")== 0){
					virtual = enterosglobales;
					enterosglobales++;			
				} else{
					virtual = enteroslocales;
					enteroslocales++;
				}
				break;
			case 'F': if(strcmp(proc_actual,"programa")== 0){
					virtual = flotantesglobales;
					flotantesglobales++;			
				} else{
					virtual = flotanteslocales;
					flotanteslocales++;
				}
				break;
			case 'S': if(strcmp(proc_actual,"programa")== 0){
					virtual = stringsglobales;
					stringsglobales++;			
				} else{
					virtual = stringslocales;
					stringslocales++;
				}
				break;
			case 'C': if(strcmp(proc_actual,"programa")== 0){
					virtual = caracteresglobales;
					caracteresglobales++;			
				} else{
					virtual = caractereslocales;
					caractereslocales++;
				}
				break;
			case 'L': if(strcmp(proc_actual,"programa")== 0){
					virtual = logicosglobales;
					logicosglobales++;			
				} else{
					virtual = logicoslocales;
					logicoslocales++;
				}
				break;
		}
		temp->dir_virtual = virtual;
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
Descripcion: Función que se encrag de regresar el id numérico correspondiente
del tipo que se le etsa mandando como paramtero

Parametros: char tipo
Salida: entero
*/
int traduce_tipo(char tipo){
	switch(tipo){
		case 'I': return 0;
		case 'F': return 1;
		case 'S': return 2;
		case 'C': return 3;
		case 'L': return 4;
	}

}

/*
Descripcion: Función que se encaraga de escribir en un arhcivo de codigo
objeto los cuadruplos que reciba.

Parametros: int operador, int operando1, int operando2, int resultadotmp
Salida: void
*/
void generar_cuadruplo(int operador, int operando1, int operando2, int resultadotmp){
	
	fprintf(objeto,"%d,%d,%d,%d\n",operador,operando1,operando2,resultadotmp);
}

/*
Descripcion: Función que se encraga de  regresar el operador al cual corresponde
dependiendo de los 2 ultimos operadores. Aplica exclusiavmente para los 
operadores con 2 caracteres.

Parametros: int operador1, int operador2
Salida: int
*/
int dame_operador_logico(int operador1, int operador2){
	if(operador1 == 9 && operador2 == 18){
		return 11;
	}else if(operador1 == 12 && operador2 == 18){
		return 13;
	}else if(operador1 == 18 && operador2 == 18){
		return 14;
	}

}

/*
Descripcion: Función que se encarga de regresar si el operador es
de tipo logico

Parametros: int operador
Salida: int
*/
int valida_existencia_logico(int operador){
	if(operador >= 9 && operador <= 14){
		return 1;
	}else{
		return 0;
	}

}
/*
Descripcion: Se encarga de obtener los opendos, tipos d eoperandos
y el operador para generar el cuadruplo

Parametros: 
Salida: void
*/
void generar_cuadruplo_expresion(){
	int operando2 = (int)g_queue_pop_head(POperandos);
	int operando1 = (int)g_queue_pop_head(POperandos);
	int operador = (int)g_queue_pop_head(POperadores);
	char tipo2 = g_queue_pop_head(PTipos);
	char tipo1 = g_queue_pop_head(PTipos);

	char tnuevo = cubo[traduce_tipo(tipo1)][traduce_tipo(tipo2)][operador];
	if(tnuevo == 'E'){
		printf("Error no se puede hacer esa operación");
	}else{
		int tmp;
		switch(tnuevo){
			case 'I': tmp = enterostemporales;
				enterostemporales++;
				break;
			case 'F': tmp = flotantestemporales;
				flotantestemporales++;
				break;
			case 'S': tmp = stringstemporales;
				stringstemporales++;
				break;
			case 'C': tmp = caracterestemporales;
				caracterestemporales++;
				break;
			case 'L': tmp = logicostemporales;
				logicostemporales++;
				break;
		}
		generar_cuadruplo(operador,operando1,operando2,tmp);
		g_queue_push_head(POperandos,tmp);
	}

}
/*
Descripcion: Se encarga de obtener el operand, tipos de operando
y el operador para generar el cuadruplo para expresiones de tipo unarias

Parametros: 
Salida: void
*/
void generar_cuadruplo_expresion_unaria(){
	int operando1 = g_queue_pop_head(POperandos);
	int operador = g_queue_pop_head(POperadores);
	char tipo1 = g_queue_pop_head(PTipos);

	char tnuevo = cubo[traduce_tipo(tipo1)][5][operador];
	if(tnuevo == 'E'){
		printf("Error no se puede hacer esa operación");
	}else{
		int tmp;
		switch(tnuevo){
			case 'I': tmp = enterostemporales;
				enterostemporales++;
				break;
			case 'F': tmp = flotantestemporales;
				flotantestemporales++;
				break;
			case 'S': tmp = stringstemporales;
				stringstemporales++;
				break;
			case 'C': tmp = caracterestemporales;
				caracterestemporales++;
				break;
			case 'L': tmp = logicostemporales;
				logicostemporales++;
				break;
		}
		generar_cuadruplo(operador,operando1,-1,tmp);
		g_queue_push_head(POperandos,tmp);
	}

}
/*
Descripcion:Funcion que se encarga de insertar las constantes a la 
tabla de constantes

Parametros:int virtual, int tipo
Salida: void
*/
void insert_constante_to_table(char *valor, int tipo){
	constante *cte = g_slice_new(constante);
	cte = g_hash_table_lookup(tabla_constantes,(gpointer)valor);
	
	if(cte == NULL){
		
		int dir;
		switch(tipo){
			case 1: dir = enterosconstantes;
				enterosconstantes++;
				break;
			case 2: dir = flotantesconstantes;
				flotantesconstantes++;
				break;
			case 3: dir = stringsconstantes;
				stringsconstantes++;
				break;
			case 4: dir = caracteresconstantes;
				caracteresconstantes++;
				break;
			case 5: dir = logicosconstantes;
				logicosconstantes++;
				break;
		}
		cte= g_slice_new(constante);
		cte->dir_virtual = dir;
		g_hash_table_insert(tabla_constantes,(gpointer)valor,(gpointer)cte);
		//printf("lkjcf\n");
		g_queue_push_head(PTipos,tipo);
		g_queue_push_head(POperandos,dir);
	}else{
		g_queue_push_head(PTipos,tipo);
		g_queue_push_head(POperandos,cte->dir_virtual);
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
char *integer; 
char *float_n;
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

tipo:	 ENTERO {tipo_actual= 'E';}
	|FLOTANTE {tipo_actual= 'F';}
	| CARACTER {tipo_actual= 'C';}
	| PALABRA {tipo_actual= 'S';}
	| LOGICO {tipo_actual= 'L';};

varcte: CTE {insert_constante_to_table(yylval.integer,1);}
	| CTESTRING {insert_constante_to_table(yylval.str,2);}
	| CTF {insert_constante_to_table(yylval.str,3);}
	| CAR {insert_constante_to_table(yylval.str,4);}
	| VACIO
	| VERPISTA
	| VERDADERO{insert_constante_to_table(yylval.str,5);}
	| FALSO{insert_constante_to_table(yylval.str,5);};

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
atipo:		CTE {insert_constante_to_table(yylval.integer,1);}
		| CTF {insert_constante_to_table(yylval.integer,2);}
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

mmexp: mexp {if(g_queue_peek_head(POperadores) == 16){
			generar_cuadruplo_expresion();		
	}} mmexpp;
mmexpp: O {g_queue_push_head(POperadores,16);/*operador or*/} mmexp 
	| ;
	
mexp: expresion{if(g_queue_peek_head(POperadores) == 15){
			generar_cuadruplo_expresion();		
	}} mexpp;
mexpp: Y{g_queue_push_head(POperadores,15);/*operador and*/} mexp
	| ;
	
expresion: exp{if(valida_existencia_logico(g_queue_peek_head(POperadores))){
			generar_cuadruplo_expresion();		
	}} expresionp;
expresionp: ep expresion 
		| ;
ep: 	MAYORQUE{g_queue_push_head(POperadores,12);/*operador mayorque*/ exp_operador_actual = 12;}  epp
	|MENORQUE{g_queue_push_head(POperadores,9);/*operador menorque*/ exp_operador_actual = 9;} epp
	| DIFERENTE{g_queue_push_head(POperadores,10);/*operador diferente*/}
	| IGUALR IGUALR  {g_queue_push_head(POperadores,14);/*operador igual igual*/} ;
epp: IGUALR {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		}
	| ;
	
exp: termino{if(g_queue_peek_head(POperadores) == 0 || g_queue_peek_head(POperadores) == 3){
			generar_cuadruplo_expresion();		
	}} expp;
expp: MAS{g_queue_push_head(POperadores,0);/*operador suma*/}  exp
	| MENOS{g_queue_push_head(POperadores,3);/*operador resta*/}  exp 
	| ;

termino: factor{if(g_queue_peek_head(POperadores) == 6 || g_queue_peek_head(POperadores) == 7){
			generar_cuadruplo_expresion();		
	}} terminop;
terminop: POR{g_queue_push_head(POperadores,6);/*operador multiplica*/} termino
	| ENTRE{g_queue_push_head(POperadores,7);/*operador division*/} termino
	| ;

factor: factorp 
	| factorpp
	| factorppp;
factorp: nf APARENTESIS{g_queue_push_head(POperadores,'(');} mmexp CPARENTESIS {if(g_queue_peek_head(POperadores) == '('){
		g_queue_pop_head(POperadores);
		}else{
			printf("Mala construccion de expresion");
		};
		if(g_queue_peek_head(POperadores) == 17){
			generar_cuadruplo_expresion_unaria();
		}
		}
nf:	NO{g_queue_push_head(POperadores,17);/*operador NOT*/}
	|;
factorpp: f varcte {if(g_queue_peek_head(POperadores) == 17 || g_queue_peek_head(POperadores) == 19){
			generar_cuadruplo_expresion_unaria();
			}};
f: 	MENOS {g_queue_push_head(POperadores,19);/*operador multiplica*/}
	| NO {g_queue_push_head(POperadores,17);/*operador NOT*/}
	| ;
factorppp: ID{id_a_verificar=yylval.str;} fun_var;
fun_var: APARENTESIS paramsf CPARENTESIS{verifica_existe_procs(id_a_verificar);}
         | {verifica_existe_var(id_a_verificar);
         	//Obteniendo el tipo de variable en la tabla d evariables
		funcion *tabla = g_slice_new(funcion);
		tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
		variable *var = g_slice_new(variable);
		var = g_hash_table_lookup(tabla->var_table,(gpointer)id_a_verificar);
		g_queue_push_head(POperandos,var->dir_virtual);
		g_queue_push_head(PTipos,var->tipo);
         	};
	
varselecciona: ID{verifica_existe_var(yylval.str);}
		|CTE {insert_constante_to_table(yylval.integer,1);}
		|CAR {insert_constante_to_table(yylval.str,4);};
 

%% 
main() { 
objeto = fopen("codigo.obj", "w");
crear_pilas_tablas();
  yyparse(); 
imprime(dir_procs); 
fclose(objeto);
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

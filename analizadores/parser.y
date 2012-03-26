%{
#include <stdio.h>
#include <string.h>
#include <glib.h>

static GHashTable *dir_procs; //Directerio de Procedimientos
static GHashTable *tabla_constantes; //Tabla de constantes 
static GQueue *cuadruplos; //Tabla de cuadruplos se maneja como lista empezanod con el inidce 0
static char *proc_actual; //Procedimeitno actual mientras recorre sintaxis
static char tipo_actual; //Tipo actual de variables o procedimientos
static char *id_a_verificar; //Varibale utilizada para verificar la existencia del id
static int exp_operador_actual; //Variable utilizada en operaicones logicas con 2 simbolos
static int contador_cuadruplos = 1; //Contador de cuadruplos realizados
extern int yylineno;
//Declaracion de las pilas.
static GQueue *POperandos;
static GQueue *POperadores;
static GQueue *PTipos;
static GQueue *PSaltos;

//Declaración de rangos de memoria
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
Estructuras para las tabalas de procedimientos y tabla de variables
*/
typedef struct{
GHashTable *var_table;
char tipo;
GQueue *parametros;
}funcion;

typedef struct{
char tipo;
char *nombre;
int dir_virtual;
}variable;

typedef struct{
int dir_virtual;
}constante;

typedef struct{
int operador;
int operando1;
int operando2;
int destino;
}cuadruplo;

int traduce_tipo(char tipo);

/*
CUBO SEMÁNTICO
*/
char cubo[20][6][6] =
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
Descripción: Inicializa la tabla de dir_procs (directorio de procedimientos)

Parámetros: void
Salida:void
*/
void crear_pilas_tablas(){
	dir_procs = g_hash_table_new(g_str_hash, g_str_equal);
	tabla_constantes = g_hash_table_new(g_str_hash, g_str_equal);
	POperandos = g_queue_new();
	POperadores = g_queue_new();
	PTipos = g_queue_new();
	PSaltos = g_queue_new();
	cuadruplos = g_queue_new();
}

/*
Descripción: Función que se encarga de insertar un procedimiento, programa global
y la rutina principal

Parámetros: char * name
Salida:void
*/
void insert_proc_to_table(char *name){
	if(g_hash_table_lookup(dir_procs,(gpointer)name) != NULL){
		printf("Error: Función %s redeclarada en la línea %d\n",name,yylineno);
		exit(1);
	}else{
	funcion *temp = g_slice_new(funcion);
	temp->var_table = g_hash_table_new(g_str_hash, g_str_equal);
	temp->tipo = tipo_actual;
	g_hash_table_insert(dir_procs,(gpointer)name,(gpointer)temp);
	proc_actual = name;
	}
}	
/*
Descripción: Inserta una variable en el proceso actual en su tabla de 
variables correspondiente.

Parámetros: char *name
Salida:void
*/	
void insert_var_to_table(char *name){
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	//printf("%s", tabla->var_table);
	if(g_hash_table_lookup(tabla->var_table,(gpointer)name) != NULL){
		printf("Error: Variable %s redeclarada en la línea %d\n",name,yylineno);
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
		printf("ALta Variable: %s %d\n",name, virtual);
	}	
}
/*
Descripción: Verificar en la tabla de variables del procedimiento actual 
si existe la variable declarada(en la tabla). Regresa error de semántica
si no cumple.

Parámetros: char *name
Salida: void
*/
void verifica_existe_var(char *name){
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	variable *local = g_slice_new(variable);
	variable *global = g_slice_new(variable);
	local = g_hash_table_lookup(tabla->var_table,(gpointer)name);
	if(local == NULL){
		tabla = g_hash_table_lookup(dir_procs,"programa");
		global = g_hash_table_lookup(tabla->var_table,(gpointer)name);
		if(global == NULL){
			printf("Error: Variable %s no declarada en la línea\n",name,yylineno);
			exit(1);
		}else{
		  int tipot = traduce_tipo(global->tipo)+1;
		  g_queue_push_head(PTipos,tipot);
		  printf("Direccion Variable Global: %s %d\n",name, global->dir_virtual);
		  g_queue_push_head(POperandos,global->dir_virtual);
		}
	}else{
	  g_queue_push_head(PTipos,traduce_tipo(local->tipo)+1);
	  printf("Direccion Variable Local: %s %d\n",name, local->dir_virtual);
	  g_queue_push_head(POperandos,local->dir_virtual);
	}
}

/*
Descripción: Verificar en el directorio de procedimientos si existe el procedimiento
mandado como parámetro. Regresa error de semántica si no cumple.

Parámetros: char *name
Salida: void
*/
void verifica_existe_procs(char *name){
	if(g_hash_table_lookup(dir_procs,(gpointer)name) == NULL){
		printf("Error: Función %s no declarada en la línea %d\n",name,yylineno);
		exit(1);
	}
	
}

/*
Descripción: Función que se encarga de regresar el id numérico correspondiente
del tipo que se le está mandando como parámetro

Parámetros: char tipo
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
Descripción: Función que se encarga de regresar el string correspondiente
del tipo que se le está mandando como parámetros

Parámetros: int tipo
Salida: char *
*/
char* traduce_tipo2(int tipo){
	switch(tipo){
		case 1: return "entero";
		case 2: return "flotante";
		case 3: return "palabra";
		case 4: return "caracter";
		case 5: return "lógico";
	}

}
/*
Descripción: Función que se encarga de escribir en un archivo de código
objeto los cuádruplos que reciba.

Parámetros: int operador, int operando1, int operando2, int resultadotmp
Salida: void
*/
void generar_cuadruplo(int operador, int operando1, int operando2, int resultadotmp){
	cuadruplo *c = g_slice_new(cuadruplo);
	c->operador = operador;
	c->operando1 = operando1;
	c->operando2 = operando2;
	c->destino = resultadotmp;
	g_queue_push_tail(cuadruplos,(gpointer)c);
	
	//fprintf(objeto,"%d,%d,%d,%d\n",operador,operando1,operando2,resultadotmp);
	contador_cuadruplos++;
}

/*
Descripción: Función que se encarga de  regresar el operador al cual corresponde
dependiendo de los 2 últimos operadores. Aplica exclusiavmente para los 
operadores con 2 caracteres.

Parámetros: int operador1, int operador2
Salida: int
*/
int dame_operador_logico(int operador1, int operador2){
	if(operador1 == 9 && operador2 == 18){// 9 = .(concatenación), 18 = no(negación)
		return 11; // 11 = <>(diferente de)
	}else if(operador1 == 12 && operador2 == 18){// 12 = <= (menor o igual a)
		return 13;//13 = > (mayor que)
	}else if(operador1 == 18 && operador2 == 18){
		return 14; //14 = >= (mayor o igual)
	}
}

/*
Descripción: Función que se encarga de regresar si el operador es
de tipo lógico

Parámetros: int operador
Salida: int
*/
int valida_existencia_logico(int operador){
	if(operador >= 9 && operador <= 14){// 9 = .(concatenación), 14 = >= (mayor o igual)
		return 1;
	}else{
		return 0;
	}

}
/*
Descripción: Se encarga de obtener los operandos, tipos de operandos
y el operador para generar el cuádruplo

Parámetros: 
Salida: void
*/
void generar_cuadruplo_expresion(){
	int operando2 = (int)g_queue_pop_head(POperandos);
	printf("op2: %d ", operando2);
	int operando1 = (int)g_queue_pop_head(POperandos);
	printf("op1: %d ", operando1);
	int operador = (int)g_queue_pop_head(POperadores);
	printf("oper: %d ", operador);
	int tipo2 = g_queue_pop_head(PTipos);
	printf("tipo2: %d ", tipo2);
	int tipo1 = g_queue_pop_head(PTipos);
	printf("tipo1: %d\n", tipo1);
//	printf("op2: %d op1: %d oper: %d tipo1: %d tipo2: %d\n", operando2, operando1, operador, tipo1, tipo2);

	char tnuevo = cubo[operador-1][tipo1-1][tipo2-1];
	if(tnuevo == 'E'){
		printf("Error: No se puede hacer la operación entre %s y %s en la línea %d \n",traduce_tipo2(tipo1),traduce_tipo2(tipo2),yylineno);
		exit(1);
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
		switch(operador){
				case 3:
				case 6:{
					generar_cuadruplo(operador,operando1,operando2,tmp);
					generar_cuadruplo(19,tmp,-1,operando1);
				}break;
				default:{
					generar_cuadruplo(operador,operando1,operando2,tmp);
					g_queue_push_head(POperandos,tmp);	
					g_queue_push_head(PTipos,traduce_tipo(tnuevo)+1);
				}
		}
		
		
	}

}
/*
Descripción: Se encarga de obtener los operandos, tipos de operandos
y el operador para generar el cuádruplo para asignacionde variables. 
Asimismo durante la declaracion de variables se distingue por no usar
temporales.

Parámetros: 
Salida: void
*/
void generar_cuadruplo_asignacion(){
	int operando2 = (int)g_queue_pop_head(POperandos);
	printf("op2: %d ", operando2);
	int operando1 = (int)g_queue_pop_head(POperandos);
	printf("op1: %d ", operando1);
	int operador = (int)g_queue_pop_head(POperadores);
	printf("oper: %d ", operador);
	int tipo2 = g_queue_pop_head(PTipos);
	printf("tipo2: %d ", tipo2);
	int tipo1 = g_queue_pop_head(PTipos);
	printf("tipo1: %d\n", tipo1);
//	printf("op2: %d op1: %d oper: %d tipo1: %d tipo2: %d\n", operando2, operando1, operador, tipo1, tipo2);

	char tnuevo = cubo[operador-1][tipo1-1][tipo2-1];
	if(tnuevo == 'E'){//E es error
		printf("Error: No se puede hacer la asignación de %s a %s en la línea %d \n",traduce_tipo2(tipo2),traduce_tipo2(tipo1),yylineno);
		exit(1);
	}else{
		generar_cuadruplo(operador,operando2,-1,operando1);
		
	}
}
/*
Descripción: Se encarga de obtener el operando, tipos de operando
y el operador para generar el cuádruplo para expresiones de tipo unarias

Parámetros: 
Salida: void
*/
void generar_cuadruplo_expresion_unaria(){
	int operando1 = g_queue_pop_head(POperandos);
	printf("op1: %d ", operando1);
	int operador = g_queue_pop_head(POperadores);
	printf("oper: %d ", operador);
	int tipo1 = g_queue_pop_head(PTipos);
	printf("tipo1: %d\n", tipo1);

	if(operador == 1 || operador == 4){
		operador++;
	}

	char tnuevo = cubo[operador-1][tipo1-1][5];
	if(tnuevo == 'E'){// E es error
		printf("Error: No se puede hacer la operación con %s en la línea %d \n",traduce_tipo2(tipo1),yylineno);
		exit(1);
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
		switch(operador){
			case 2:
			case 5:{
				generar_cuadruplo(operador,operando1,1,tmp);
				generar_cuadruplo(19,tmp,-1,operando1);
			}break;
			default:{
				generar_cuadruplo(operador,operando1,-1,tmp);
				g_queue_push_head(POperandos,tmp);
				g_queue_push_head(PTipos,traduce_tipo(tnuevo)+1);
			}
		}	
	}
}
/*
Descripción:Funcion que se encarga de insertar las constantes a la 
tabla de constantes

Parámetros:int virtual, int tipo
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
		g_queue_push_head(PTipos,tipo);
		printf("Direccion Constante: %d %s\n", dir, valor);
		g_queue_push_head(POperandos,dir);
	}else{
		g_queue_push_head(PTipos,tipo);
		printf("Direccion Constante: %d %s\n", cte->dir_virtual, valor);
		g_queue_push_head(POperandos,cte->dir_virtual);
	}
}
/*
Descripción: Imprime el resultado de lo que se guardó en una tabla

Parámetros: GHashTable *a
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
vars_id: ID{id_a_verificar = yylval.str; insert_var_to_table(yylval.str);} varsip;
varsip: COMA vars_id
        | {verifica_existe_var(id_a_verificar);} IGUALR {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/} var_init {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	}
	var_initp
        | ;
var_init: lectura
          | mmexp;
var_initp: COMA vars_id
           | ;

funcion: FUNCION tipof ID{insert_proc_to_table(yylval.str);} APARENTESIS funcionpp CPARENTESIS ALLAVE funcionp CLLAVE;
tipof: tipo
	|  {tipo_actual= 'V';};
funcionp: estatutofuncion funcionp
	| ;
funcionpp: params 
	| ;

main: PRINCIPAL{insert_proc_to_table(yylval.str);} ALLAVE bloque CLLAVE;

bloque: estatuto bloque
	| ;

tipo:	 ENTERO {tipo_actual= 'I';}
	| FLOTANTE {tipo_actual= 'F';}
	| CARACTER {tipo_actual= 'C';}
	| PALABRA {tipo_actual= 'S';}
	| LOGICO {tipo_actual= 'L';};

varcte: CTE {insert_constante_to_table(yylval.integer,1);}
	| CTESTRING {insert_constante_to_table(yylval.str,3);}
	| CTF {insert_constante_to_table(yylval.str,2);}
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

asignacion: {verifica_existe_var(id_a_verificar);} asignacionp  PUNTOCOMA;
asignacionp: 	asigp
		| ap;
asigp: 		IGUALR {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/}lea {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	};
lea: 	lectura
		  |mmexp;

ap:		MAS{g_queue_push_head(POperadores,1);/*operador +*/} maiap
		|MENOS{g_queue_push_head(POperadores,4);/*operador -*/} miap;
maiap:		MAS{ generar_cuadruplo_expresion_unaria();}
		| IGUALR atipo {generar_cuadruplo_expresion();};
miap:		MENOS { generar_cuadruplo_expresion_unaria();}
		|IGUALR atipo{generar_cuadruplo_expresion();};

atipo:		CTE {insert_constante_to_table(yylval.integer,1);}
		| CTF {insert_constante_to_table(yylval.integer,2);}
		| ID{verifica_existe_var(yylval.str);};

condicion: c
	|  cp;
c:	SI APARENTESIS condicion_exp {
		int aux = g_queue_pop_head(PTipos);
		
		if(aux != 5){
			printf("Error: Se espera un valor lógico en la línea %d\n",yylineno);
			exit(1);
		}
		int resultado = g_queue_pop_head(POperandos);
		printf("Genera cuadruplo gotof\n");
		generar_cuadruplo(22,resultado,-1,-1);
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
		
		
	} CPARENTESIS ALLAVE bloque CLLAVE sip {
		int final = g_queue_pop_head(PSaltos);
		//printf("salto %d\n",final);
		//Rellenar GoTo con el contador de cuádruplos para el final
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,(guint)final-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,final-1);
	};
condicion_exp: mmexp
               | accionsi;
sip:	SINO{
		printf("Genera cuadruplo goto\n");
		generar_cuadruplo(21,-1,-1,-1);
		int falso = g_queue_pop_head(PSaltos);

		//Rellenar falso con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
	} sipp
	| ;
sipp: 	condicion
	| ALLAVE bloque CLLAVE;
cp: 	SELECCIONA APARENTESIS exp CPARENTESIS ALLAVE cuandop CLLAVE{
		//Regla 30
		int p;
		while(p = g_queue_pop_head(PSaltos)){
			cuadruplo *tmp = g_slice_new(cuadruplo);
			tmp = g_queue_pop_nth(cuadruplos,p-1);
			tmp->destino = contador_cuadruplos;
			g_queue_push_nth(cuadruplos,(gpointer)tmp,p-1);
		}
		//Sacar de Poperando y Ptipos la cte de comparacion
		g_queue_pop_head(POperandos);
		g_queue_pop_head(PTipos);
	};
cuandop: CUANDO varselecciona{
		//Regla 28
		g_queue_push_head(POperadores,15);
		int cte = g_queue_peek_nth(POperandos,1);
		int tipo = g_queue_peek_nth(PTipos,1);
		generar_cuadruplo_expresion();
		int tmp = g_queue_pop_head(POperandos);
		g_queue_pop_head(PTipos);
		printf("Genera cuadruplo gotof\n");
		generar_cuadruplo(22,tmp,-1,-1);
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
		//Volver a meter tipo y cte de comparacion
		g_queue_push_head(POperandos,cte);
		g_queue_push_head(PTipos,tipo);
		
	} IGUALR MAYORQUE ALLAVE bloque CLLAVE{
		//Regla29
		int falso = g_queue_pop_head(PSaltos);
		printf("Genera cuadruplo goto\n");
		generar_cuadruplo(21,-1,-1,-1);
		//Rellenar falso con contador_cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
	} cuandopp;
cuandopp: cuandop 
	| ;

escritura: ESCRIBE APARENTESIS escriturap CPARENTESIS{
		int operando1 = (int)g_queue_pop_head(POperandos);	
		int tipo1 = g_queue_pop_head(PTipos);
		generar_cuadruplo(25,operando1,-1,-1);
		} PUNTOCOMA;
escriturap: escriturapp { if(g_queue_peek_head(POperadores) == 9){
		printf("Genera cuadruplo .\n");
		generar_cuadruplo_expresion();		
		}} 
	e;
escriturapp: varcte 
	| exp;
e: 	CONCA {g_queue_push_head(POperadores,9);/*operador concatenacion(.)*/} escriturap
	| ;

lectura: LEE APARENTESIS CPARENTESIS {insert_constante_to_table("Lectura de pantalla",3);};

ciclo: MIENTRAS{g_queue_push_head(PSaltos,contador_cuadruplos); } APARENTESIS mmexp CPARENTESIS ALLAVE
	{ 	int aux = g_queue_pop_head(PTipos);
		
		if(aux != 5){
			printf("Error: Se espera un valor logico en la línea %d\n",yylineno);
			exit(1);
		}
		int resultado = g_queue_pop_head(POperandos);
		printf("Genera cuadruplo gotof\n");
		generar_cuadruplo(22,resultado,-1,-1);		
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
	} bloque CLLAVE {
		int falso = g_queue_pop_head(PSaltos);
		int retorno = g_queue_pop_head(PSaltos);
		generar_cuadruplo(21,-1,-1,retorno);
		//Rellenar falso con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
	};

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

mmexp: mexp {
  if(g_queue_peek_head(POperadores) == 17){
  			printf("Genera cuadruplo or \n");
			generar_cuadruplo_expresion();		
	}} mmexpp;
mmexpp: O {g_queue_push_head(POperadores,17);/*operador or*/} mmexp 
	| ;
	
mexp: expresion{
  if(g_queue_peek_head(POperadores) == 16){
  			printf("Genera cuadruplo and /\n");
			generar_cuadruplo_expresion();		
	}} mexpp;
mexpp: Y{g_queue_push_head(POperadores,16);/*operador and*/} mexp
	| ;
	
expresion: exp{
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
  			printf("Genera cuadruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	}} expresionp;
expresionp: ep expresion 
		| ;
ep: 	MAYORQUE{g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;}  epp
	|MENORQUE{g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;} epp
	| DIFERENTE{g_queue_push_head(POperadores,11);/*operador diferente*/}
	| IGUALR IGUALR  {g_queue_push_head(POperadores,15);/*operador igual igual*/} ;
epp: IGUALR {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		}
	| ;
	
exp: termino
  {if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	}} expp;
expp: MAS{g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/}  exp
	| MENOS{g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/}  exp 
	| ;

termino: factor
  {if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	}} 
	terminop;
terminop: POR{g_queue_push_head(POperadores,7);/*operador multiplica*/} termino
	| ENTRE{g_queue_push_head(POperadores,8);/*operador division*/} termino
	| ;

factor: factorp 
	| factorpp
	| factorppp;
factorp: nf APARENTESIS{g_queue_push_head(POperadores,'(');} mmexp CPARENTESIS {if(g_queue_peek_head(POperadores) == '('){
		g_queue_pop_head(POperadores);
		}else{
			printf("Mala construccion de expresion");
		};
		if(g_queue_peek_head(POperadores) == 18){
			printf("Genera cuadruplo not\n");
			generar_cuadruplo_expresion_unaria();
		}
		}
nf:	NO{g_queue_push_head(POperadores,18);/*operador NOT*/}
	|;
factorpp: f varcte {
  if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		printf("Genera cuadruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	};
f: 	MENOS {g_queue_push_head(POperadores,20);/*operador multiplica*/}
	| NO {g_queue_push_head(POperadores,18);/*operador NOT*/}
	| ;
factorppp: ID{id_a_verificar=yylval.str;} fun_var;
fun_var: APARENTESIS paramsf CPARENTESIS{verifica_existe_procs(id_a_verificar);}
         | {verifica_existe_var(id_a_verificar);
         	//Obteniendo el tipo de variable en la tabla d evariables
		/*
		funcion *tabla = g_slice_new(funcion);
		tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
		variable *var = g_slice_new(variable);
		var = g_hash_table_lookup(tabla->var_table,(gpointer)id_a_verificar);
		
		g_queue_push_head(POperandos,var->dir_virtual);
		g_queue_push_head(PTipos,traduce_tipo(var->tipo)+1);
		*/
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


//Escribir en el arhcivo los cuádruplos
cuadruplo *a = g_slice_new(cuadruplo);
while(a = g_queue_pop_head(cuadruplos)){
	fprintf(objeto,"%d,%d,%d,%d\n",a->operador,a->operando1,a->operando2,a->destino);
}

fclose(objeto);
free(dir_procs);
}

yyerror(char *s){
       printf("Error de sintaxis en la línea %d\n", yylineno);
}

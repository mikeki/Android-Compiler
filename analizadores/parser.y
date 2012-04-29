%{
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#define GPOINTER_TO_INT(p) ((gint)  (glong) (p))
#define GINT_TO_POINTER(i) ((gpointer) (glong) (i))


static GHashTable *dir_procs; //Directorio de procedimientos
static GHashTable *tabla_constantes; //Tabla de constantes 
static GQueue *cuadruplos; //Tabla de cuadruplos se maneja como lista empezando con el índice 0
static char *proc_actual; //Procedimiento actual mientras recorre sintaxis
static char tipo_actual; //Tipo actual de variables
static char tipo_funcion_actual;//Tipo actual de las funciones
static int bandera_return;//Bandera de retorno de funciones
static char *id_a_verificar; //Varibale utilizada para verificar la existencia del id
static int contador_cuadruplos = 1; //Contador de cuadruplos realizados
static int accion;
extern int yylineno;
static char *nombreobj;//El archivo obj tendrá el mismo nombre que el ID del programa

//Declaracion de las pilas.
static GQueue *POperandos;
static GQueue *POperadores;
static GQueue *PTipos;
static GQueue *PSaltos;
static GQueue *PSwitch;
static GQueue *PFunciones;
static GQueue *PParametros;

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
Estructuras para las tablas de procedimientos y tabla de variables
*/
typedef struct{
GHashTable *var_table;
char tipo;
GQueue *parametros;
int dir_inicial;
int tamano_locales[5];
int tamano_temporales[5];
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

typedef struct{
int operador;
char *operando1;
int operando2;
int destino;
}cuadruplofuncion;

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
		{//CONCATENACIÓN(.)
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
Descripción: Se encarga de escribir en el código objeto
el directorio de procedimientos. La función será utilizada en 
g_hash_table_foreach.
Entrada: char *key, char *value, gpointer user_data
Salida: void
*/
void imprime_dir_procs(char *key, funcion *value, gpointer user_data){
	funcion *f = value;

	fprintf(objeto,"%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",key,traduce_tipo(f->tipo),f->dir_inicial,f->tamano_locales[0],f->tamano_locales[1]
		,f->tamano_locales[2],f->tamano_locales[3],f->tamano_locales[4],f->tamano_temporales[0],f->tamano_temporales[1],
		f->tamano_temporales[2],f->tamano_temporales[3],f->tamano_temporales[4]);

	
}

/*
Descripción: Se encarga de escribir en el código objeto
la tabla de constantes. La función será utilizada en 
g_hash_table_foreach.
Entrada: char *key, char *value, gpointer user_data
Salida: void
*/
void imprime_tabla_constantes(char *key, constante *value, gpointer user_data){
	constante *c = value;

	fprintf(objeto,"%s,%d\n",key,c->dir_virtual);

	
}

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
	PSwitch = g_queue_new();
	PFunciones = g_queue_new();
	PParametros = g_queue_new();
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
	temp->parametros = g_queue_new();
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
void insert_var_to_table(char *name, char * proc){
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc);
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
			case 'I': if(strcmp(proc,"programa")== 0){
					virtual = enterosglobales;
					enterosglobales++;			
				} else{
					virtual = enteroslocales;
					enteroslocales++;
				}
				tabla->tamano_locales[0]++;
				break;
			case 'F': if(strcmp(proc,"programa")== 0){
					virtual = flotantesglobales;
					flotantesglobales++;			
				} else{
					virtual = flotanteslocales;
					flotanteslocales++;
				}
				tabla->tamano_locales[1]++;
				break;
			case 'S': if(strcmp(proc,"programa")== 0){
					virtual = stringsglobales;
					stringsglobales++;			
				} else{
					virtual = stringslocales;
					stringslocales++;
				}
				tabla->tamano_locales[2]++;
				break;
			case 'C': if(strcmp(proc,"programa")== 0){
					virtual = caracteresglobales;
					caracteresglobales++;			
				} else{
					virtual = caractereslocales;
					caractereslocales++;
				}
				tabla->tamano_locales[3]++;
				break;
			case 'L': if(strcmp(proc,"programa")== 0){
					virtual = logicosglobales;
					logicosglobales++;			
				} else{
					virtual = logicoslocales;
					logicoslocales++;
				}
				tabla->tamano_locales[4]++;
				break;
		}
		temp->dir_virtual = virtual;
		g_hash_table_insert(tabla->var_table,(gpointer)name,(gpointer)temp);
		g_hash_table_foreach(tabla->var_table,(GHFunc)printf,NULL);
		printf("Alta variable: %s %d\n",name, virtual);
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
		  g_queue_push_head(PTipos,GINT_TO_POINTER(tipot));
		  printf("Dirección variable global: %s %d\n",name, global->dir_virtual);
		  g_queue_push_head(POperandos,GINT_TO_POINTER(global->dir_virtual));
		}
	}else{
	  g_queue_push_head(PTipos,GINT_TO_POINTER(traduce_tipo(local->tipo)+1));
	  printf("Dirección variable local: %s %d\n",name, local->dir_virtual);
	  g_queue_push_head(POperandos,GINT_TO_POINTER(local->dir_virtual));
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
Descripción: Inserta el procedieminto en la pila de operandos, asimismo inserta 
el tipo correspondiente.
Parámetros: char *name
Salida: void
*/
void inserta_procs_factor(char *name, int tmp){
	funcion *f = g_hash_table_lookup(dir_procs,(gpointer)name);
	printf("Tipo en factor: %c\n",f->tipo);
	if(f->tipo == 'V'){//Valida si un modulo llamdo en la expresion es de tipo void
		printf("Error: Expresión inválida en la línea %d\n",yylineno);
		exit(1);
	}
	funcion *proc_global = g_hash_table_lookup(dir_procs,"programa");
	variable *modulo = g_hash_table_lookup(proc_global->var_table,(gpointer)name);
	g_queue_push_head(POperandos,GINT_TO_POINTER(tmp));
	g_queue_push_head(PTipos,GINT_TO_POINTER(traduce_tipo(modulo->tipo)+1));
	printf("Dirección variable global: %s %d\n",name, modulo->dir_virtual);
	
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
		case 'V': return 5;
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
		case 6: return "void";
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
Descripción: Función que se encarga de escribir en un archivo de código
objeto los cuádruplos que reciba de tipo función.
Parámetros: int operador, char *operando1, int operando2, int resultadotmp
Salida: void
*/
void generar_cuadruplo_funcion(int operador, char *operando1, int operando2, int resultadotmp){
	cuadruplofuncion *c = g_slice_new(cuadruplofuncion);
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
	if(operador1 == 10 && operador2 == 19){//(menor o igual a)
		return 12;// (<=) Menor Igual
	}else if(operador1 == 13 && operador2 == 19){
		return 14; //(>=) Mayor Igual
	}
}

/*
Descripción: Función que se encarga de regresar si el operador es
de tipo lógico
Parámetros: int operador
Salida: int
*/
int valida_existencia_logico(int operador){
	if(operador >= 10 && operador <= 15){// 10 = (<), 15 == (igual igual)
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
	int operando2 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	printf("op2: %d ", operando2);
	int operando1 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	printf("op1: %d ", operando1);
	int operador = GPOINTER_TO_INT(g_queue_pop_head(POperadores));
	printf("oper: %d ", operador);
	int tipo2 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
	printf("tipo2: %d ", tipo2);
	int tipo1 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
	printf("tipo1: %d\n", tipo1);
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
//	printf("op2: %d op1: %d oper: %d tipo1: %d tipo2: %d\n", operando2, operando1, operador, tipo1, tipo2);

	char tnuevo = cubo[operador-1][tipo1-1][tipo2-1];
	if(tnuevo == 'E'){
		printf("Error: No se puede hacer la operación entre %s y %s en la línea %d \n",traduce_tipo2(tipo1),
			traduce_tipo2(tipo2),yylineno);
		exit(1);
	}else{
		int tmp;
		switch(tnuevo){
			case 'I': tmp = enterostemporales;
				enterostemporales++;
				tabla->tamano_temporales[0]++;
				break;
			case 'F': tmp = flotantestemporales;
				flotantestemporales++;
				tabla->tamano_temporales[1]++;
				break;
			case 'S': tmp = stringstemporales;
				stringstemporales++;
				tabla->tamano_temporales[2]++;
				break;
			case 'C': tmp = caracterestemporales;
				caracterestemporales++;
				tabla->tamano_temporales[3]++;
				break;
			case 'L': tmp = logicostemporales;
				logicostemporales++;
				tabla->tamano_temporales[4]++;
				break;
		}
		switch(operador){
				case 3:
				case 6:{
				  g_queue_pop_head(POperadores);
					generar_cuadruplo(operador,operando1,operando2,operando1);
				}break;
				default:{
					generar_cuadruplo(operador,operando1,operando2,tmp);
					g_queue_push_head(POperandos,GINT_TO_POINTER(tmp));	
					g_queue_push_head(PTipos,GINT_TO_POINTER(traduce_tipo(tnuevo)+1));
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
	int operando2 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	printf("op2: %d ", operando2);
	int operando1 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	printf("op1: %d ", operando1);
	int operador = GPOINTER_TO_INT(g_queue_pop_head(POperadores));
	printf("oper: %d ", operador);
	int tipo2 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
	printf("tipo2: %d ", tipo2);
	int tipo1 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
	printf("tipo1: %d\n", tipo1);
//	printf("op2: %d op1: %d oper: %d tipo1: %d tipo2: %d\n", operando2, operando1, operador, tipo1, tipo2);

	char tnuevo = cubo[operador-1][tipo1-1][tipo2-1];
	if(tnuevo == 'E'){//E es error
		printf("Error: No se puede hacer la asignación de %s a %s en la línea %d \n",traduce_tipo2(tipo2),
			traduce_tipo2(tipo1),yylineno);
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
	int operando1 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	printf("op1: %d ", operando1);
	int operador = GPOINTER_TO_INT(g_queue_pop_head(POperadores));
	printf("oper: %d ", operador);
	int tipo1 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
	printf("tipo1: %d\n", tipo1);
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	if(operador == 1 || operador == 4){//Indica si es ++ o --
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
				tabla->tamano_temporales[0]++;
				break;
			case 'F': tmp = flotantestemporales;
				flotantestemporales++;
				tabla->tamano_temporales[1]++;
				break;
			case 'S': tmp = stringstemporales;
				stringstemporales++;
				tabla->tamano_temporales[2]++;
				break;
			case 'C': tmp = caracterestemporales;
				caracterestemporales++;
				tabla->tamano_temporales[3]++;
				break;
			case 'L': tmp = logicostemporales;
				logicostemporales++;
				tabla->tamano_temporales[4]++;
				break;
		}
		switch(operador){
			case 2:
			case 5:{
				generar_cuadruplo(operador,operando1,-1,operando1);
			}break;
			default:{
				generar_cuadruplo(operador,operando1,-1,tmp);
				g_queue_push_head(POperandos,GINT_TO_POINTER(tmp));
				g_queue_push_head(PTipos,GINT_TO_POINTER(traduce_tipo(tnuevo)+1));
			}
		}	
	}
}

/*
Descripción: Se encarga de generar el cuádruplo 
para la acción de ver pista.
Parámetros: 
Salida: void
*/
void generar_cuadruplo_verpista(){
	int operador = 37;
	printf("oper: %d ", operador);
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	int tmp;
	tmp = enterostemporales;
	enterostemporales++;
	tabla->tamano_temporales[0]++;	
	generar_cuadruplo(operador,-1,-1,tmp);
	g_queue_push_head(POperandos,GINT_TO_POINTER(tmp));
	g_queue_push_head(PTipos,GINT_TO_POINTER(1));			
}

/*
Descripción: Se encarga de generar el cuádruplo 
para la acción con Destino temporal.
Parámetros: int accion 
Salida: void
*/
void generar_cuadruplo_accion_expresion(int accion){
	int operador = accion;
	printf("oper: %d ", operador);
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	int tmp;
	tmp = logicostemporales;
	logicostemporales++;
	tabla->tamano_temporales[4]++;	
	generar_cuadruplo(operador,-1,-1,tmp);
	g_queue_push_head(POperandos,GINT_TO_POINTER(tmp));
	g_queue_push_head(PTipos,GINT_TO_POINTER(5));			
}

/*
Descripción: Se encarga de generar el cuádruplo 
para la acción con Destino temporal.
Parámetros: int accion
Salida: void
*/
void generar_cuadruplo_accionsi(int accion){
	int operador = accion;
	printf("oper: %d ", operador);
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	int tmp;
	tmp = logicostemporales;
	logicostemporales++;
	tabla->tamano_temporales[4]++;	
	generar_cuadruplo(operador,-1,-1,tmp);
	g_queue_push_head(POperandos,GINT_TO_POINTER(tmp));
	g_queue_push_head(PTipos,GINT_TO_POINTER(5));			
}

/*
Descripción: Función que se encarga de insertar las constantes a la 
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
		g_queue_push_head(PTipos,GINT_TO_POINTER(tipo));
		printf("Dirección constante: %d %s\n", dir, valor);
		g_queue_push_head(POperandos,GINT_TO_POINTER(dir));
	}else{
		g_queue_push_head(PTipos,GINT_TO_POINTER(tipo));
		printf("Dirección constante: %d %s\n", cte->dir_virtual, valor);
		g_queue_push_head(POperandos,GINT_TO_POINTER(cte->dir_virtual));
	}
}

/*
Descripción: Meter el tipo del parámetro en el procedimiento actual del directorio
de procedimientos en la secuencia de parámetros en la lista de parámetros.
Entrada: 
Salida: void
*/
void insert_param_tipo(){
	funcion *proc = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	g_queue_push_tail(proc->parametros,GINT_TO_POINTER(traduce_tipo(tipo_actual)+1));
	//printf("Se agrego a parametos: %d\n",g_queue_peek_nth(proc->parametros,0));
	//g_queue_foreach(proc->parametros,(GHFunc)printf,NULL);
}

/*
Descripción: Método que se encarga de introducir en el dir. de procedimientos
el cuádruplo siguiente.
Entrada: 
Salida: void
*/
void insert_dir_inicial(){
	funcion *proc = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	
	proc->dir_inicial = contador_cuadruplos;	
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
%token ADELANTE ATRAS ROTADERECHA ROTAIZQUIERDA TOMARTESORO TOPA TOPADERECHA TOPAIZQUIERDA
%token VERPISTA SI SINO MIENTRAS FUNCION ENTERO FLOTANTE SELECCIONA CUANDO
%token REGRESA LOGICO PALABRA ESCRIBE LEE PRINCIPAL VERDADERO FALSO
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

programa: {}PROGRAMA ID{nombreobj = yylval.str;//Nombre del programa
/* Regla 48*/tipo_actual = 'V'; /*Regla 101*/insert_proc_to_table("programa"); /*Regla 33*/ insert_dir_inicial();/*Regla 43*/generar_cuadruplo(21,-1,-1,-1);/*goto del main*/ } IGUALP programap main;
programap: programapp programappp;
programapp: 	vars programapp
		| ;
programappp: funcion programappp
		| ;

vars: tipo vars_id PUNTOCOMA;
vars_id: ID{/*Regla 103 y 32*/id_a_verificar = yylval.str; insert_var_to_table(yylval.str,proc_actual);} varsip;
varsip: COMA vars_id
        | {/*Regla 1*/verifica_existe_var(id_a_verificar);} IGUALR {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(19));/*operador asigancion(=)*/} var_init {
		//Regla 3
		printf("Genera cuádruplo =\n");
		generar_cuadruplo_asignacion();	}
	var_initp
        | ;
var_init: lectura
          | mmexp;
var_initp: COMA vars_id
           | ;

funcion: FUNCION tipof ID{
	//Regla 101
	insert_proc_to_table(yylval.str);
	//Regla 35
	bandera_return = 0;
	/*Regla 46*/ 
	if(tipo_funcion_actual != 'V'){
		insert_var_to_table(proc_actual,"programa");
	}
	} APARENTESIS funcionpp CPARENTESIS ALLAVE {/*Regla 33*/insert_dir_inicial();} funcionv funcionp CLLAVE{
	//Regla 34
	//Locales
	enteroslocales = 210000;
	flotanteslocales = 220000;
	stringslocales = 230000;
	caractereslocales = 240000;
	logicoslocales = 250000;

	//Temporales
	enterostemporales = 310000;
	flotantestemporales = 320000;
	stringstemporales = 330000;
	caracterestemporales = 340000;
	logicostemporales = 350000;

	//Verificar si hubo return
	if(bandera_return == 0 && tipo_funcion_actual != 'V'){
		printf("Error: En la función %s no contiene regresa \n",proc_actual);
		exit(1);
	}
	if(tipo_funcion_actual == 'V' && bandera_return == 1){
		printf("Error: En la función %s no debe haber regresa\n",proc_actual);
		exit(1);
	}

	//Generar cuadruplo de RET
	
	printf("Genera cuádruplo RET\n");
	generar_cuadruplo(27,-1,-1,-1);
	
	};
funcionv: 	vars funcionv
		|;
tipof: tipo{//Regla 49
		tipo_funcion_actual = tipo_actual;
		}
	|  { 	//Regla 48
		tipo_funcion_actual= 'V';
		tipo_actual = 'V';};
funcionp: estatutofuncion funcionp
	| ;
funcionpp: params 
	| ;

main: PRINCIPAL{/* Regla 48*/tipo_actual = 'V';
		/*Regla 101*/insert_proc_to_table(yylval.str);
		/*Regla 33*/insert_dir_inicial();
		//Regla 35
		bandera_return = 0;
		} ALLAVE{
		//Regla 50
		//Rellenar goto inicial del main con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_peek_nth(cuadruplos,0);
		tmp->destino = contador_cuadruplos;
		} mainv bloque CLLAVE
		{
		
		//Verificar si hubo return
		if(bandera_return == 1){
			printf("Error: En principal no debe haber regresa\n");
			exit(1);
		}
		}
		;
mainv: 		vars mainv
		|;
bloque: estatutofuncion bloque
	| ;

tipo:	 ENTERO {/*Regla 102*/tipo_actual= 'I';}
	| FLOTANTE {/*Regla 102*/tipo_actual= 'F';}
	| CARACTER {/*Regla 102*/tipo_actual= 'C';}
	| PALABRA {/*Regla 102*/tipo_actual= 'S';}
	| LOGICO {/*Regla 102*/tipo_actual= 'L';};

varcte: CTE {/*Regla 16*/insert_constante_to_table(yylval.integer,1);}
	| CTESTRING {/*Regla 16*/insert_constante_to_table(yylval.str,3);}
	| CTF {/*Regla 16*/insert_constante_to_table(yylval.str,2);}
	| CAR {/*Regla 16*/insert_constante_to_table(yylval.str,4);}
	| VERPISTA APARENTESIS CPARENTESIS{/*Regla 31*/generar_cuadruplo_verpista(); }
	| VERDADERO{/*Regla 16*/insert_constante_to_table(yylval.str,5);}
	| FALSO{/*Regla 16*/insert_constante_to_table(yylval.str,5);};

estatutofuncion: estatuto
		|regresa;

estatuto: empieza_id
		|condicion
		|escritura
		|ciclo
		|accion;
		
empieza_id: ID{/*Regla 17*/id_a_verificar=yylval.str;} empieza_idp;
empieza_idp: ejecuta_funcion
            | asignacion;

ejecuta_funcion:  APARENTESIS{
			/*Regla 105*/
			verifica_existe_procs(id_a_verificar);
						
			//Regla 36
			g_queue_push_head(PFunciones,id_a_verificar);
			//ERA
			generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
			g_queue_push_head(PParametros,GINT_TO_POINTER(0));
			
			} paramsf CPARENTESIS{
			//Regla 39
			char *func = g_queue_peek_head(PFunciones);
			funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)func);
	
			g_queue_pop_head(PFunciones);
			int contador_parametros = GPOINTER_TO_INT(g_queue_pop_head(PParametros));
			if(g_queue_get_length(ft->parametros) != contador_parametros){
				printf("Error: Menos parámetros de los esperados en la linea %d\n",yylineno);
				exit(1);
			}
			//Regla 40
			//GOSUB
			printf("Genera cuádruplo GOSUB \n");
			//printf("Tipo: %c \n",ft->tipo);
			
			generar_cuadruplo_funcion(24,func,ft->dir_inicial,-1);
			} PUNTOCOMA;

paramsf: params2
          | ;

regresa: REGRESA{/*Regla 44*/bandera_return = 1;} mmexp {
	//Regla 45
	int expresion = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	int tipoexp = GPOINTER_TO_INT(g_queue_pop_head(PTipos)) - 1;

	if(tipo_funcion_actual == 'V'){
		printf("Error: En la función %s no debe haber regresa\n",proc_actual);
		exit(1);
	}
	
	if(tipoexp != traduce_tipo(tipo_funcion_actual)){
		printf("Error: Se espera un valor de tipo %s en el regresa en la linea %d\n",traduce_tipo2(traduce_tipo(tipo_funcion_actual) + 1),yylineno);
		exit(1);
	}

	//Generar cuadruplo de RETURN
	printf("Genera cuádruplo RETURN\n");
	generar_cuadruplo(35,expresion,-1,-1);

	//Generar cuadruplo de asignacion
	//obtener dir virtual de la golab de la funcion
	char *p = "programa";
	funcion *tabla = g_hash_table_lookup(dir_procs,p);
	g_hash_table_foreach(tabla->var_table,(GHFunc)printf,NULL);
	variable *global = g_slice_new(variable);
	global = g_hash_table_lookup(tabla->var_table,(gpointer)proc_actual);
	//printf("Direccion Variable Global: %s %d\n",proc_actual, global->dir_virtual);
	  //printf("Hola\n");
	
	char tnuevo = cubo[19-1][traduce_tipo(tipo_funcion_actual)][tipoexp];
	if(tnuevo == 'E'){//E es error
		printf("Error: Se espera un valor de tipo %s en el regresa en la línea %d\n",traduce_tipo2(traduce_tipo(tipo_funcion_actual) + 1),yylineno);
		exit(1);
	}
	
	}PUNTOCOMA;

asignacion: {/*Regla 104*/verifica_existe_var(id_a_verificar);} asignacionp  PUNTOCOMA;
asignacionp: 	asigp
		| ap;
asigp: 		IGUALR {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(19));/*operador asigancion(=)*/}lea {
		//Regla 3
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	};
lea: 	lectura
		  |mmexp;

ap:		MAS{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(1));/*operador +*/} maiap
		|MENOS{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(4));/*operador -*/} miap;
maiap:		MAS{/*Regla 4*/generar_cuadruplo_expresion_unaria();}
		| IGUALR {verifica_existe_var(id_a_verificar); g_queue_push_head(POperadores,GINT_TO_POINTER(3));} atipo {/*Regla 5*/generar_cuadruplo_expresion();};
miap:		MENOS {/*Regla 4*/ generar_cuadruplo_expresion_unaria();}
		|IGUALR{verifica_existe_var(id_a_verificar); g_queue_push_head(POperadores,GINT_TO_POINTER(6));} atipo{/*Regla 5*/generar_cuadruplo_expresion();};

atipo:		CTE {/*Regla 16*/insert_constante_to_table(yylval.integer,1);}
		| CTF {/*Regla 16*/insert_constante_to_table(yylval.integer,2);}
		| ID{/*Regla 104*/verifica_existe_var(yylval.str);};

condicion: c
	|  cp;
c:	SI APARENTESIS condicion_exp {
		//Regla 20
		int aux = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
		
		if(aux != 5){
			printf("Error: Se espera un valor lógico en la línea %d\n",yylineno);
			exit(1);
		}
		int resultado = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
		printf("Genera cuádruplo GoToF\n");
		generar_cuadruplo(22,resultado,-1,-1);
		g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos-1));
		
		
	} CPARENTESIS ALLAVE bloque CLLAVE sip {
		//Regla 22
		int final = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		//Rellenar GoTo con el contador de cuádruplos para el final
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,(guint)final-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,final-1);
	};
condicion_exp: mmexp
		| accionsi;
sip:	SINO{
		//Regla 21
		printf("Genera cuádruplo GoTo\n");
		generar_cuadruplo(21,-1,-1,-1);
		int falso = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));

		//Rellenar falso con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
		g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos-1));
	} sipp
	| ;
sipp: 	condicion
	| ALLAVE bloque CLLAVE;
cp: 	SELECCIONA APARENTESIS exp CPARENTESIS ALLAVE{
		//Regla 42
		g_queue_push_head(PSwitch,GINT_TO_POINTER(0));		
		} cuandop CLLAVE{
		//Regla 30
		int p;
		int acum = GPOINTER_TO_INT(g_queue_pop_head(PSwitch));
		int i = 0;
		while(i < acum){
			p = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
			cuadruplo *tmp = g_slice_new(cuadruplo);
			tmp = g_queue_pop_nth(cuadruplos,p-1);
			tmp->destino = contador_cuadruplos;
			g_queue_push_nth(cuadruplos,(gpointer)tmp,p-1);
			i++;
		}
		//Sacar de Poperando y Ptipos la cte de comparacion
		g_queue_pop_head(POperandos);
		g_queue_pop_head(PTipos);
	};
cuandop: CUANDO varselecciona{
		//Regla 28
		g_queue_push_head(POperadores,GINT_TO_POINTER(15));
		int cte = GPOINTER_TO_INT(g_queue_peek_nth(POperandos,1));
		int tipo = GPOINTER_TO_INT(g_queue_peek_nth(PTipos,1));
		generar_cuadruplo_expresion();
		int tmp = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
		g_queue_pop_head(PTipos);
		printf("Genera cuádruplo GoToF\n");
		generar_cuadruplo(22,tmp,-1,-1);
		g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos-1));
		//Volver a meter tipo y cte de comparacion
		g_queue_push_head(POperandos,GINT_TO_POINTER(cte));
		g_queue_push_head(PTipos,GINT_TO_POINTER(tipo));
		
	} IGUALR MAYORQUE ALLAVE bloque CLLAVE{
		//Regla29
		int falso = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		printf("Genera cuádruplo GoTo\n");
		generar_cuadruplo(21,-1,-1,-1);
		//Rellenar falso con contador_cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
		g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos-1));
		//Regla 51
		int acum = GPOINTER_TO_INT(g_queue_pop_head(PSwitch));
		acum++;
		g_queue_push_head(PSwitch,GINT_TO_POINTER(acum));
	} cuandopp;
cuandopp: cuandop 
	| ;

escritura: ESCRIBE APARENTESIS escriturap CPARENTESIS{
		//Regla 26
		int operando1 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));	
		int tipo1 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
		printf("Genera cuádruplo de escribe\n");
		generar_cuadruplo(34,operando1,-1,-1);
		} PUNTOCOMA;
escriturap: exp { 
		//Regla 27
		if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 9){
		printf("Genera cuádruplo .\n");
		generar_cuadruplo_expresion();		
		}} 
		e;
e: 	CONCA {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(9));/*operador concatenacion(.)*/} escriturap
	| ;

lectura: LEE APARENTESIS CPARENTESIS {/*Regla 16*/insert_constante_to_table("Lectura de pantalla",3);};

ciclo: MIENTRAS{/* Regla 23*/g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos)); } APARENTESIS mmexp CPARENTESIS ALLAVE
	{ 	//Regla 24
		int aux = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
		
		if(aux != 5){
			printf("Error: Se espera un valor lógico en la línea %d\n",yylineno);
			exit(1);
		}
		int resultado = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
		printf("Genera cuádruplo GoToF\n");
		generar_cuadruplo(22,resultado,-1,-1);		
		g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos-1));
	} bloque CLLAVE {
		//Regla 25
		int falso = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		int retorno = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		generar_cuadruplo(21,-1,-1,retorno);
		//Rellenar falso con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
	};

accion: acciones{
	//Regla 41
	printf("Genera cuádruplo de acción\n");
	generar_cuadruplo(accion,-1,-1,-1);
	} APARENTESIS CPARENTESIS PUNTOCOMA;
	
accionsi: acciones{
	//Regla 18
	printf("Genera cuádruplo de acción\n");
	generar_cuadruplo_accionsi(accion);
	
	} APARENTESIS CPARENTESIS;
acciones: ADELANTE{/*Regla 52*/accion = 28;}
	| ATRAS{/*Regla 52*/accion = 29;}
	| ROTADERECHA{/*Regla 52*/accion = 30;}
	| ROTAIZQUIERDA{/*Regla 52*/accion = 31;}
	| TOMARTESORO{/*Regla 52*/accion = 32;}
	| TOPA{/*Regla 52*/accion = 33;}
	| TOPADERECHA{/*Regla 52*/accion = 38;}
	| TOPAIZQUIERDA{/*Regla 52*/accion = 39;};

params: tipo paramsp;
paramsp: ID{/*Regla 19*/insert_param_tipo();/*Regla 103*/insert_var_to_table(yylval.str,proc_actual);} paramspp;
paramspp: COMA params
	| ;
params2: exp{ 
	
	//Regla 37
	
	int argumento = GPOINTER_TO_INT(g_queue_pop_head(POperandos));
	int tipoarg = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
	
	funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)g_queue_peek_head(PFunciones));
	int contador_parametros = GPOINTER_TO_INT(g_queue_peek_head(PParametros));
	if(g_queue_get_length(ft->parametros) < contador_parametros + 1){
				printf("Error: Mas parámetros de los esperados en la linea %d\n",yylineno);
				exit(1);
			}
	
	int tipoparam = GPOINTER_TO_INT(g_queue_peek_nth(ft->parametros,contador_parametros));
	printf("Argumento y tipoarg, tipoparam: %d,%d,%d\n",argumento,tipoarg,tipoparam);
	
	if(tipoarg != tipoparam){
		printf("Error: Se espera un valor %s en la línea %d\n",traduce_tipo2(tipoparam),yylineno);
		exit(1);
	}
	//Generar cuadruplo parametro
	printf("Genera cuádruplo parámetro \n");
	generar_cuadruplo(26,argumento,contador_parametros,-1);
	//Regla 38
	int p = GPOINTER_TO_INT(g_queue_pop_head(PParametros));
	p++;
	g_queue_push_head(PParametros,GINT_TO_POINTER(p));
	} params2p;
params2p: COMA params2
	| ;

mmexp: mexp {
	//Regla 9
	  if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 17){
  			printf("Genera cuádruplo or \n");
			generar_cuadruplo_expresion();		
	}} mmexpp;
mmexpp: O {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(17));/*operador or*/} mmexp 
	| ;
	
mexp: expresion{
	//Regla 8
  if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 16){
  			printf("Genera cuádruplo and /\n");
			generar_cuadruplo_expresion();		
	}} mexpp;
mexpp: Y{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(16));/*operador and*/} mexp
	| ;
	
expresion: exp{
	//Regla 7
  if(valida_existencia_logico(GPOINTER_TO_INT(g_queue_peek_head(POperadores)))){
  			printf("Genera cuádruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	}} expresionp;
expresionp: ep expresion 
		| ;
ep: 	MAYORQUE{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(13));/*operador mayorque*/}  epp
	|MENORQUE{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(10));/*operador menorque*/} epp
	| DIFERENTE{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(11));/*operador diferente*/}
	| IGUALR IGUALR  {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(15));/*operador igual igual*/} ;
epp: IGUALR {
		//Regla 6
		int operadoranterior = GPOINTER_TO_INT(g_queue_pop_head(POperadores));
		int operadorreal = dame_operador_logico(operadoranterior,19);
		g_queue_push_head(POperadores,GINT_TO_POINTER(operadorreal));
		}
	| ;
	
exp: termino
  {	//Regla 10
  	if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 1 || GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 4){
		printf("Genera cuádruplo + o -\n");
		generar_cuadruplo_expresion();		
	}} expp;
expp: MAS{ /*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(1));printf("Push +\n");/*operador suma*/}  exp
	| MENOS{ /*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(4));printf("Push -\n");/*operador resta*/}  exp 
	| ;

termino: factor
  {	//Regla 11
  	if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 7 || GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 8){
    	printf("Genera cuádruplo * o /\n");
		generar_cuadruplo_expresion();		
	}} 
	terminop;
terminop: POR{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(7));/*operador multiplica*/} termino
	| ENTRE{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(8));/*operador division*/} termino
	| ;

factor: factorp 
	| factorpp
	| factorppp
	| factorpppp;
factorp: nf APARENTESIS{/*Regla 12*/g_queue_push_head(POperadores,GINT_TO_POINTER('('));} mmexp CPARENTESIS {
		/*Regla 13*/
		if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == '('){
			g_queue_pop_head(POperadores);
		}else{
			printf("Error: Mala construcción de expresión en la línea %d\n",yylineno);
			exit(1);
		}
		//Regla 14
		if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 18){
			printf("Genera cuádruplo not\n");
			generar_cuadruplo_expresion_unaria();
		}
		};
nf:	NO{/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(18));/*operador NOT*/}
	|;
factorpp: f varcte {
	//Regla 15
  	if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 18 || GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 20){
		printf("Genera cuádruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	};
f: 	MENOS {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(20));/*operador multiplica*/}
	| NO {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(18));/*operador NOT*/}
	| ;
factorppp: ID{/*Regla 17*/id_a_verificar=yylval.str;} fun_var;
fun_var: APARENTESIS{
		//Regla 105
		verifica_existe_procs(id_a_verificar);
		//Regla 36
		g_queue_push_head(PFunciones,id_a_verificar);
		printf("Genera cuádruplo de función: %s \n",id_a_verificar);
		generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
		g_queue_push_head(PParametros,GINT_TO_POINTER(0));
		g_queue_push_head(POperadores,GINT_TO_POINTER('('));
			
	} paramsf CPARENTESIS{
		//verifica_existe_procs(id_a_verificar);
		//Regla 39
		char *func = g_queue_peek_head(PFunciones);
		funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)func);
		funcion *factual = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
    
		g_queue_pop_head(PFunciones);
		int contador_parametros = GPOINTER_TO_INT(g_queue_pop_head(PParametros));
		if(g_queue_get_length(ft->parametros) != contador_parametros){
			printf("Error: Menos parámetros de los esperados en la linea %d\n",yylineno);
			exit(1);
		}
		//Regla 40 
		//GENERAR GOSUB
		printf("Genera cuádruplo GOSUB \n");
		int tmp;
		switch(ft->tipo){
			case 'I': tmp = enterostemporales;
				enterostemporales++;
				factual->tamano_temporales[0]++;
				break;
			case 'F': tmp = flotantestemporales;
				flotantestemporales++;
				factual->tamano_temporales[1]++;
				break;
			case 'S': tmp = stringstemporales;
				stringstemporales++;
				factual->tamano_temporales[2]++;
				break;
			case 'C': tmp = caracterestemporales;
				caracterestemporales++;
				factual->tamano_temporales[3]++;
				break;
			case 'L': tmp = logicostemporales;
				logicostemporales++;
				factual->tamano_temporales[4]++;
				break;
		}
		generar_cuadruplo_funcion(24,func,ft->dir_inicial,tmp);

		//Regla 47
		inserta_procs_factor(func,tmp);

		//SE saca el fondo falso
		g_queue_pop_head(POperadores);
	}
         | {	//Regla 1
         	verifica_existe_var(id_a_verificar);
         	
         	};

factorpppp: nf accionsi {
		//Regla 53
		//printf("Generar cuadruplo de accion \n");
		//generar_cuadruplo_accion_expresion(accion);

		if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 18){
			printf("Genera cuádruplo not o - \n");
			generar_cuadruplo_expresion_unaria();
		}
		};
	
varselecciona: ID{/*Regla 104*/verifica_existe_var(yylval.str);}
		|CTE {/*Regla 16*/insert_constante_to_table(yylval.integer,1);}
		|CAR {/*Regla 16*/insert_constante_to_table(yylval.str,4);};
 

%% 
main() { 
crear_pilas_tablas();
  yyparse(); 
  objeto = fopen(strcat(nombreobj,".roid"), "w");
//Impresion del directorio de procedimientos en consola
imprime(dir_procs); 

//Generar cuadruplo final END
generar_cuadruplo(36,-1,-1,-1);


//Escribir el directorio de procedimientos
g_hash_table_foreach(dir_procs,(GHFunc)imprime_dir_procs,NULL);


fprintf(objeto,"--\n");
//Escribir en el archivo la tabla de constantes
g_hash_table_foreach(tabla_constantes,(GHFunc)imprime_tabla_constantes,NULL);
fprintf(objeto,"--\n");

//Escribir en el archivo los cuádruplos
cuadruplo *a = g_slice_new(cuadruplo);
cuadruplofuncion *b = g_slice_new(cuadruplofuncion);
cuadruplo *fin = g_slice_new(cuadruplo);
fin = g_queue_peek_head(cuadruplos);


while(fin){
	a = g_queue_peek_head(cuadruplos);
	if(a->operador == 24 || a->operador == 25){
		b = g_queue_pop_head(cuadruplos);
		//printf("cuadruplo funcion\n");
		fprintf(objeto,"%d,%s,%d,%d\n",b->operador,b->operando1,b->operando2,b->destino);	
	}else{
		a = g_queue_pop_head(cuadruplos);
		//printf("cuadruplo normal\n");
		fprintf(objeto,"%d,%d,%d,%d\n",a->operador,a->operando1,a->operando2,a->destino);	
	}
	fin = g_queue_peek_head(cuadruplos);
}

fclose(objeto);
free(dir_procs);
}

yyerror(char *s){
       printf("Error de sintaxis en la línea %d\n", yylineno);
}


/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

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
			printf("Error: Variable %s no declarada en la línea %d\n",name,yylineno);
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
		
		switch(operador){
				case 3:
				case 6:{
				  g_queue_pop_head(POperadores);
					generar_cuadruplo(operador,operando1,operando2,operando1);
				}break;
				default:{
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
		
		switch(operador){
			case 2:
			case 5:{
				generar_cuadruplo(operador,operando1,-1,operando1);
			}break;
			default:{
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



/* Line 189 of yacc.c  */
#line 938 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ADELANTE = 258,
     ATRAS = 259,
     ROTADERECHA = 260,
     ROTAIZQUIERDA = 261,
     TOMARTESORO = 262,
     TOPA = 263,
     TOPADERECHA = 264,
     TOPAIZQUIERDA = 265,
     VERPISTA = 266,
     SI = 267,
     SINO = 268,
     MIENTRAS = 269,
     FUNCION = 270,
     ENTERO = 271,
     FLOTANTE = 272,
     SELECCIONA = 273,
     CUANDO = 274,
     REGRESA = 275,
     LOGICO = 276,
     PALABRA = 277,
     ESCRIBE = 278,
     LEE = 279,
     PRINCIPAL = 280,
     VERDADERO = 281,
     FALSO = 282,
     Y = 283,
     O = 284,
     NO = 285,
     PROGRAMA = 286,
     CARACTER = 287,
     COMA = 288,
     PUNTOCOMA = 289,
     IGUALP = 290,
     ALLAVE = 291,
     CLLAVE = 292,
     IGUALR = 293,
     MAYORQUE = 294,
     MENORQUE = 295,
     DIFERENTE = 296,
     APARENTESIS = 297,
     CPARENTESIS = 298,
     MAS = 299,
     MENOS = 300,
     POR = 301,
     ENTRE = 302,
     CONCA = 303,
     CTF = 304,
     CTESTRING = 305,
     ID = 306,
     CAR = 307,
     CTE = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 864 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 1035 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1047 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  128
/* YYNRULES -- Number of rules.  */
#define YYNRULES  199
/* YYNRULES -- Number of states.  */
#define YYNSTATES  289

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    13,    16,    19,    20,    23,
      24,    28,    29,    33,    36,    37,    38,    39,    46,    47,
      49,    51,    54,    55,    56,    57,    70,    73,    74,    76,
      77,    80,    81,    83,    84,    85,    86,    94,    97,    98,
     101,   102,   104,   106,   108,   110,   112,   114,   116,   118,
     120,   124,   126,   128,   130,   132,   134,   136,   138,   140,
     142,   143,   147,   149,   151,   152,   153,   160,   162,   163,
     164,   165,   171,   172,   176,   178,   180,   181,   185,   187,
     189,   190,   194,   195,   199,   201,   202,   206,   208,   209,
     213,   215,   217,   219,   221,   223,   224,   234,   236,   238,
     239,   243,   244,   246,   250,   251,   260,   261,   262,   273,
     275,   276,   277,   284,   285,   289,   290,   294,   295,   299,
     300,   301,   311,   312,   318,   319,   324,   326,   328,   330,
     332,   334,   336,   338,   340,   343,   344,   348,   351,   352,
     353,   357,   360,   361,   362,   366,   367,   371,   372,   373,
     377,   378,   382,   383,   384,   388,   391,   392,   393,   397,
     398,   402,   404,   407,   409,   410,   411,   415,   416,   420,
     421,   425,   426,   427,   431,   432,   436,   437,   441,   442,
     444,   446,   448,   450,   451,   457,   459,   460,   463,   465,
     467,   468,   469,   473,   474,   479,   480,   483,   485,   487
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      55,     0,    -1,    -1,    -1,    56,    31,    51,    57,    35,
      58,    77,    -1,    59,    60,    -1,    61,    59,    -1,    -1,
      70,    60,    -1,    -1,    82,    62,    34,    -1,    -1,    51,
      63,    64,    -1,    33,    62,    -1,    -1,    -1,    -1,    65,
      38,    66,    68,    67,    69,    -1,    -1,   129,    -1,   145,
      -1,    33,    62,    -1,    -1,    -1,    -1,    15,    74,    51,
      71,    42,    76,    43,    36,    72,    73,    75,    37,    -1,
      61,    73,    -1,    -1,    82,    -1,    -1,    84,    75,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    25,    78,    36,    79,
      80,    81,    37,    -1,    61,    80,    -1,    -1,    84,    81,
      -1,    -1,    16,    -1,    17,    -1,    32,    -1,    22,    -1,
      21,    -1,    53,    -1,    50,    -1,    49,    -1,    52,    -1,
      11,    42,    43,    -1,    26,    -1,    27,    -1,    85,    -1,
      93,    -1,    86,    -1,   110,    -1,   123,    -1,   130,    -1,
     133,    -1,    -1,    51,    87,    88,    -1,    89,    -1,    96,
      -1,    -1,    -1,    42,    90,    92,    43,    91,    34,    -1,
     142,    -1,    -1,    -1,    -1,    20,    94,   145,    95,    34,
      -1,    -1,    97,    98,    34,    -1,    99,    -1,   102,    -1,
      -1,    38,   100,   101,    -1,   129,    -1,   145,    -1,    -1,
      44,   103,   105,    -1,    -1,    45,   104,   107,    -1,    44,
      -1,    -1,    38,   106,   109,    -1,    45,    -1,    -1,    38,
     108,   109,    -1,    53,    -1,    49,    -1,    51,    -1,   111,
      -1,   117,    -1,    -1,    12,    42,   113,   112,    43,    36,
      81,    37,   114,    -1,   145,    -1,   135,    -1,    -1,    13,
     115,   116,    -1,    -1,   110,    -1,    36,    81,    37,    -1,
      -1,    18,    42,   160,    43,    36,   118,   119,    37,    -1,
      -1,    -1,    19,   181,   120,    38,    39,    36,    81,    37,
     121,   122,    -1,   119,    -1,    -1,    -1,    23,    42,   125,
      43,   124,    34,    -1,    -1,   160,   126,   127,    -1,    -1,
      48,   128,   125,    -1,    -1,    24,    42,    43,    -1,    -1,
      -1,    14,   131,    42,   145,    43,    36,   132,    81,    37,
      -1,    -1,   137,   134,    42,    43,    34,    -1,    -1,   137,
     136,    42,    43,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,
      82,   139,    -1,    -1,    51,   140,   141,    -1,    33,   138,
      -1,    -1,    -1,   160,   143,   144,    -1,    33,   142,    -1,
      -1,    -1,   149,   146,   147,    -1,    -1,    29,   148,   145,
      -1,    -1,    -1,   153,   150,   151,    -1,    -1,    28,   152,
     149,    -1,    -1,    -1,   160,   154,   155,    -1,   156,   153,
      -1,    -1,    -1,    39,   157,   159,    -1,    -1,    40,   158,
     159,    -1,    41,    -1,    38,    38,    -1,    38,    -1,    -1,
      -1,   165,   161,   162,    -1,    -1,    44,   163,   160,    -1,
      -1,    45,   164,   160,    -1,    -1,    -1,   170,   166,   167,
      -1,    -1,    46,   168,   165,    -1,    -1,    47,   169,   165,
      -1,    -1,   171,    -1,   174,    -1,   176,    -1,   180,    -1,
      -1,   173,    42,   172,   145,    43,    -1,    30,    -1,    -1,
     175,    83,    -1,    45,    -1,    30,    -1,    -1,    -1,    51,
     177,   178,    -1,    -1,    42,   179,    92,    43,    -1,    -1,
     173,   135,    -1,    51,    -1,    53,    -1,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   885,   885,   885,   885,   887,   888,   889,   890,   891,
     893,   894,   894,   895,   896,   896,   896,   896,   901,   902,
     903,   904,   905,   907,   916,   907,   948,   949,   950,   953,
     956,   957,   958,   959,   961,   966,   961,   982,   983,   984,
     985,   987,   988,   989,   990,   991,   993,   994,   995,   996,
     997,   998,   999,  1001,  1002,  1004,  1005,  1006,  1007,  1008,
    1010,  1010,  1011,  1012,  1014,  1024,  1014,  1043,  1044,  1046,
    1046,  1046,  1083,  1083,  1084,  1085,  1086,  1086,  1090,  1091,
    1093,  1093,  1094,  1094,  1095,  1096,  1096,  1097,  1098,  1098,
    1100,  1101,  1102,  1104,  1105,  1106,  1106,  1129,  1130,  1131,
    1131,  1144,  1145,  1146,  1147,  1147,  1167,  1182,  1167,  1198,
    1199,  1201,  1201,  1208,  1208,  1215,  1215,  1216,  1218,  1256,
    1257,  1256,  1280,  1280,  1286,  1286,  1292,  1293,  1294,  1295,
    1296,  1297,  1298,  1299,  1301,  1302,  1302,  1303,  1304,  1305,
    1305,  1334,  1335,  1337,  1337,  1343,  1343,  1344,  1346,  1346,
    1352,  1352,  1353,  1355,  1355,  1361,  1362,  1363,  1363,  1364,
    1364,  1365,  1366,  1367,  1373,  1376,  1375,  1381,  1381,  1382,
    1382,  1383,  1386,  1385,  1392,  1392,  1393,  1393,  1394,  1396,
    1397,  1398,  1399,  1400,  1400,  1414,  1415,  1416,  1423,  1424,
    1425,  1426,  1426,  1427,  1427,  1484,  1489,  1500,  1501,  1502
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADELANTE", "ATRAS", "ROTADERECHA",
  "ROTAIZQUIERDA", "TOMARTESORO", "TOPA", "TOPADERECHA", "TOPAIZQUIERDA",
  "VERPISTA", "SI", "SINO", "MIENTRAS", "FUNCION", "ENTERO", "FLOTANTE",
  "SELECCIONA", "CUANDO", "REGRESA", "LOGICO", "PALABRA", "ESCRIBE", "LEE",
  "PRINCIPAL", "VERDADERO", "FALSO", "Y", "O", "NO", "PROGRAMA",
  "CARACTER", "COMA", "PUNTOCOMA", "IGUALP", "ALLAVE", "CLLAVE", "IGUALR",
  "MAYORQUE", "MENORQUE", "DIFERENTE", "APARENTESIS", "CPARENTESIS", "MAS",
  "MENOS", "POR", "ENTRE", "CONCA", "CTF", "CTESTRING", "ID", "CAR", "CTE",
  "$accept", "programa", "$@1", "$@2", "programap", "programapp",
  "programappp", "vars", "vars_id", "$@3", "varsip", "$@4", "$@5", "$@6",
  "var_init", "var_initp", "funcion", "$@7", "$@8", "funcionv", "tipof",
  "funcionp", "funcionpp", "main", "$@9", "$@10", "mainv", "bloque",
  "tipo", "varcte", "estatutofuncion", "estatuto", "empieza_id", "$@11",
  "empieza_idp", "ejecuta_funcion", "$@12", "$@13", "paramsf", "regresa",
  "$@14", "$@15", "asignacion", "$@16", "asignacionp", "asigp", "$@17",
  "lea", "ap", "$@18", "$@19", "maiap", "$@20", "miap", "$@21", "atipo",
  "condicion", "c", "$@22", "condicion_exp", "sip", "$@23", "sipp", "cp",
  "$@24", "cuandop", "$@25", "$@26", "cuandopp", "escritura", "$@27",
  "escriturap", "$@28", "e", "$@29", "lectura", "ciclo", "$@30", "$@31",
  "accion", "$@32", "accionsi", "$@33", "acciones", "params", "paramsp",
  "$@34", "paramspp", "params2", "$@35", "params2p", "mmexp", "$@36",
  "mmexpp", "$@37", "mexp", "$@38", "mexpp", "$@39", "expresion", "$@40",
  "expresionp", "ep", "$@41", "$@42", "epp", "exp", "$@43", "expp", "$@44",
  "$@45", "termino", "$@46", "terminop", "$@47", "$@48", "factor",
  "factorp", "$@49", "nf", "factorpp", "f", "factorppp", "$@50", "fun_var",
  "$@51", "factorpppp", "varselecciona", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    56,    57,    55,    58,    59,    59,    60,    60,
      61,    63,    62,    64,    65,    66,    67,    64,    64,    68,
      68,    69,    69,    71,    72,    70,    73,    73,    74,    74,
      75,    75,    76,    76,    78,    79,    77,    80,    80,    81,
      81,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    85,
      87,    86,    88,    88,    90,    91,    89,    92,    92,    94,
      95,    93,    97,    96,    98,    98,   100,    99,   101,   101,
     103,   102,   104,   102,   105,   106,   105,   107,   108,   107,
     109,   109,   109,   110,   110,   112,   111,   113,   113,   115,
     114,   114,   116,   116,   118,   117,   120,   121,   119,   122,
     122,   124,   123,   126,   125,   128,   127,   127,   129,   131,
     132,   130,   134,   133,   136,   135,   137,   137,   137,   137,
     137,   137,   137,   137,   138,   140,   139,   141,   141,   143,
     142,   144,   144,   146,   145,   148,   147,   147,   150,   149,
     152,   151,   151,   154,   153,   155,   155,   157,   156,   158,
     156,   156,   156,   159,   159,   161,   160,   163,   162,   164,
     162,   162,   166,   165,   168,   167,   169,   167,   167,   170,
     170,   170,   170,   172,   171,   173,   173,   174,   175,   175,
     175,   177,   176,   179,   178,   178,   180,   181,   181,   181
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     7,     2,     2,     0,     2,     0,
       3,     0,     3,     2,     0,     0,     0,     6,     0,     1,
       1,     2,     0,     0,     0,    12,     2,     0,     1,     0,
       2,     0,     1,     0,     0,     0,     7,     2,     0,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     1,     0,     0,     6,     1,     0,     0,
       0,     5,     0,     3,     1,     1,     0,     3,     1,     1,
       0,     3,     0,     3,     1,     0,     3,     1,     0,     3,
       1,     1,     1,     1,     1,     0,     9,     1,     1,     0,
       3,     0,     1,     3,     0,     8,     0,     0,    10,     1,
       0,     0,     6,     0,     3,     0,     3,     0,     3,     0,
       0,     9,     0,     5,     0,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     3,     2,     0,     0,
       3,     2,     0,     0,     3,     0,     3,     0,     0,     3,
       0,     3,     0,     0,     3,     2,     0,     0,     3,     0,
       3,     1,     2,     1,     0,     0,     3,     0,     3,     0,
       3,     0,     0,     3,     0,     3,     0,     3,     0,     1,
       1,     1,     1,     0,     5,     1,     0,     2,     1,     1,
       0,     0,     3,     0,     4,     0,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     7,    41,    42,
      45,    44,    43,     0,     9,     7,     0,    34,     4,    29,
       5,     9,     6,    11,     0,     0,     0,    28,     8,    14,
      10,    35,    23,     0,    12,     0,    38,     0,    13,    15,
      38,    40,    33,   186,    37,   126,   127,   128,   129,   130,
     131,   132,   133,     0,   119,     0,    69,     0,    60,     0,
      40,    53,    55,    54,    56,    93,    94,    57,    58,    59,
     122,     0,     0,    32,     0,   185,   188,   191,    16,    19,
      20,   143,   148,   153,   165,   172,   179,     0,   180,     0,
     181,   182,   190,     0,   186,   186,   186,    72,    36,    39,
       0,     0,   135,   134,     0,   195,    22,   147,   152,   156,
     171,   178,   183,   196,   124,     0,    51,    52,    48,    47,
      49,    46,   187,    95,    98,    97,   186,     0,    70,     0,
     113,    64,    61,    62,    63,     0,     0,    24,   138,   118,
     193,   192,     0,    17,   145,   144,   150,   149,     0,   157,
     159,   161,   154,   186,   167,   169,   166,   174,   176,   173,
     186,     0,     0,     0,     0,     0,     0,   111,   117,   186,
      76,    80,    82,     0,    74,    75,     0,    27,     0,   136,
     186,    21,   186,   186,   162,   164,   164,   155,   186,   186,
     186,   186,     0,     0,    50,     0,     0,   104,    71,     0,
     115,   114,     0,    67,   139,   186,     0,     0,    73,   123,
      27,    31,   137,     0,   146,   151,   163,   158,   160,   168,
     170,   175,   177,   184,   125,    40,   120,     0,   112,   186,
      65,   142,    77,    78,    79,    85,    84,    81,    88,    87,
      83,    26,     0,    31,   194,     0,    40,     0,     0,   116,
       0,   186,   140,     0,     0,    25,    30,   101,     0,   197,
     199,   198,   106,   105,    66,   141,    91,    92,    90,    86,
      89,    99,    96,   121,     0,     0,     0,    40,   102,   100,
       0,     0,    40,   103,     0,   107,   110,   109,   108
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    13,    14,    20,    15,    24,    29,
      34,    35,    43,   106,    78,   143,    21,    37,   177,   211,
      26,   242,    71,    18,    25,    36,    41,    59,    16,   122,
      60,    61,    62,    97,   132,   133,   169,   250,   202,    63,
      95,   166,   134,   135,   173,   174,   205,   232,   175,   206,
     207,   237,   253,   240,   254,   269,    64,    65,   163,   123,
     272,   275,   279,    66,   227,   248,   274,   286,   288,    67,
     199,   129,   168,   201,   229,    79,    68,    93,   246,    69,
     100,   113,   161,    70,    73,   103,   138,   179,   203,   231,
     252,    80,   107,   145,   182,    81,   108,   147,   183,    82,
     109,   152,   153,   185,   186,   217,    83,   110,   156,   188,
     189,    84,   111,   159,   190,   191,    85,    86,   160,    87,
      88,    89,    90,   105,   141,   180,    91,   262
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -193
static const yytype_int16 yypact[] =
{
    -193,    21,    -7,  -193,   -19,  -193,     5,    52,  -193,  -193,
    -193,  -193,  -193,    35,    62,    52,    28,  -193,  -193,    52,
    -193,    62,  -193,  -193,    59,    60,    44,  -193,  -193,    33,
    -193,  -193,  -193,    28,  -193,    73,    52,    74,  -193,  -193,
      52,     8,    52,    12,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,    76,  -193,    95,  -193,    96,  -193,    82,
       8,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,    71,    88,  -193,    98,    77,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,   145,  -193,   120,
    -193,  -193,    40,   101,    83,    83,    83,   102,  -193,  -193,
     103,   121,  -193,  -193,   113,   116,   126,   131,   134,    67,
      42,    25,  -193,  -193,  -193,   122,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,    83,   123,  -193,   124,
    -193,  -193,  -193,  -193,  -193,   -11,   125,  -193,   138,  -193,
    -193,  -193,    28,  -193,  -193,  -193,  -193,  -193,   136,  -193,
    -193,  -193,  -193,    83,  -193,  -193,  -193,  -193,  -193,  -193,
      83,   135,   133,   137,   139,   142,   147,  -193,   140,    72,
    -193,  -193,  -193,   149,  -193,  -193,   150,    52,    52,  -193,
      72,  -193,    83,    83,  -193,   141,   141,  -193,    83,    83,
      83,    83,   146,   148,  -193,   154,   156,  -193,  -193,   151,
    -193,  -193,   152,  -193,  -193,    12,    14,    -8,  -193,  -193,
      52,     8,  -193,   153,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,     8,  -193,   174,  -193,    83,
    -193,   161,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,   160,     8,  -193,   162,     8,     3,   163,  -193,
     164,    83,  -193,    27,    27,  -193,  -193,   188,   165,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,   166,    17,   167,     8,  -193,  -193,
     169,   170,     8,  -193,   171,  -193,   174,  -193,  -193
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -193,  -193,  -193,  -193,  -193,   194,   182,   -35,   -30,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,     0,
    -193,   -32,  -193,  -193,  -193,  -193,   172,   -60,   -17,  -193,
    -192,  -193,  -193,  -193,  -193,  -193,  -193,  -193,    34,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,   -41,   -59,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,   -71,  -193,  -193,  -193,  -193,
    -193,   -10,  -193,  -193,  -193,    13,  -193,  -193,  -193,  -193,
    -193,   128,  -193,   -83,    43,  -193,  -193,  -193,   -28,  -193,
    -193,   -85,  -193,  -193,  -193,    41,  -193,  -193,  -193,    75,
    -193,  -193,  -193,  -193,  -193,    39,   -88,  -193,  -193,  -193,
    -193,  -101,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -191
static const yytype_int16 yytable[] =
{
      99,    40,    27,    38,   114,    40,   127,   125,   130,   114,
     128,    45,    46,    47,    48,    49,    50,    51,    52,   243,
      53,     3,    54,  -190,     4,    72,    55,   170,    56,    53,
     238,    57,     5,   171,   172,    55,    74,   239,  -190,  -190,
       7,   164,    75,    45,    46,    47,    48,    49,    50,    51,
      52,   243,   235,   277,   259,   260,   261,    76,   236,    58,
      17,  -190,  -190,    77,  -190,  -190,    33,   -18,     8,     9,
      75,   157,   158,    10,    11,   192,   266,    19,   267,    23,
     268,   204,  -186,  -190,    12,    76,   154,   155,  -189,   221,
     222,    77,   204,    30,  -190,    32,    31,   214,  -190,  -190,
     219,   220,    75,  -189,  -189,   148,   149,   150,   151,  -190,
    -190,    39,   181,    75,   101,   -68,    42,    76,    92,    98,
     234,  -190,  -190,    77,  -190,  -190,  -189,  -189,    76,  -189,
    -189,   115,  -190,  -190,    77,  -190,  -190,    94,    96,   102,
     104,   130,   210,   126,   131,   136,   116,   117,    45,    46,
      47,    48,    49,    50,    51,    52,   139,   137,   140,   142,
     144,    72,   146,   204,   162,   245,   165,   167,   176,   118,
     119,   178,   120,   121,   184,   210,   194,   193,   197,   216,
     195,   198,   196,   208,   209,   228,   258,   112,   200,   223,
     225,   224,   226,   247,   251,   230,   244,   255,   264,   257,
     263,   271,   273,    28,   276,   282,   280,   283,   285,    22,
     241,   256,    44,   270,   213,   287,   278,   281,   233,   249,
     124,   212,   284,   265,   215,   218,     0,     0,   187
};

static const yytype_int16 yycheck[] =
{
      60,    36,    19,    33,    87,    40,    94,    92,    96,    92,
      95,     3,     4,     5,     6,     7,     8,     9,    10,   211,
      12,     0,    14,    11,    31,    42,    18,    38,    20,    12,
      38,    23,    51,    44,    45,    18,    24,    45,    26,    27,
      35,   126,    30,     3,     4,     5,     6,     7,     8,     9,
      10,   243,    38,    36,    51,    52,    53,    45,    44,    51,
      25,    49,    50,    51,    52,    53,    33,    34,    16,    17,
      30,    46,    47,    21,    22,   160,    49,    15,    51,    51,
      53,   169,    42,    11,    32,    45,    44,    45,    11,   190,
     191,    51,   180,    34,    11,    51,    36,   182,    26,    27,
     188,   189,    30,    26,    27,    38,    39,    40,    41,    26,
      27,    38,   142,    30,    43,    43,    42,    45,    42,    37,
     205,    49,    50,    51,    52,    53,    49,    50,    45,    52,
      53,    11,    49,    50,    51,    52,    53,    42,    42,    51,
      42,   229,   177,    42,    42,    42,    26,    27,     3,     4,
       5,     6,     7,     8,     9,    10,    43,    36,    42,    33,
      29,   178,    28,   251,    42,   225,    43,    43,    43,    49,
      50,    33,    52,    53,    38,   210,    43,    42,    36,    38,
      43,    34,    43,    34,    34,    34,   246,    42,    48,    43,
      36,    43,    36,    19,    33,    43,    43,    37,    34,    37,
      37,    13,    37,    21,    38,    36,    39,    37,    37,    15,
     210,   243,    40,   254,   180,   286,   275,   277,   205,   229,
      92,   178,   282,   251,   183,   186,    -1,    -1,   153
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,    56,     0,    31,    51,    57,    35,    16,    17,
      21,    22,    32,    58,    59,    61,    82,    25,    77,    15,
      60,    70,    59,    51,    62,    78,    74,    82,    60,    63,
      34,    36,    51,    33,    64,    65,    79,    71,    62,    38,
      61,    80,    42,    66,    80,     3,     4,     5,     6,     7,
       8,     9,    10,    12,    14,    18,    20,    23,    51,    81,
      84,    85,    86,    93,   110,   111,   117,   123,   130,   133,
     137,    76,    82,   138,    24,    30,    45,    51,    68,   129,
     145,   149,   153,   160,   165,   170,   171,   173,   174,   175,
     176,   180,    42,   131,    42,    94,    42,    87,    37,    81,
     134,    43,    51,   139,    42,   177,    67,   146,   150,   154,
     161,   166,    42,   135,   137,    11,    26,    27,    49,    50,
      52,    53,    83,   113,   135,   145,    42,   160,   145,   125,
     160,    42,    88,    89,    96,    97,    42,    36,   140,    43,
      42,   178,    33,    69,    29,   147,    28,   151,    38,    39,
      40,    41,   155,   156,    44,    45,   162,    46,    47,   167,
     172,   136,    42,   112,   145,    43,    95,    43,   126,    90,
      38,    44,    45,    98,    99,   102,    43,    72,    33,   141,
     179,    62,   148,   152,    38,   157,   158,   153,   163,   164,
     168,   169,   145,    42,    43,    43,    43,    36,    34,   124,
      48,   127,    92,   142,   160,   100,   103,   104,    34,    34,
      61,    73,   138,    92,   145,   149,    38,   159,   159,   160,
     160,   165,   165,    43,    43,    36,    36,   118,    34,   128,
      43,   143,   101,   129,   145,    38,    44,   105,    38,    45,
     107,    73,    75,    84,    43,    81,   132,    19,   119,   125,
      91,    33,   144,   106,   108,    37,    75,    37,    81,    51,
      52,    53,   181,    37,    34,   142,    49,    51,    53,   109,
     109,    13,   114,    37,   120,   115,    38,    36,   110,   116,
      39,    81,    36,    37,    81,    37,   121,   119,   122
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 885 "parser.y"
    {;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 885 "parser.y"
    {nombreobj = yylval.str;//Nombre del programa
/* Regla 48*/tipo_actual = 'V'; /*Regla 101*/insert_proc_to_table("programa"); /*Regla 33*/ insert_dir_inicial();/*Regla 43*/generar_cuadruplo(21,-1,-1,-1);/*goto del main*/ ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 894 "parser.y"
    {/*Regla 103 y 32*/id_a_verificar = yylval.str; insert_var_to_table(yylval.str,proc_actual);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 896 "parser.y"
    {/*Regla 1*/verifica_existe_var(id_a_verificar);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 896 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(19));/*operador asigancion(=)*/;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 896 "parser.y"
    {
		//Regla 3
		printf("Genera cuádruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 907 "parser.y"
    {
	//Regla 101
	insert_proc_to_table(yylval.str);
	//Regla 35
	bandera_return = 0;
	/*Regla 46*/ 
	if(tipo_funcion_actual != 'V'){
		insert_var_to_table(proc_actual,"programa");
	}
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
    {/*Regla 33*/insert_dir_inicial();;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
    {
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
	
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 950 "parser.y"
    {//Regla 49
		tipo_funcion_actual = tipo_actual;
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 953 "parser.y"
    { 	//Regla 48
		tipo_funcion_actual= 'V';
		tipo_actual = 'V';;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 961 "parser.y"
    {/* Regla 48*/tipo_actual = 'V';
		/*Regla 101*/insert_proc_to_table(yylval.str);
		/*Regla 33*/insert_dir_inicial();
		//Regla 35
		bandera_return = 0;
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 966 "parser.y"
    {
		//Regla 50
		//Rellenar goto inicial del main con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_peek_nth(cuadruplos,0);
		tmp->destino = contador_cuadruplos;
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 973 "parser.y"
    {
		
		//Verificar si hubo return
		if(bandera_return == 1){
			printf("Error: En principal no debe haber regresa\n");
			exit(1);
		}
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 987 "parser.y"
    {/*Regla 102*/tipo_actual= 'I';;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 988 "parser.y"
    {/*Regla 102*/tipo_actual= 'F';;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 989 "parser.y"
    {/*Regla 102*/tipo_actual= 'C';;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 990 "parser.y"
    {/*Regla 102*/tipo_actual= 'S';;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 991 "parser.y"
    {/*Regla 102*/tipo_actual= 'L';;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 993 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,1);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 994 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,3);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 995 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,2);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 996 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,4);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 997 "parser.y"
    {/*Regla 31*/generar_cuadruplo_verpista(); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 998 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,5);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 999 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,5);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1010 "parser.y"
    {/*Regla 17*/id_a_verificar=yylval.str;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1014 "parser.y"
    {
			/*Regla 105*/
			verifica_existe_procs(id_a_verificar);
						
			//Regla 36
			g_queue_push_head(PFunciones,id_a_verificar);
			//ERA
			generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
			g_queue_push_head(PParametros,GINT_TO_POINTER(0));
			
			;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1024 "parser.y"
    {
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
			;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1046 "parser.y"
    {/*Regla 44*/bandera_return = 1;;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1046 "parser.y"
    {
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
	
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1083 "parser.y"
    {/*Regla 104*/verifica_existe_var(id_a_verificar);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1086 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(19));/*operador asigancion(=)*/;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1086 "parser.y"
    {
		//Regla 3
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1093 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(1));/*operador +*/;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1094 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(4));/*operador -*/;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1095 "parser.y"
    {/*Regla 4*/generar_cuadruplo_expresion_unaria();;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1096 "parser.y"
    {verifica_existe_var(id_a_verificar); g_queue_push_head(POperadores,GINT_TO_POINTER(3));;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1096 "parser.y"
    {/*Regla 5*/generar_cuadruplo_expresion();;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1097 "parser.y"
    {/*Regla 4*/ generar_cuadruplo_expresion_unaria();;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1098 "parser.y"
    {verifica_existe_var(id_a_verificar); g_queue_push_head(POperadores,GINT_TO_POINTER(6));;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1098 "parser.y"
    {/*Regla 5*/generar_cuadruplo_expresion();;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1100 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,1);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1101 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,2);;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1102 "parser.y"
    {/*Regla 104*/verifica_existe_var(yylval.str);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1106 "parser.y"
    {
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
		
		
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1120 "parser.y"
    {
		//Regla 22
		int final = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		//Rellenar GoTo con el contador de cuádruplos para el final
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,(guint)final-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,final-1);
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1131 "parser.y"
    {
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
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1147 "parser.y"
    {
		//Regla 42
		g_queue_push_head(PSwitch,GINT_TO_POINTER(0));		
		;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1150 "parser.y"
    {
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
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1167 "parser.y"
    {
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
		
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1182 "parser.y"
    {
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
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1201 "parser.y"
    {
		//Regla 26
		int operando1 = GPOINTER_TO_INT(g_queue_pop_head(POperandos));	
		int tipo1 = GPOINTER_TO_INT(g_queue_pop_head(PTipos));
		printf("Genera cuádruplo de escribe\n");
		generar_cuadruplo(34,operando1,-1,-1);
		;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1208 "parser.y"
    { 
		//Regla 27
		if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 9){
		printf("Genera cuádruplo .\n");
		generar_cuadruplo_expresion();		
		};}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1215 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(9));/*operador concatenacion(.)*/;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1218 "parser.y"
    {/*Regla 54*/
					int tipo_var = g_queue_peek_head(PTipos);
					funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
					int tmp2;
					switch(tipo_var){
						case 1: tmp2 = enterostemporales;
							enterostemporales++;
							tabla->tamano_temporales[0]++;
							break;
						case 2: tmp2 = flotantestemporales;
							flotantestemporales++;
							tabla->tamano_temporales[1]++;
							break;
						case 3: tmp2 = stringstemporales;
							stringstemporales++;
							tabla->tamano_temporales[2]++;
							break;
						case 4: tmp2 = caracterestemporales;
							caracterestemporales++;
							tabla->tamano_temporales[3]++;
							break;
						case 5: tmp2 = logicostemporales;
							logicostemporales++;
							tabla->tamano_temporales[4]++;
							break;
					}
					printf("tipo var: %d y tmp: %d enterostemp: %d\n",tipo_var,tmp2,enterostemporales);
					
					printf("Genera cuadruplo lee \n");
					generar_cuadruplo(40,-1,-1,tmp2);

					//Se agrega el temporal a la pila
					g_queue_push_head(POperandos,GINT_TO_POINTER(tmp2));
					g_queue_push_head(PTipos,GINT_TO_POINTER(tipo_var));
					//insert_constante_to_table("Lectura de pantalla",3);
					
					;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1256 "parser.y"
    {/* Regla 23*/g_queue_push_head(PSaltos,GINT_TO_POINTER(contador_cuadruplos)); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1257 "parser.y"
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
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1268 "parser.y"
    {
		//Regla 25
		int falso = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		int retorno = GPOINTER_TO_INT(g_queue_pop_head(PSaltos));
		generar_cuadruplo(21,-1,-1,retorno);
		//Rellenar falso con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1280 "parser.y"
    {
	//Regla 41
	printf("Genera cuádruplo de acción\n");
	generar_cuadruplo(accion,-1,-1,-1);
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1286 "parser.y"
    {
	//Regla 18
	printf("Genera cuádruplo de acción\n");
	generar_cuadruplo_accionsi(accion);
	
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1292 "parser.y"
    {/*Regla 52*/accion = 28;;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1293 "parser.y"
    {/*Regla 52*/accion = 29;;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1294 "parser.y"
    {/*Regla 52*/accion = 30;;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1295 "parser.y"
    {/*Regla 52*/accion = 31;;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1296 "parser.y"
    {/*Regla 52*/accion = 32;;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1297 "parser.y"
    {/*Regla 52*/accion = 33;;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1298 "parser.y"
    {/*Regla 52*/accion = 38;;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1299 "parser.y"
    {/*Regla 52*/accion = 39;;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1302 "parser.y"
    {/*Regla 19*/insert_param_tipo();/*Regla 103*/insert_var_to_table(yylval.str,proc_actual);;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1305 "parser.y"
    { 
	
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
	;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1337 "parser.y"
    {
	//Regla 9
	  if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 17){
  			printf("Genera cuádruplo or \n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1343 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(17));/*operador or*/;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1346 "parser.y"
    {
	//Regla 8
  if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 16){
  			printf("Genera cuádruplo and /\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1352 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(16));/*operador and*/;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1355 "parser.y"
    {
	//Regla 7
  if(valida_existencia_logico(GPOINTER_TO_INT(g_queue_peek_head(POperadores)))){
  			printf("Genera cuádruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1363 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(13));/*operador mayorque*/;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1364 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(10));/*operador menorque*/;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1365 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(11));/*operador diferente*/;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1366 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(15));/*operador igual igual*/;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1367 "parser.y"
    {
		//Regla 6
		int operadoranterior = GPOINTER_TO_INT(g_queue_pop_head(POperadores));
		int operadorreal = dame_operador_logico(operadoranterior,19);
		g_queue_push_head(POperadores,GINT_TO_POINTER(operadorreal));
		;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1376 "parser.y"
    {	//Regla 10
  	if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 1 || GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 4){
		printf("Genera cuádruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1381 "parser.y"
    { /*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(1));printf("Push +\n");/*operador suma*/;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1382 "parser.y"
    { /*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(4));printf("Push -\n");/*operador resta*/;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1386 "parser.y"
    {	//Regla 11
  	if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 7 || GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 8){
    	printf("Genera cuádruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1392 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(7));/*operador multiplica*/;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1393 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(8));/*operador division*/;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1400 "parser.y"
    {/*Regla 12*/g_queue_push_head(POperadores,GINT_TO_POINTER('('));;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1400 "parser.y"
    {
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
		;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1414 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(18));/*operador NOT*/;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1416 "parser.y"
    {
	//Regla 15
  	if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 18 || GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 20){
		printf("Genera cuádruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1423 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(20));/*operador multiplica*/;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1424 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,GINT_TO_POINTER(18));/*operador NOT*/;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1426 "parser.y"
    {/*Regla 17*/id_a_verificar=yylval.str;;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1427 "parser.y"
    {
		//Regla 105
		verifica_existe_procs(id_a_verificar);
		//Regla 36
		g_queue_push_head(PFunciones,id_a_verificar);
		printf("Genera cuádruplo de función: %s \n",id_a_verificar);
		generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
		g_queue_push_head(PParametros,GINT_TO_POINTER(0));
		g_queue_push_head(POperadores,GINT_TO_POINTER('('));
			
	;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1437 "parser.y"
    {
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
	;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1484 "parser.y"
    {	//Regla 1
         	verifica_existe_var(id_a_verificar);
         	
         	;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1489 "parser.y"
    {
		//Regla 53
		//printf("Generar cuadruplo de accion \n");
		//generar_cuadruplo_accion_expresion(accion);

		if(GPOINTER_TO_INT(g_queue_peek_head(POperadores)) == 18){
			printf("Genera cuádruplo not o - \n");
			generar_cuadruplo_expresion_unaria();
		}
		;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1500 "parser.y"
    {/*Regla 104*/verifica_existe_var(yylval.str);;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1501 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,1);;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1502 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 3675 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1505 "parser.y"
 
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


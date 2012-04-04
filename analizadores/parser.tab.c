
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

static GHashTable *dir_procs; //Directerio de Procedimientos
static GHashTable *tabla_constantes; //Tabla de constantes 
static GQueue *cuadruplos; //Tabla de cuadruplos se maneja como lista empezanod con el inidce 0
static char *proc_actual; //Procedimeitno actual mientras recorre sintaxis
static char tipo_actual; //Tipo actual de variables o procedimientos
static char *id_a_verificar; //Varibale utilizada para verificar la existencia del id
static int exp_operador_actual; //Variable utilizada en operaicones logicas con 2 simbolos
static int contador_cuadruplos = 1; //Contador de cuadruplos realizados
static int accion;
extern int yylineno;
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
Estructuras para las tabalas de procedimientos y tabla de variables
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
Descripción: Se encraga de escribir en el codigo objeto
el directorio de procedimientos. La funcion sera utilizada en 
g_hash_table_foreach.

Entrada: char *key, char *value, gpointer user_data
Salida: void
*/
void imprime_dir_procs(char *key, funcion *value, gpointer user_data){
	funcion *f = value;

	fprintf(objeto,"%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",key,f->tipo,f->dir_inicial,f->tamano_locales[0],f->tamano_locales[1]
		,f->tamano_locales[2],f->tamano_locales[3],f->tamano_locales[4],f->tamano_temporales[0],f->tamano_temporales[1],
		f->tamano_temporales[2],f->tamano_temporales[3],f->tamano_temporales[4]);

	
}

/*
Descripción: Se encraga de escribir en el codigo objeto
la tabla de constantes. La funcion sera utilizada en 
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
	temp->tipo = traduce_tipo(tipo_actual);
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
				tabla->tamano_locales[0]++;
				break;
			case 'F': if(strcmp(proc_actual,"programa")== 0){
					virtual = flotantesglobales;
					flotantesglobales++;			
				} else{
					virtual = flotanteslocales;
					flotanteslocales++;
				}
				tabla->tamano_locales[1]++;
				break;
			case 'S': if(strcmp(proc_actual,"programa")== 0){
					virtual = stringsglobales;
					stringsglobales++;			
				} else{
					virtual = stringslocales;
					stringslocales++;
				}
				tabla->tamano_locales[2]++;
				break;
			case 'C': if(strcmp(proc_actual,"programa")== 0){
					virtual = caracteresglobales;
					caracteresglobales++;			
				} else{
					virtual = caractereslocales;
					caractereslocales++;
				}
				tabla->tamano_locales[3]++;
				break;
			case 'L': if(strcmp(proc_actual,"programa")== 0){
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
objeto los cuádruplos que reciba de tipo funcion.

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
	int operando1 = g_queue_pop_head(POperandos);
	printf("op1: %d ", operando1);
	int operador = g_queue_pop_head(POperadores);
	printf("oper: %d ", operador);
	int tipo1 = g_queue_pop_head(PTipos);
	printf("tipo1: %d\n", tipo1);
	funcion *tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
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
Descripción: Meter el tipo del parametro en el procedimiento actual del directorio
de procedimeintos en la secuencia de paramteros en la lista de parametros.

Entrada: 
Salida: void
*/
void insert_param_tipo(){
	funcion *proc = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
	
	g_queue_push_tail(proc->parametros,traduce_tipo(tipo_actual)+1);
	//printf("Se agrego a parametos: %d\n",g_queue_peek_nth(proc->parametros,0));
	//g_queue_foreach(proc->parametros,(GHFunc)printf,NULL);
}
/*
Descripción: Metodo que se encraga de intorudcir en el dir. de procedimientos
el cuadruplo siguiente.

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
#line 875 "parser.tab.c"

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
     VERPISTA = 264,
     SI = 265,
     SINO = 266,
     MIENTRAS = 267,
     FUNCION = 268,
     ENTERO = 269,
     FLOTANTE = 270,
     SELECCIONA = 271,
     CUANDO = 272,
     REGRESA = 273,
     LOGICO = 274,
     PALABRA = 275,
     ESCRIBE = 276,
     LEE = 277,
     PRINCIPAL = 278,
     VACIO = 279,
     VERDADERO = 280,
     FALSO = 281,
     Y = 282,
     O = 283,
     NO = 284,
     PROGRAMA = 285,
     CARACTER = 286,
     COMA = 287,
     PUNTOCOMA = 288,
     IGUALP = 289,
     ALLAVE = 290,
     CLLAVE = 291,
     IGUALR = 292,
     MAYORQUE = 293,
     MENORQUE = 294,
     DIFERENTE = 295,
     APARENTESIS = 296,
     CPARENTESIS = 297,
     MAS = 298,
     MENOS = 299,
     POR = 300,
     ENTRE = 301,
     CONCA = 302,
     CTF = 303,
     CTESTRING = 304,
     ID = 305,
     CAR = 306,
     CTE = 307
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 801 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 971 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 983 "parser.tab.c"

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
#define YYLAST   210

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  126
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  284

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    13,    16,    19,    20,    23,
      24,    28,    29,    33,    36,    37,    38,    39,    46,    47,
      49,    51,    54,    55,    56,    68,    71,    72,    74,    75,
      76,    80,    81,    83,    84,    85,    86,    87,    96,    99,
     100,   103,   104,   106,   108,   110,   112,   114,   116,   118,
     120,   122,   124,   126,   128,   130,   132,   134,   136,   138,
     140,   142,   144,   145,   149,   151,   153,   154,   155,   162,
     164,   165,   169,   170,   174,   176,   178,   179,   183,   185,
     187,   188,   192,   193,   197,   199,   202,   204,   207,   209,
     211,   213,   215,   217,   218,   228,   230,   232,   233,   237,
     238,   240,   244,   245,   254,   255,   256,   267,   269,   270,
     271,   278,   279,   283,   285,   287,   288,   292,   293,   297,
     298,   299,   309,   310,   316,   317,   322,   324,   326,   328,
     330,   332,   334,   337,   338,   342,   345,   346,   347,   351,
     352,   356,   357,   358,   362,   363,   367,   368,   369,   373,
     374,   378,   379,   380,   384,   387,   388,   389,   393,   394,
     398,   400,   403,   405,   406,   407,   411,   412,   416,   417,
     421,   422,   423,   427,   428,   432,   433,   437,   438,   440,
     442,   444,   445,   451,   453,   454,   457,   459,   461,   462,
     463,   467,   468,   473,   474,   476,   478
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      54,     0,    -1,    -1,    -1,    55,    30,    50,    56,    34,
      57,    76,    -1,    58,    59,    -1,    60,    58,    -1,    -1,
      69,    59,    -1,    -1,    82,    61,    33,    -1,    -1,    50,
      62,    63,    -1,    32,    61,    -1,    -1,    -1,    -1,    64,
      37,    65,    67,    66,    68,    -1,    -1,   126,    -1,   143,
      -1,    32,    61,    -1,    -1,    -1,    13,    72,    50,    70,
      41,    75,    42,    35,    71,    73,    36,    -1,    60,    71,
      -1,    -1,    82,    -1,    -1,    -1,    74,    84,    73,    -1,
      -1,   135,    -1,    -1,    -1,    -1,    -1,    23,    77,    35,
      78,    80,    79,    81,    36,    -1,    60,    80,    -1,    -1,
      85,    81,    -1,    -1,    14,    -1,    15,    -1,    31,    -1,
      20,    -1,    19,    -1,    52,    -1,    49,    -1,    48,    -1,
      51,    -1,    24,    -1,     9,    -1,    25,    -1,    26,    -1,
      85,    -1,    93,    -1,    86,    -1,   106,    -1,   119,    -1,
     127,    -1,   130,    -1,    -1,    50,    87,    88,    -1,    89,
      -1,    94,    -1,    -1,    -1,    41,    90,    92,    42,    91,
      33,    -1,   139,    -1,    -1,    18,   143,    33,    -1,    -1,
      95,    96,    33,    -1,    97,    -1,   100,    -1,    -1,    37,
      98,    99,    -1,   126,    -1,   143,    -1,    -1,    43,   101,
     103,    -1,    -1,    44,   102,   104,    -1,    43,    -1,    37,
     105,    -1,    44,    -1,    37,   105,    -1,    52,    -1,    48,
      -1,    50,    -1,   107,    -1,   113,    -1,    -1,    10,    41,
     109,   108,    42,    35,    81,    36,   110,    -1,   143,    -1,
     132,    -1,    -1,    11,   111,   112,    -1,    -1,   106,    -1,
      35,    81,    36,    -1,    -1,    16,    41,   158,    42,    35,
     114,   115,    36,    -1,    -1,    -1,    17,   178,   116,    37,
      38,    35,    81,    36,   117,   118,    -1,   115,    -1,    -1,
      -1,    21,    41,   121,    42,   120,    33,    -1,    -1,   123,
     122,   124,    -1,    83,    -1,   158,    -1,    -1,    47,   125,
     121,    -1,    -1,    22,    41,    42,    -1,    -1,    -1,    12,
     128,    41,   143,    42,    35,   129,    81,    36,    -1,    -1,
     134,   131,    41,    42,    33,    -1,    -1,   134,   133,    41,
      42,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,    82,   136,    -1,    -1,    50,   137,
     138,    -1,    32,   135,    -1,    -1,    -1,   158,   140,   141,
      -1,    -1,    32,   142,   139,    -1,    -1,    -1,   147,   144,
     145,    -1,    -1,    28,   146,   143,    -1,    -1,    -1,   151,
     148,   149,    -1,    -1,    27,   150,   147,    -1,    -1,    -1,
     158,   152,   153,    -1,   154,   151,    -1,    -1,    -1,    38,
     155,   157,    -1,    -1,    39,   156,   157,    -1,    40,    -1,
      37,    37,    -1,    37,    -1,    -1,    -1,   163,   159,   160,
      -1,    -1,    43,   161,   158,    -1,    -1,    44,   162,   158,
      -1,    -1,    -1,   168,   164,   165,    -1,    -1,    45,   166,
     163,    -1,    -1,    46,   167,   163,    -1,    -1,   169,    -1,
     172,    -1,   174,    -1,    -1,   171,    41,   170,   143,    42,
      -1,    29,    -1,    -1,   173,    83,    -1,    44,    -1,    29,
      -1,    -1,    -1,    50,   175,   176,    -1,    -1,    41,   177,
      92,    42,    -1,    -1,    50,    -1,    52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   821,   821,   821,   821,   822,   823,   824,   825,   826,
     828,   829,   829,   830,   831,   831,   831,   831,   835,   836,
     837,   838,   839,   841,   841,   856,   857,   858,   859,   860,
     860,   861,   862,   863,   865,   865,   870,   865,   873,   874,
     875,   876,   878,   879,   880,   881,   882,   884,   885,   886,
     887,   888,   889,   890,   891,   893,   894,   896,   897,   898,
     899,   900,   902,   902,   903,   904,   906,   915,   906,   930,
     931,   933,   935,   935,   936,   937,   938,   938,   941,   942,
     944,   944,   945,   945,   946,   947,   948,   949,   951,   952,
     953,   955,   956,   957,   957,   979,   980,   981,   981,   993,
     994,   995,   996,   996,  1015,  1030,  1015,  1046,  1047,  1049,
    1049,  1054,  1054,  1059,  1060,  1061,  1061,  1062,  1064,  1066,
    1067,  1066,  1088,  1088,  1094,  1094,  1099,  1100,  1101,  1102,
    1103,  1104,  1106,  1107,  1107,  1108,  1109,  1110,  1110,  1135,
    1135,  1141,  1143,  1143,  1148,  1148,  1149,  1151,  1151,  1156,
    1156,  1157,  1159,  1159,  1164,  1165,  1166,  1166,  1167,  1167,
    1168,  1169,  1170,  1174,  1177,  1176,  1181,  1181,  1182,  1182,
    1183,  1186,  1185,  1191,  1191,  1192,  1192,  1193,  1195,  1196,
    1197,  1198,  1198,  1208,  1209,  1210,  1216,  1217,  1218,  1219,
    1219,  1220,  1220,  1244,  1248,  1249,  1250
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADELANTE", "ATRAS", "ROTADERECHA",
  "ROTAIZQUIERDA", "TOMARTESORO", "TOPA", "VERPISTA", "SI", "SINO",
  "MIENTRAS", "FUNCION", "ENTERO", "FLOTANTE", "SELECCIONA", "CUANDO",
  "REGRESA", "LOGICO", "PALABRA", "ESCRIBE", "LEE", "PRINCIPAL", "VACIO",
  "VERDADERO", "FALSO", "Y", "O", "NO", "PROGRAMA", "CARACTER", "COMA",
  "PUNTOCOMA", "IGUALP", "ALLAVE", "CLLAVE", "IGUALR", "MAYORQUE",
  "MENORQUE", "DIFERENTE", "APARENTESIS", "CPARENTESIS", "MAS", "MENOS",
  "POR", "ENTRE", "CONCA", "CTF", "CTESTRING", "ID", "CAR", "CTE",
  "$accept", "programa", "$@1", "$@2", "programap", "programapp",
  "programappp", "vars", "vars_id", "$@3", "varsip", "$@4", "$@5", "$@6",
  "var_init", "var_initp", "funcion", "$@7", "funcionv", "tipof",
  "funcionp", "$@8", "funcionpp", "main", "$@9", "$@10", "$@11", "mainv",
  "bloque", "tipo", "varcte", "estatutofuncion", "estatuto", "empieza_id",
  "$@12", "empieza_idp", "ejecuta_funcion", "$@13", "$@14", "paramsf",
  "regresa", "asignacion", "$@15", "asignacionp", "asigp", "$@16", "lea",
  "ap", "$@17", "$@18", "maiap", "miap", "atipo", "condicion", "c", "$@19",
  "condicion_exp", "sip", "$@20", "sipp", "cp", "$@21", "cuandop", "$@22",
  "$@23", "cuandopp", "escritura", "$@24", "escriturap", "$@25",
  "escriturapp", "e", "$@26", "lectura", "ciclo", "$@27", "$@28", "accion",
  "$@29", "accionsi", "$@30", "acciones", "params", "paramsp", "$@31",
  "paramspp", "params2", "$@32", "params2p", "$@33", "mmexp", "$@34",
  "mmexpp", "$@35", "mexp", "$@36", "mexpp", "$@37", "expresion", "$@38",
  "expresionp", "ep", "$@39", "$@40", "epp", "exp", "$@41", "expp", "$@42",
  "$@43", "termino", "$@44", "terminop", "$@45", "$@46", "factor",
  "factorp", "$@47", "nf", "factorpp", "f", "factorppp", "$@48", "fun_var",
  "$@49", "varselecciona", 0
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
     305,   306,   307
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    55,    56,    54,    57,    58,    58,    59,    59,
      60,    62,    61,    63,    64,    65,    66,    63,    63,    67,
      67,    68,    68,    70,    69,    71,    71,    72,    72,    74,
      73,    73,    75,    75,    77,    78,    79,    76,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    84,    85,    85,    85,
      85,    85,    87,    86,    88,    88,    90,    91,    89,    92,
      92,    93,    95,    94,    96,    96,    98,    97,    99,    99,
     101,   100,   102,   100,   103,   103,   104,   104,   105,   105,
     105,   106,   106,   108,   107,   109,   109,   111,   110,   110,
     112,   112,   114,   113,   116,   117,   115,   118,   118,   120,
     119,   122,   121,   123,   123,   125,   124,   124,   126,   128,
     129,   127,   131,   130,   133,   132,   134,   134,   134,   134,
     134,   134,   135,   137,   136,   138,   138,   140,   139,   142,
     141,   141,   144,   143,   146,   145,   145,   148,   147,   150,
     149,   149,   152,   151,   153,   153,   155,   154,   156,   154,
     154,   154,   157,   157,   159,   158,   161,   160,   162,   160,
     160,   164,   163,   166,   165,   167,   165,   165,   168,   168,
     168,   170,   169,   171,   171,   172,   173,   173,   173,   175,
     174,   177,   176,   176,   178,   178,   178
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     7,     2,     2,     0,     2,     0,
       3,     0,     3,     2,     0,     0,     0,     6,     0,     1,
       1,     2,     0,     0,    11,     2,     0,     1,     0,     0,
       3,     0,     1,     0,     0,     0,     0,     8,     2,     0,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     3,     1,     1,     0,     0,     6,     1,
       0,     3,     0,     3,     1,     1,     0,     3,     1,     1,
       0,     3,     0,     3,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     0,     9,     1,     1,     0,     3,     0,
       1,     3,     0,     8,     0,     0,    10,     1,     0,     0,
       6,     0,     3,     1,     1,     0,     3,     0,     3,     0,
       0,     9,     0,     5,     0,     4,     1,     1,     1,     1,
       1,     1,     2,     0,     3,     2,     0,     0,     3,     0,
       3,     0,     0,     3,     0,     3,     0,     0,     3,     0,
       3,     0,     0,     3,     2,     0,     0,     3,     0,     3,
       1,     2,     1,     0,     0,     3,     0,     3,     0,     3,
       0,     0,     3,     0,     3,     0,     3,     0,     1,     1,
       1,     0,     5,     1,     0,     2,     1,     1,     0,     0,
       3,     0,     4,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     7,    42,    43,
      46,    45,    44,     0,     9,     7,     0,    34,     4,    28,
       5,     9,     6,    11,     0,     0,     0,    27,     8,    14,
      10,    35,    23,     0,    12,     0,    39,     0,    13,    15,
      39,    36,    33,   188,    38,    41,     0,     0,    32,     0,
     187,   186,   189,    16,    19,    20,   142,   147,   152,   164,
     171,   178,     0,   179,     0,   180,   126,   127,   128,   129,
     130,   131,     0,   119,     0,     0,    62,     0,    41,    57,
      58,    91,    92,    59,    60,    61,   122,     0,   133,   132,
       0,   193,    22,   146,   151,   155,   170,   177,   181,    52,
      51,    53,    54,    49,    48,    50,    47,   185,   188,     0,
     188,   184,    72,    37,    40,     0,    26,   136,   118,   191,
     190,     0,    17,   144,   143,   149,   148,     0,   156,   158,
     160,   153,   188,   166,   168,   165,   173,   175,   172,   188,
      93,    96,   124,    95,   188,     0,   113,     0,   111,   114,
      66,    63,    64,    65,     0,     0,    26,    29,     0,   134,
     188,    21,   188,   188,   161,   163,   163,   154,   188,   188,
     188,   188,     0,     0,     0,     0,     0,   109,   117,   188,
      76,    80,    82,     0,    74,    75,     0,    25,     0,     0,
     135,     0,    69,   137,   145,   150,   162,   157,   159,   167,
     169,   174,   176,   182,     0,     0,     0,   102,     0,   115,
     112,     0,   188,     0,     0,    73,   123,    24,   188,    29,
      55,    56,   192,   141,    41,   125,   120,     0,   110,   184,
      67,    77,    78,    79,     0,    84,    81,     0,    86,    83,
       0,    30,   139,   138,     0,    41,     0,     0,   116,     0,
      89,    90,    88,    85,    87,    71,   188,    99,     0,   194,
     196,   195,   104,   103,    68,   140,    97,    94,   121,     0,
       0,     0,    41,   100,    98,     0,     0,    41,   101,     0,
     105,   108,   107,   106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    13,    14,    20,    15,    24,    29,
      34,    35,    43,    92,    53,   122,    21,    37,   157,    26,
     188,   189,    46,    18,    25,    36,    45,    41,    77,    16,
     146,   219,    78,    79,   112,   151,   152,   179,   249,   191,
     221,   153,   154,   183,   184,   212,   231,   185,   213,   214,
     236,   239,   253,    80,    81,   173,   140,   267,   270,   274,
      82,   227,   247,   269,   281,   283,    83,   208,   147,   178,
     148,   210,   229,    54,    84,   109,   245,    85,   115,   141,
     174,    86,    48,    89,   117,   159,   192,   223,   243,   256,
      55,    93,   124,   162,    56,    94,   126,   163,    57,    95,
     131,   132,   165,   166,   197,    58,    96,   135,   168,   169,
      59,    97,   138,   170,   171,    60,    61,   139,    62,    63,
      64,    65,    91,   120,   160,   262
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -110
static const yytype_int16 yypact[] =
{
    -110,    34,   -24,  -110,   -25,  -110,     2,   120,  -110,  -110,
    -110,  -110,  -110,    16,    29,   120,    -6,  -110,  -110,   120,
    -110,    29,  -110,  -110,    22,    23,    21,  -110,  -110,   -13,
    -110,  -110,  -110,    -6,  -110,    45,   120,    44,  -110,  -110,
     120,  -110,   120,    28,  -110,    25,    49,    36,  -110,    51,
      56,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,    57,  -110,    70,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,    60,  -110,    63,    72,  -110,    79,    25,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,    88,  -110,  -110,
      94,    96,   106,   113,   116,   115,    30,     3,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,    59,   103,
      58,    81,   104,  -110,  -110,   107,   120,   117,  -110,  -110,
    -110,    -6,  -110,  -110,  -110,  -110,  -110,   119,  -110,  -110,
    -110,  -110,    58,  -110,  -110,  -110,  -110,  -110,  -110,    58,
    -110,  -110,  -110,  -110,    58,   108,  -110,   118,  -110,  -110,
    -110,  -110,  -110,  -110,    10,   121,   120,   122,   120,  -110,
      39,  -110,    58,    58,  -110,   124,   124,  -110,    58,    58,
      58,    58,   123,   126,   125,   127,   129,  -110,   110,    39,
    -110,  -110,  -110,   137,  -110,  -110,   138,  -110,   136,     6,
    -110,   131,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,   139,   133,   141,  -110,   144,  -110,
    -110,   140,    28,   -20,     8,  -110,  -110,  -110,    58,   122,
    -110,  -110,  -110,   130,    25,  -110,  -110,   142,  -110,    81,
    -110,  -110,  -110,  -110,    64,  -110,  -110,    64,  -110,  -110,
     145,  -110,  -110,  -110,   143,    25,    76,   147,  -110,   148,
    -110,  -110,  -110,  -110,  -110,  -110,    58,   169,   149,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,   150,
       5,   146,    25,  -110,  -110,   151,   152,    25,  -110,   153,
    -110,   142,  -110,  -110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,  -110,  -110,   175,   170,   -32,   -28,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,    37,  -110,
     -27,  -110,  -110,  -110,  -110,  -110,  -110,   155,   -78,   -16,
     132,  -110,     9,  -110,  -110,  -110,  -110,  -110,  -110,    18,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,   -37,   -69,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,   -79,  -110,  -110,  -110,  -110,  -110,   -26,  -110,
    -110,  -110,  -110,    -8,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,    97,    48,  -110,  -110,  -110,   -49,  -110,  -110,  -110,
    -101,  -110,  -110,  -110,    46,  -110,  -110,  -110,    78,  -110,
    -110,  -110,  -110,  -110,    42,  -109,  -110,  -110,  -110,  -110,
     -94,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,  -110
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -185
static const yytype_int16 yytable[] =
{
     114,   145,   149,    27,    40,    38,     4,   143,    40,    66,
      67,    68,    69,    70,    71,    72,    72,   234,    73,    33,
     -18,    74,    74,   235,   218,     5,    47,    75,    66,    67,
      68,    69,    70,    71,     3,    72,     7,    73,   172,    17,
     272,    74,    19,   175,    23,   237,    75,   180,   136,   137,
      49,   193,   238,   181,   182,    30,    76,    50,    31,   199,
     200,   194,    66,    67,    68,    69,    70,    71,    50,  -184,
     193,    32,    51,   133,   134,    76,   201,   202,    52,    99,
    -184,   -70,    39,    51,   156,    42,    88,    50,    50,    52,
      99,    87,    90,   161,   100,   101,   102,  -183,    98,  -184,
    -184,   108,    51,    51,   110,   100,   101,   102,    52,    52,
      50,   233,   250,   111,   251,   113,   252,   240,   103,   104,
     149,   105,   106,   116,   156,    51,   259,   260,   261,   103,
     104,    52,   105,   106,     8,     9,   118,   119,   121,    10,
      11,   123,    47,   125,   144,   150,   244,   193,   155,   158,
     176,    12,   127,   128,   129,   130,   164,   209,   -31,   246,
     177,   196,   242,   186,   207,   203,   205,   258,   204,   206,
     215,   216,   217,   222,   224,   225,   226,   228,   255,   257,
     266,   264,   230,   263,   275,   268,   277,   271,   278,   280,
      22,    28,   241,   187,   276,    44,   107,   211,   220,   279,
     254,   273,   282,   248,   232,   142,   190,   265,   198,   195,
     167
};

static const yytype_uint16 yycheck[] =
{
      78,   110,   111,    19,    36,    33,    30,   108,    40,     3,
       4,     5,     6,     7,     8,    10,    10,    37,    12,    32,
      33,    16,    16,    43,    18,    50,    42,    21,     3,     4,
       5,     6,     7,     8,     0,    10,    34,    12,   139,    23,
      35,    16,    13,   144,    50,    37,    21,    37,    45,    46,
      22,   160,    44,    43,    44,    33,    50,    29,    35,   168,
     169,   162,     3,     4,     5,     6,     7,     8,    29,    41,
     179,    50,    44,    43,    44,    50,   170,   171,    50,     9,
      41,    42,    37,    44,   116,    41,    50,    29,    29,    50,
       9,    42,    41,   121,    24,    25,    26,    41,    41,    41,
      41,    41,    44,    44,    41,    24,    25,    26,    50,    50,
      29,   212,    48,    41,    50,    36,    52,   218,    48,    49,
     229,    51,    52,    35,   156,    44,    50,    51,    52,    48,
      49,    50,    51,    52,    14,    15,    42,    41,    32,    19,
      20,    28,   158,    27,    41,    41,   224,   256,    41,    32,
      42,    31,    37,    38,    39,    40,    37,    47,    36,    17,
      42,    37,    32,    42,    35,    42,    41,   245,    42,    42,
      33,    33,    36,    42,    35,    42,    35,    33,    33,    36,
      11,    33,    42,    36,    38,    36,    35,    37,    36,    36,
      15,    21,   219,   156,   272,    40,    64,   179,   189,   277,
     237,   270,   281,   229,   212,   108,   158,   256,   166,   163,
     132
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,    55,     0,    30,    50,    56,    34,    14,    15,
      19,    20,    31,    57,    58,    60,    82,    23,    76,    13,
      59,    69,    58,    50,    61,    77,    72,    82,    59,    62,
      33,    35,    50,    32,    63,    64,    78,    70,    61,    37,
      60,    80,    41,    65,    80,    79,    75,    82,   135,    22,
      29,    44,    50,    67,   126,   143,   147,   151,   158,   163,
     168,   169,   171,   172,   173,   174,     3,     4,     5,     6,
       7,     8,    10,    12,    16,    21,    50,    81,    85,    86,
     106,   107,   113,   119,   127,   130,   134,    42,    50,   136,
      41,   175,    66,   144,   148,   152,   159,   164,    41,     9,
      24,    25,    26,    48,    49,    51,    52,    83,    41,   128,
      41,    41,    87,    36,    81,   131,    35,   137,    42,    41,
     176,    32,    68,    28,   145,    27,   149,    37,    38,    39,
      40,   153,   154,    43,    44,   160,    45,    46,   165,   170,
     109,   132,   134,   143,    41,   158,    83,   121,   123,   158,
      41,    88,    89,    94,    95,    41,    60,    71,    32,   138,
     177,    61,   146,   150,    37,   155,   156,   151,   161,   162,
     166,   167,   143,   108,   133,   143,    42,    42,   122,    90,
      37,    43,    44,    96,    97,   100,    42,    71,    73,    74,
     135,    92,   139,   158,   143,   147,    37,   157,   157,   158,
     158,   163,   163,    42,    42,    41,    42,    35,   120,    47,
     124,    92,    98,   101,   102,    33,    33,    36,    18,    84,
      85,    93,    42,   140,    35,    42,    35,   114,    33,   125,
      42,    99,   126,   143,    37,    43,   103,    37,    44,   104,
     143,    73,    32,   141,    81,   129,    17,   115,   121,    91,
      48,    50,    52,   105,   105,    33,   142,    36,    81,    50,
      51,    52,   178,    36,    33,   139,    11,   110,    36,   116,
     111,    37,    35,   106,   112,    38,    81,    35,    36,    81,
      36,   117,   115,   118
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
#line 821 "parser.y"
    {generar_cuadruplo(21,-1,-1,-1);/*goto del main*/ ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 821 "parser.y"
    {tipo_actual = 'V'; insert_proc_to_table("programa");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 829 "parser.y"
    {id_a_verificar = yylval.str; insert_var_to_table(yylval.str);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 831 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 831 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 831 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 841 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 841 "parser.y"
    {
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
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 859 "parser.y"
    {tipo_actual= 'V';;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 860 "parser.y"
    {insert_dir_inicial();;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 865 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 865 "parser.y"
    {
		//Rellenar goto inicial del main con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_peek_nth(cuadruplos,0);
		tmp->destino = contador_cuadruplos;
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 870 "parser.y"
    {
		insert_dir_inicial();
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 878 "parser.y"
    {tipo_actual= 'I';;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 879 "parser.y"
    {tipo_actual= 'F';;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 880 "parser.y"
    {tipo_actual= 'C';;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 881 "parser.y"
    {tipo_actual= 'S';;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 882 "parser.y"
    {tipo_actual= 'L';;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 884 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 885 "parser.y"
    {insert_constante_to_table(yylval.str,3);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 886 "parser.y"
    {insert_constante_to_table(yylval.str,2);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 887 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 890 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 891 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 902 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 906 "parser.y"
    {
			verifica_existe_procs(id_a_verificar);
						
			//Regla 36
			g_queue_push_head(PFunciones,id_a_verificar);
			//ERA
			generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
			g_queue_push_head(PParametros,0);
			
			;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 915 "parser.y"
    {
			//Regla 39
			char *func = g_queue_peek_head(PFunciones);
			funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)func);
	
			g_queue_pop_head(PFunciones);
			int contador_parametros = g_queue_pop_head(PParametros);
			if(g_queue_get_length(ft->parametros) != contador_parametros + 1){
				printf("Error: Menos parámetros de los esperados en la linea %d\n",yylineno);
				exit(1);
			}
			//Regla 40
			generar_cuadruplo_funcion(24,func,ft->dir_inicial,-1);
			;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 935 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 938 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 938 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 944 "parser.y"
    {g_queue_push_head(POperadores,1);/*operador +*/;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 945 "parser.y"
    {g_queue_push_head(POperadores,4);/*operador -*/;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 946 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 947 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 948 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 949 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 951 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 952 "parser.y"
    {insert_constante_to_table(yylval.integer,2);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 953 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 957 "parser.y"
    {
		int aux = g_queue_pop_head(PTipos);
		
		if(aux != 5){
			printf("Error: Se espera un valor lógico en la línea %d\n",yylineno);
			exit(1);
		}
		int resultado = g_queue_pop_head(POperandos);
		printf("Genera cuadruplo gotof\n");
		generar_cuadruplo(22,resultado,-1,-1);
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
		
		
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 970 "parser.y"
    {
		int final = g_queue_pop_head(PSaltos);
		//printf("salto %d\n",final);
		//Rellenar GoTo con el contador de cuádruplos para el final
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,(guint)final-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,final-1);
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 981 "parser.y"
    {
		printf("Genera cuadruplo goto\n");
		generar_cuadruplo(21,-1,-1,-1);
		int falso = g_queue_pop_head(PSaltos);

		//Rellenar falso con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,falso-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,falso-1);
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
	;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 996 "parser.y"
    {
		g_queue_push_head(PSwitch,0);		
		;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 998 "parser.y"
    {
		//Regla 30
		int p;
		int acum = g_queue_pop_head(PSwitch);
		int i = 0;
		while(i < acum){
			p = g_queue_pop_head(PSaltos);
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

  case 104:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
    {
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
		
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1030 "parser.y"
    {
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
		//Regla 42
		int acum = g_queue_pop_head(PSwitch);
		acum++;
		g_queue_push_head(PSwitch,acum);
	;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1049 "parser.y"
    {
		int operando1 = (int)g_queue_pop_head(POperandos);	
		int tipo1 = g_queue_pop_head(PTipos);
		generar_cuadruplo(25,operando1,-1,-1);
		;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1054 "parser.y"
    { if(g_queue_peek_head(POperadores) == 9){
		printf("Genera cuadruplo .\n");
		generar_cuadruplo_expresion();		
		};}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1061 "parser.y"
    {g_queue_push_head(POperadores,9);/*operador concatenacion(.)*/;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1064 "parser.y"
    {insert_constante_to_table("Lectura de pantalla",3);;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1066 "parser.y"
    {g_queue_push_head(PSaltos,contador_cuadruplos); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1067 "parser.y"
    { 	int aux = g_queue_pop_head(PTipos);
		
		if(aux != 5){
			printf("Error: Se espera un valor logico en la línea %d\n",yylineno);
			exit(1);
		}
		int resultado = g_queue_pop_head(POperandos);
		printf("Genera cuadruplo gotof\n");
		generar_cuadruplo(22,resultado,-1,-1);		
		g_queue_push_head(PSaltos,contador_cuadruplos-1);
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1077 "parser.y"
    {
		int falso = g_queue_pop_head(PSaltos);
		int retorno = g_queue_pop_head(PSaltos);
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
#line 1088 "parser.y"
    {
	//Regla 41
	printf("Genera cuadruplo de accion\n");
	generar_cuadruplo(accion,-1,-1,-1);
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1094 "parser.y"
    {
	//Regla 41
	printf("Genera cuadruplo de accion\n");
	generar_cuadruplo(accion,-1,-1,-1);	
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1099 "parser.y"
    {accion = 28;;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1100 "parser.y"
    {accion = 29;;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1101 "parser.y"
    {accion = 30;;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1102 "parser.y"
    {accion = 31;;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1103 "parser.y"
    {accion = 32;;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1104 "parser.y"
    {accion = 33;;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1107 "parser.y"
    {insert_param_tipo();insert_var_to_table(yylval.str);/*Regla 103*/;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1110 "parser.y"
    { 
	
	//Regla 37
	
	int argumento = g_queue_pop_head(POperandos);
	int tipoarg = g_queue_pop_head(PTipos);
	
	funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)g_queue_peek_head(PFunciones));
	int contador_parametros = g_queue_peek_head(PParametros);
	if(g_queue_get_length(ft->parametros) < contador_parametros + 1){
				printf("Error: Mas parámetros de los esperados en la linea %d\n",yylineno);
				exit(1);
			}
	
	int tipoparam = g_queue_peek_nth(ft->parametros,contador_parametros);
	printf("Argumento y tipoarg, tipoparam: %d,%d,%d\n",argumento,tipoarg,tipoparam);
	
	if(tipoarg != tipoparam){
		printf("Error: Se espera un valor %s en la línea %d\n",traduce_tipo2(tipoparam),yylineno);
			exit(1);
	}
	//Generar cuadruplo parametro
	printf("Genera cuadruplo parametro \n");
	generar_cuadruplo(26,argumento,contador_parametros+1,-1);
	;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1135 "parser.y"
    {
		//Regla 38
		int p = g_queue_pop_head(PParametros);
		p++;
		g_queue_push_head(PParametros,p);
		;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1143 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 17){
  			printf("Genera cuadruplo or \n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1148 "parser.y"
    {g_queue_push_head(POperadores,17);/*operador or*/;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1151 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 16){
  			printf("Genera cuadruplo and /\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1156 "parser.y"
    {g_queue_push_head(POperadores,16);/*operador and*/;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1159 "parser.y"
    {
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
  			printf("Genera cuadruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1166 "parser.y"
    {g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1167 "parser.y"
    {g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1168 "parser.y"
    {g_queue_push_head(POperadores,11);/*operador diferente*/;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1169 "parser.y"
    {g_queue_push_head(POperadores,15);/*operador igual igual*/;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1170 "parser.y"
    {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1177 "parser.y"
    {if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1181 "parser.y"
    {g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1182 "parser.y"
    {g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1186 "parser.y"
    {if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1191 "parser.y"
    {g_queue_push_head(POperadores,7);/*operador multiplica*/;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1192 "parser.y"
    {g_queue_push_head(POperadores,8);/*operador division*/;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1198 "parser.y"
    {g_queue_push_head(POperadores,'(');;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1198 "parser.y"
    {if(g_queue_peek_head(POperadores) == '('){
		g_queue_pop_head(POperadores);
		}else{
			printf("Mala construccion de expresion");
		};
		if(g_queue_peek_head(POperadores) == 18){
			printf("Genera cuadruplo not\n");
			generar_cuadruplo_expresion_unaria();
		}
		;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1208 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1210 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		printf("Genera cuadruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1216 "parser.y"
    {g_queue_push_head(POperadores,20);/*operador multiplica*/;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1217 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1219 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1220 "parser.y"
    {
		verifica_existe_procs(id_a_verificar);
					
		//Regla 36
		g_queue_push_head(PFunciones,id_a_verificar);
		//ERA
		generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
		g_queue_push_head(PParametros,0);
			
	;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1229 "parser.y"
    {
		verifica_existe_procs(id_a_verificar);
		//Regla 39
		char *func = g_queue_peek_head(PFunciones);
		funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)func);
	
		g_queue_pop_head(PFunciones);
		int contador_parametros = g_queue_pop_head(PParametros);
		if(g_queue_get_length(ft->parametros) != contador_parametros + 1){
			printf("Error: Menos parámetros de los esperados en la linea %d\n",yylineno);
			exit(1);
		}
		//Regla 40
		generar_cuadruplo_funcion(24,func,ft->dir_inicial,-1);
	;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1244 "parser.y"
    {verifica_existe_var(id_a_verificar);
         	
         	;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1248 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1249 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1250 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 3368 "parser.tab.c"
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
#line 1253 "parser.y"
 
main() { 
objeto = fopen("codigo.obj", "w");
crear_pilas_tablas();
  yyparse(); 
imprime(dir_procs); 


//Escirbir el directorio de procedimientos
g_hash_table_foreach(dir_procs,(GHFunc)imprime_dir_procs,NULL);

fprintf(objeto,"--\n");
//Escribir en el archivo la tabla de constantes
g_hash_table_foreach(tabla_constantes,(GHFunc)imprime_tabla_constantes,NULL);
fprintf(objeto,"--\n");
//Escribir en el arhcivo los cuádruplos
cuadruplo *a = g_slice_new(cuadruplo);
cuadruplofuncion *b = g_slice_new(cuadruplofuncion);
cuadruplo *fin = g_slice_new(cuadruplo);
fin = g_queue_peek_head(cuadruplos);
while(fin){
	a = g_queue_peek_head(cuadruplos);
	if(a->operador == 24 || a->operador == 25){
		b = g_queue_pop_head(cuadruplos);
		fprintf(objeto,"%d,%s,%d,%d\n",b->operador,b->operando1,b->operando2,b->destino);
		
	}else{
		a = g_queue_pop_head(cuadruplos);
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


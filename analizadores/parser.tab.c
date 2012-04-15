
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
static char tipo_actual; //Tipo actual de variables
static char tipo_funcion_actual;//Tipo actual de las funciones
static int bandera_return;
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
Descripción: Inserta el procedieminto en la pila d eoperandos asimismo inserta 
el tipo correspondiente.

Parámetros: char *name
Salida: void
*/
void inserta_procs_factor(char *name){
	funcion *f = g_hash_table_lookup(dir_procs,(gpointer)name);
	if(f->tipo == 'V'){//Valida si un modulo llamdo en la expresion es de tipo void
		printf("Error: Expresion invalida en la línea %d\n",yylineno);
		exit(1);
	}
	funcion *proc_global = g_hash_table_lookup(dir_procs,"programa");
	variable *modulo = g_hash_table_lookup(proc_global->var_table,(gpointer)name);
	g_queue_push_head(POperandos,modulo->dir_virtual);
	g_queue_push_head(PTipos,traduce_tipo(modulo->tipo)+1);
	printf("Direccion Variable Global: %s %d\n",name, modulo->dir_virtual);
	
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
Descripción: Meter el tipo del parámetro en el procedimiento actual del directorio
de procedimientos en la secuencia de parámetros en la lista de parámetros.

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
#line 897 "parser.tab.c"

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
#line 823 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 993 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1005 "parser.tab.c"

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
#define YYLAST   198

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  126
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNRULES -- Number of states.  */
#define YYNSTATES  283

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
     164,   165,   166,   167,   173,   174,   178,   180,   182,   183,
     187,   189,   191,   192,   196,   197,   201,   203,   206,   208,
     211,   213,   215,   217,   219,   221,   222,   232,   234,   236,
     237,   241,   242,   244,   248,   249,   258,   259,   260,   271,
     273,   274,   275,   282,   283,   287,   288,   292,   293,   297,
     298,   299,   309,   310,   316,   317,   322,   324,   326,   328,
     330,   332,   334,   337,   338,   342,   345,   346,   347,   351,
     354,   355,   356,   360,   361,   365,   366,   367,   371,   372,
     376,   377,   378,   382,   385,   386,   387,   391,   392,   396,
     398,   401,   403,   404,   405,   409,   410,   414,   415,   419,
     420,   421,   425,   426,   430,   431,   435,   436,   438,   440,
     442,   443,   449,   451,   452,   455,   457,   459,   460,   461,
     465,   466,   471,   472,   474,   476
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      54,     0,    -1,    -1,    -1,    55,    30,    50,    56,    34,
      57,    76,    -1,    58,    59,    -1,    60,    58,    -1,    -1,
      69,    59,    -1,    -1,    82,    61,    33,    -1,    -1,    50,
      62,    63,    -1,    32,    61,    -1,    -1,    -1,    -1,    64,
      37,    65,    67,    66,    68,    -1,    -1,   127,    -1,   143,
      -1,    32,    61,    -1,    -1,    -1,    13,    72,    50,    70,
      41,    75,    42,    35,    71,    73,    36,    -1,    60,    71,
      -1,    -1,    82,    -1,    -1,    -1,    74,    84,    73,    -1,
      -1,   136,    -1,    -1,    -1,    -1,    -1,    23,    77,    35,
      78,    80,    79,    81,    36,    -1,    60,    80,    -1,    -1,
      85,    81,    -1,    -1,    14,    -1,    15,    -1,    31,    -1,
      20,    -1,    19,    -1,    52,    -1,    49,    -1,    48,    -1,
      51,    -1,    24,    -1,     9,    -1,    25,    -1,    26,    -1,
      85,    -1,    93,    -1,    86,    -1,   108,    -1,   121,    -1,
     128,    -1,   131,    -1,    -1,    50,    87,    88,    -1,    89,
      -1,    96,    -1,    -1,    -1,    41,    90,    92,    42,    91,
      33,    -1,   140,    -1,    -1,    -1,    -1,    18,    94,   143,
      95,    33,    -1,    -1,    97,    98,    33,    -1,    99,    -1,
     102,    -1,    -1,    37,   100,   101,    -1,   127,    -1,   143,
      -1,    -1,    43,   103,   105,    -1,    -1,    44,   104,   106,
      -1,    43,    -1,    37,   107,    -1,    44,    -1,    37,   107,
      -1,    52,    -1,    48,    -1,    50,    -1,   109,    -1,   115,
      -1,    -1,    10,    41,   111,   110,    42,    35,    81,    36,
     112,    -1,   143,    -1,   133,    -1,    -1,    11,   113,   114,
      -1,    -1,   108,    -1,    35,    81,    36,    -1,    -1,    16,
      41,   158,    42,    35,   116,   117,    36,    -1,    -1,    -1,
      17,   178,   118,    37,    38,    35,    81,    36,   119,   120,
      -1,   117,    -1,    -1,    -1,    21,    41,   123,    42,   122,
      33,    -1,    -1,   158,   124,   125,    -1,    -1,    47,   126,
     123,    -1,    -1,    22,    41,    42,    -1,    -1,    -1,    12,
     129,    41,   143,    42,    35,   130,    81,    36,    -1,    -1,
     135,   132,    41,    42,    33,    -1,    -1,   135,   134,    41,
      42,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,    82,   137,    -1,    -1,    50,   138,
     139,    -1,    32,   136,    -1,    -1,    -1,   158,   141,   142,
      -1,    32,   140,    -1,    -1,    -1,   147,   144,   145,    -1,
      -1,    28,   146,   143,    -1,    -1,    -1,   151,   148,   149,
      -1,    -1,    27,   150,   147,    -1,    -1,    -1,   158,   152,
     153,    -1,   154,   151,    -1,    -1,    -1,    38,   155,   157,
      -1,    -1,    39,   156,   157,    -1,    40,    -1,    37,    37,
      -1,    37,    -1,    -1,    -1,   163,   159,   160,    -1,    -1,
      43,   161,   158,    -1,    -1,    44,   162,   158,    -1,    -1,
      -1,   168,   164,   165,    -1,    -1,    45,   166,   163,    -1,
      -1,    46,   167,   163,    -1,    -1,   169,    -1,   172,    -1,
     174,    -1,    -1,   171,    41,   170,   143,    42,    -1,    29,
      -1,    -1,   173,    83,    -1,    44,    -1,    29,    -1,    -1,
      -1,    50,   175,   176,    -1,    -1,    41,   177,    92,    42,
      -1,    -1,    50,    -1,    52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   843,   843,   843,   843,   844,   845,   846,   847,   848,
     850,   851,   851,   852,   853,   853,   853,   853,   857,   858,
     859,   860,   861,   863,   863,   903,   904,   905,   909,   910,
     910,   911,   912,   913,   915,   915,   920,   915,   923,   924,
     925,   926,   928,   929,   930,   931,   932,   934,   935,   936,
     937,   938,   939,   940,   941,   943,   944,   946,   947,   948,
     949,   950,   952,   952,   953,   954,   956,   965,   956,   980,
     981,   983,   983,   983,  1028,  1028,  1029,  1030,  1031,  1031,
    1034,  1035,  1037,  1037,  1038,  1038,  1039,  1040,  1041,  1042,
    1044,  1045,  1046,  1048,  1049,  1050,  1050,  1072,  1073,  1074,
    1074,  1086,  1087,  1088,  1089,  1089,  1108,  1123,  1108,  1139,
    1140,  1142,  1142,  1149,  1149,  1156,  1156,  1157,  1159,  1161,
    1162,  1161,  1183,  1183,  1189,  1189,  1194,  1195,  1196,  1197,
    1198,  1199,  1201,  1202,  1202,  1203,  1204,  1205,  1205,  1236,
    1237,  1239,  1239,  1244,  1244,  1245,  1247,  1247,  1252,  1252,
    1253,  1255,  1255,  1260,  1261,  1262,  1262,  1263,  1263,  1264,
    1265,  1266,  1270,  1273,  1272,  1277,  1277,  1278,  1278,  1279,
    1282,  1281,  1287,  1287,  1288,  1288,  1289,  1291,  1292,  1293,
    1294,  1294,  1304,  1305,  1306,  1312,  1313,  1314,  1315,  1315,
    1316,  1316,  1344,  1348,  1349,  1350
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
  "regresa", "$@15", "$@16", "asignacion", "$@17", "asignacionp", "asigp",
  "$@18", "lea", "ap", "$@19", "$@20", "maiap", "miap", "atipo",
  "condicion", "c", "$@21", "condicion_exp", "sip", "$@22", "sipp", "cp",
  "$@23", "cuandop", "$@24", "$@25", "cuandopp", "escritura", "$@26",
  "escriturap", "$@27", "e", "$@28", "lectura", "ciclo", "$@29", "$@30",
  "accion", "$@31", "accionsi", "$@32", "acciones", "params", "paramsp",
  "$@33", "paramspp", "params2", "$@34", "params2p", "mmexp", "$@35",
  "mmexpp", "$@36", "mexp", "$@37", "mexpp", "$@38", "expresion", "$@39",
  "expresionp", "ep", "$@40", "$@41", "epp", "exp", "$@42", "expp", "$@43",
  "$@44", "termino", "$@45", "terminop", "$@46", "$@47", "factor",
  "factorp", "$@48", "nf", "factorpp", "f", "factorppp", "$@49", "fun_var",
  "$@50", "varselecciona", 0
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
      92,    94,    95,    93,    97,    96,    98,    98,   100,    99,
     101,   101,   103,   102,   104,   102,   105,   105,   106,   106,
     107,   107,   107,   108,   108,   110,   109,   111,   111,   113,
     112,   112,   114,   114,   116,   115,   118,   119,   117,   120,
     120,   122,   121,   124,   123,   126,   125,   125,   127,   129,
     130,   128,   132,   131,   134,   133,   135,   135,   135,   135,
     135,   135,   136,   138,   137,   139,   139,   141,   140,   142,
     142,   144,   143,   146,   145,   145,   148,   147,   150,   149,
     149,   152,   151,   153,   153,   155,   154,   156,   154,   154,
     154,   157,   157,   159,   158,   161,   160,   162,   160,   160,
     164,   163,   166,   165,   167,   165,   165,   168,   168,   168,
     170,   169,   171,   171,   172,   173,   173,   173,   175,   174,
     177,   176,   176,   178,   178,   178
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
       0,     0,     0,     5,     0,     3,     1,     1,     0,     3,
       1,     1,     0,     3,     0,     3,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     0,     9,     1,     1,     0,
       3,     0,     1,     3,     0,     8,     0,     0,    10,     1,
       0,     0,     6,     0,     3,     0,     3,     0,     3,     0,
       0,     9,     0,     5,     0,     4,     1,     1,     1,     1,
       1,     1,     2,     0,     3,     2,     0,     0,     3,     2,
       0,     0,     3,     0,     3,     0,     0,     3,     0,     3,
       0,     0,     3,     2,     0,     0,     3,     0,     3,     1,
       2,     1,     0,     0,     3,     0,     3,     0,     3,     0,
       0,     3,     0,     3,     0,     3,     0,     1,     1,     1,
       0,     5,     1,     0,     2,     1,     1,     0,     0,     3,
       0,     4,     0,     1,     1,     1
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
      39,    36,    33,   187,    38,    41,     0,     0,    32,     0,
     186,   185,   188,    16,    19,    20,   141,   146,   151,   163,
     170,   177,     0,   178,     0,   179,   126,   127,   128,   129,
     130,   131,     0,   119,     0,     0,    62,     0,    41,    57,
      58,    93,    94,    59,    60,    61,   122,     0,   133,   132,
       0,   192,    22,   145,   150,   154,   169,   176,   180,    52,
      51,    53,    54,    49,    48,    50,    47,   184,   187,     0,
     187,   187,    74,    37,    40,     0,    26,   136,   118,   190,
     189,     0,    17,   143,   142,   148,   147,     0,   155,   157,
     159,   152,   187,   165,   167,   164,   172,   174,   171,   187,
      95,    98,   124,    97,   187,     0,     0,   113,    66,    63,
      64,    65,     0,     0,    26,    29,     0,   134,   187,    21,
     187,   187,   160,   162,   162,   153,   187,   187,   187,   187,
       0,     0,     0,     0,     0,   111,   117,   187,    78,    82,
      84,     0,    76,    77,     0,    25,     0,     0,   135,     0,
      69,   137,   144,   149,   161,   156,   158,   166,   168,   173,
     175,   181,     0,     0,     0,   104,     0,   115,   114,     0,
     187,     0,     0,    75,   123,    24,    71,    29,    55,    56,
     191,   140,    41,   125,   120,     0,   112,   187,    67,    79,
      80,    81,     0,    86,    83,     0,    88,    85,   187,    30,
     187,   138,     0,    41,     0,     0,   116,     0,    91,    92,
      90,    87,    89,    72,   139,   101,     0,   193,   195,   194,
     106,   105,    68,     0,    99,    96,   121,     0,    73,     0,
       0,    41,   102,   100,     0,     0,    41,   103,     0,   107,
     110,   109,   108
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    13,    14,    20,    15,    24,    29,
      34,    35,    43,    92,    53,   122,    21,    37,   155,    26,
     186,   187,    46,    18,    25,    36,    45,    41,    77,    16,
     107,   217,    78,    79,   112,   149,   150,   177,   247,   189,
     219,   238,   263,   151,   152,   181,   182,   210,   229,   183,
     211,   212,   234,   237,   251,    80,    81,   171,   140,   265,
     269,   273,    82,   225,   245,   267,   280,   282,    83,   206,
     146,   176,   208,   227,    54,    84,   109,   243,    85,   115,
     141,   172,    86,    48,    89,   117,   157,   190,   221,   241,
      55,    93,   124,   160,    56,    94,   126,   161,    57,    95,
     131,   132,   163,   164,   195,    58,    96,   135,   166,   167,
      59,    97,   138,   168,   169,    60,    61,   139,    62,    63,
      64,    65,    91,   120,   158,   260
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -109
static const yytype_int16 yypact[] =
{
    -109,    18,    -9,  -109,    -7,  -109,    12,    60,  -109,  -109,
    -109,  -109,  -109,    25,    39,    60,    20,  -109,  -109,    60,
    -109,    39,  -109,  -109,    40,    42,    47,  -109,  -109,   -25,
    -109,  -109,  -109,    20,  -109,    55,    60,    59,  -109,  -109,
      60,  -109,    60,    49,  -109,    26,    62,    58,  -109,    69,
      72,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    75,  -109,    63,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    81,  -109,    84,    86,  -109,    92,    26,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,    94,  -109,  -109,
      89,    95,   101,   107,   110,    44,    11,    50,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,    57,    98,
      80,    80,    99,  -109,  -109,   100,    60,   111,  -109,  -109,
    -109,    20,  -109,  -109,  -109,  -109,  -109,   105,  -109,  -109,
    -109,  -109,    80,  -109,  -109,  -109,  -109,  -109,  -109,    80,
    -109,  -109,  -109,  -109,    80,   103,   104,  -109,  -109,  -109,
    -109,  -109,   -17,   106,    60,   113,    60,  -109,    76,  -109,
      80,    80,  -109,   114,   114,  -109,    80,    80,    80,    80,
     108,   112,   115,   116,   117,  -109,   119,    76,  -109,  -109,
    -109,   120,  -109,  -109,   122,  -109,   121,     7,  -109,   118,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,   124,   125,   126,  -109,   129,  -109,  -109,   127,
      49,     2,     0,  -109,  -109,  -109,  -109,   113,  -109,  -109,
    -109,   131,    26,  -109,  -109,   130,  -109,    80,  -109,  -109,
    -109,  -109,     1,  -109,  -109,     1,  -109,  -109,    80,  -109,
      80,  -109,   128,    26,    16,   132,  -109,   137,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,   160,   136,  -109,  -109,  -109,
    -109,  -109,  -109,   140,  -109,  -109,  -109,   138,  -109,     6,
     139,    26,  -109,  -109,   141,   142,    26,  -109,   143,  -109,
     130,  -109,  -109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,  -109,  -109,   159,   161,   -31,   -27,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,    27,  -109,
     -37,  -109,  -109,  -109,  -109,  -109,  -109,   144,   -78,   -18,
    -109,  -109,    -4,  -109,  -109,  -109,  -109,  -109,  -109,     8,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,   -49,   -82,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,   -92,  -109,  -109,  -109,  -109,  -109,
     -38,  -109,  -109,  -109,   -20,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    83,    36,  -109,  -109,  -109,   -46,  -109,  -109,
    -104,  -109,  -109,  -109,    34,  -109,  -109,  -109,    64,  -109,
    -109,  -109,  -109,  -109,    33,  -108,  -109,  -109,  -109,  -109,
     -66,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -184
static const yytype_int16 yytable[] =
{
     114,    27,   145,   147,   143,    40,    38,    33,   -18,    40,
      66,    67,    68,    69,    70,    71,    72,    72,     3,    73,
     178,     4,    74,    74,    47,   216,   179,   180,    75,    66,
      67,    68,    69,    70,    71,   170,    72,   235,    73,   232,
     173,   271,    74,     5,   236,   233,     7,    75,    17,   248,
     191,   249,    19,   250,   133,   134,   192,    76,   197,   198,
      66,    67,    68,    69,    70,    71,   257,   258,   259,   191,
      23,    49,    99,    30,     8,     9,    76,    31,    50,    10,
      11,   127,   128,   129,   130,   154,    50,   100,   101,   102,
    -183,    12,    39,    51,   159,   136,   137,    32,  -183,    52,
      42,    51,   199,   200,    87,    50,   231,    52,    88,    50,
      90,   103,   104,  -182,   105,   106,    98,  -183,   -70,   147,
      51,  -183,   108,   154,    51,   110,    52,   111,   113,   116,
      52,   118,   191,   121,   253,   123,   119,   125,    47,   144,
     148,   153,   162,   156,   242,   174,   175,   244,   184,   -31,
     201,   194,   205,   213,   202,   214,   203,   215,   204,   222,
     220,   224,   226,   240,   255,   256,   207,   223,   261,   228,
     262,   264,   266,   268,    22,   270,   276,   274,   277,   279,
     239,   185,    28,   218,    44,   209,   252,   272,   281,   246,
     230,   142,   188,   275,   254,   193,   165,   196,   278
};

static const yytype_uint16 yycheck[] =
{
      78,    19,   110,   111,   108,    36,    33,    32,    33,    40,
       3,     4,     5,     6,     7,     8,    10,    10,     0,    12,
      37,    30,    16,    16,    42,    18,    43,    44,    21,     3,
       4,     5,     6,     7,     8,   139,    10,    37,    12,    37,
     144,    35,    16,    50,    44,    43,    34,    21,    23,    48,
     158,    50,    13,    52,    43,    44,   160,    50,   166,   167,
       3,     4,     5,     6,     7,     8,    50,    51,    52,   177,
      50,    22,     9,    33,    14,    15,    50,    35,    29,    19,
      20,    37,    38,    39,    40,   116,    29,    24,    25,    26,
      41,    31,    37,    44,   121,    45,    46,    50,    41,    50,
      41,    44,   168,   169,    42,    29,   210,    50,    50,    29,
      41,    48,    49,    41,    51,    52,    41,    41,    42,   227,
      44,    41,    41,   154,    44,    41,    50,    41,    36,    35,
      50,    42,   240,    32,   238,    28,    41,    27,   156,    41,
      41,    41,    37,    32,   222,    42,    42,    17,    42,    36,
      42,    37,    35,    33,    42,    33,    41,    36,    42,    35,
      42,    35,    33,    32,    36,   243,    47,    42,    36,    42,
      33,    11,    36,    33,    15,    37,    35,    38,    36,    36,
     217,   154,    21,   187,    40,   177,   235,   269,   280,   227,
     210,   108,   156,   271,   240,   161,   132,   164,   276
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,    55,     0,    30,    50,    56,    34,    14,    15,
      19,    20,    31,    57,    58,    60,    82,    23,    76,    13,
      59,    69,    58,    50,    61,    77,    72,    82,    59,    62,
      33,    35,    50,    32,    63,    64,    78,    70,    61,    37,
      60,    80,    41,    65,    80,    79,    75,    82,   136,    22,
      29,    44,    50,    67,   127,   143,   147,   151,   158,   163,
     168,   169,   171,   172,   173,   174,     3,     4,     5,     6,
       7,     8,    10,    12,    16,    21,    50,    81,    85,    86,
     108,   109,   115,   121,   128,   131,   135,    42,    50,   137,
      41,   175,    66,   144,   148,   152,   159,   164,    41,     9,
      24,    25,    26,    48,    49,    51,    52,    83,    41,   129,
      41,    41,    87,    36,    81,   132,    35,   138,    42,    41,
     176,    32,    68,    28,   145,    27,   149,    37,    38,    39,
      40,   153,   154,    43,    44,   160,    45,    46,   165,   170,
     111,   133,   135,   143,    41,   158,   123,   158,    41,    88,
      89,    96,    97,    41,    60,    71,    32,   139,   177,    61,
     146,   150,    37,   155,   156,   151,   161,   162,   166,   167,
     143,   110,   134,   143,    42,    42,   124,    90,    37,    43,
      44,    98,    99,   102,    42,    71,    73,    74,   136,    92,
     140,   158,   143,   147,    37,   157,   157,   158,   158,   163,
     163,    42,    42,    41,    42,    35,   122,    47,   125,    92,
     100,   103,   104,    33,    33,    36,    18,    84,    85,    93,
      42,   141,    35,    42,    35,   116,    33,   126,    42,   101,
     127,   143,    37,    43,   105,    37,    44,   106,    94,    73,
      32,   142,    81,   130,    17,   117,   123,    91,    48,    50,
      52,   107,   107,   143,   140,    36,    81,    50,    51,    52,
     178,    36,    33,    95,    11,   112,    36,   118,    33,   113,
      37,    35,   108,   114,    38,    81,    35,    36,    81,    36,
     119,   117,   120
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
#line 843 "parser.y"
    {generar_cuadruplo(21,-1,-1,-1);/*goto del main*/ ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 843 "parser.y"
    {tipo_actual = 'V'; insert_proc_to_table("programa");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 851 "parser.y"
    {id_a_verificar = yylval.str; insert_var_to_table(yylval.str,proc_actual);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 853 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 853 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 853 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 863 "parser.y"
    {
	//Regla 35
	insert_proc_to_table(yylval.str);
	bandera_return = 0;
	/*Regla 46*/ 
	if(tipo_funcion_actual != 'V'){
		insert_var_to_table(proc_actual,"programa");
	}
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 871 "parser.y"
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

	//Checar si hubo return
	if(bandera_return == 0 && tipo_funcion_actual != 'V'){
		printf("Error: En la función %s no contiene regresa \n",proc_actual);
		exit(1);
	}
	if(tipo_funcion_actual == 'V' && bandera_return == 1){
		printf("Error: En la función %s no debe haber regresa\n",proc_actual);
		exit(1);
	}

	//Generar cuadruplo de RET
	if(tipo_funcion_actual == 'V'){
		printf("Genera cuadruplo RET\n");
		generar_cuadruplo_funcion(27,-1,-1,-1);
	}
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 905 "parser.y"
    {
		tipo_funcion_actual = tipo_actual;
		
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 909 "parser.y"
    {tipo_funcion_actual= 'V';;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 910 "parser.y"
    {insert_dir_inicial();;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 915 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 915 "parser.y"
    {
		//Rellenar goto inicial del main con el contador de cuadruplos
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_peek_nth(cuadruplos,0);
		tmp->destino = contador_cuadruplos;
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 920 "parser.y"
    {
		insert_dir_inicial();
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 928 "parser.y"
    {tipo_actual= 'I';;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 929 "parser.y"
    {tipo_actual= 'F';;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 930 "parser.y"
    {tipo_actual= 'C';;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 931 "parser.y"
    {tipo_actual= 'S';;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 932 "parser.y"
    {tipo_actual= 'L';;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 934 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 935 "parser.y"
    {insert_constante_to_table(yylval.str,3);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 936 "parser.y"
    {insert_constante_to_table(yylval.str,2);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 937 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 940 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 941 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 952 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 956 "parser.y"
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
#line 965 "parser.y"
    {
			//Regla 39
			char *func = g_queue_peek_head(PFunciones);
			funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)func);
	
			g_queue_pop_head(PFunciones);
			int contador_parametros = g_queue_pop_head(PParametros);
			if(g_queue_get_length(ft->parametros) != contador_parametros){
				printf("Error: Menos parámetros de los esperados en la linea %d\n",yylineno);
				exit(1);
			}
			//Regla 40
			generar_cuadruplo_funcion(24,func,ft->dir_inicial,-1);
			;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 983 "parser.y"
    {bandera_return = 1;;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 983 "parser.y"
    {
	//Regla 45
	int expresion = g_queue_pop_head(POperandos);
	int tipoexp = g_queue_pop_head(PTipos) - 1;

	if(tipo_funcion_actual == 'V'){
		printf("Error: En la función %s no debe haber regresa\n",proc_actual);
		exit(1);
	}
	
	if(tipoexp != traduce_tipo(tipo_funcion_actual)){
		printf("Error: Se espera un valor de tipo %s en el regresa en la linea %d\n",traduce_tipo2(traduce_tipo(tipo_funcion_actual) + 1),yylineno);
		exit(1);
	}

	//Generar cuadruplo de RETURN
	printf("Genera cuadruplo RETURN\n");
	generar_cuadruplo_funcion(35,expresion,-1,-1);

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
		printf("Error: Se espera un valor de tipo %s en el regresa en la linea %d\n",traduce_tipo2(traduce_tipo(tipo_funcion_actual) + 1),yylineno);
		exit(1);
	}else{
		generar_cuadruplo(19,expresion,-1,global->dir_virtual);
		
	}

	//Generar cuadruplo de RET
	printf("Genera cuadruplo RET\n");
	generar_cuadruplo_funcion(27,-1,-1,-1);
	
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1028 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1031 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1031 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1037 "parser.y"
    {g_queue_push_head(POperadores,1);/*operador +*/;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1038 "parser.y"
    {g_queue_push_head(POperadores,4);/*operador -*/;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1039 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1040 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1041 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1042 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1044 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1045 "parser.y"
    {insert_constante_to_table(yylval.integer,2);;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1046 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1050 "parser.y"
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

  case 96:

/* Line 1455 of yacc.c  */
#line 1063 "parser.y"
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

  case 99:

/* Line 1455 of yacc.c  */
#line 1074 "parser.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 1089 "parser.y"
    {
		g_queue_push_head(PSwitch,0);		
		;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1091 "parser.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 1108 "parser.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 1123 "parser.y"
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

  case 111:

/* Line 1455 of yacc.c  */
#line 1142 "parser.y"
    {
		//Regla 26
		int operando1 = (int)g_queue_pop_head(POperandos);	
		int tipo1 = g_queue_pop_head(PTipos);
		printf("Genera cuadruplo de escribe\n");
		generar_cuadruplo(34,operando1,-1,-1);
		;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1149 "parser.y"
    { 
		//Regla 27
		if(g_queue_peek_head(POperadores) == 9){
		printf("Genera cuadruplo .\n");
		generar_cuadruplo_expresion();		
		};}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1156 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,9);/*operador concatenacion(.)*/;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1159 "parser.y"
    {insert_constante_to_table("Lectura de pantalla",3);;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1161 "parser.y"
    {g_queue_push_head(PSaltos,contador_cuadruplos); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1162 "parser.y"
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
#line 1172 "parser.y"
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
#line 1183 "parser.y"
    {
	//Regla 41
	printf("Genera cuadruplo de accion\n");
	generar_cuadruplo(accion,-1,-1,-1);
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1189 "parser.y"
    {
	//Regla 41
	printf("Genera cuadruplo de accion\n");
	generar_cuadruplo(accion,-1,-1,-1);	
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1194 "parser.y"
    {accion = 28;;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1195 "parser.y"
    {accion = 29;;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1196 "parser.y"
    {accion = 30;;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1197 "parser.y"
    {accion = 31;;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1198 "parser.y"
    {accion = 32;;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1199 "parser.y"
    {accion = 33;;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1202 "parser.y"
    {insert_param_tipo();insert_var_to_table(yylval.str,proc_actual);/*Regla 103*/;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1205 "parser.y"
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

	//Regla 38
	int p = g_queue_pop_head(PParametros);
	p++;
	g_queue_push_head(PParametros,p);
	
	;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1239 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 17){
  			printf("Genera cuadruplo or \n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1244 "parser.y"
    {g_queue_push_head(POperadores,17);/*operador or*/;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1247 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 16){
  			printf("Genera cuadruplo and /\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1252 "parser.y"
    {g_queue_push_head(POperadores,16);/*operador and*/;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1255 "parser.y"
    {
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
  			printf("Genera cuadruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1262 "parser.y"
    {g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1263 "parser.y"
    {g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1264 "parser.y"
    {g_queue_push_head(POperadores,11);/*operador diferente*/;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1265 "parser.y"
    {g_queue_push_head(POperadores,15);/*operador igual igual*/;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1266 "parser.y"
    {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1273 "parser.y"
    {if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1277 "parser.y"
    {g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1278 "parser.y"
    {g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1282 "parser.y"
    {if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1287 "parser.y"
    {g_queue_push_head(POperadores,7);/*operador multiplica*/;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1288 "parser.y"
    {g_queue_push_head(POperadores,8);/*operador division*/;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1294 "parser.y"
    {g_queue_push_head(POperadores,'(');;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1294 "parser.y"
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

  case 182:

/* Line 1455 of yacc.c  */
#line 1304 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1306 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		printf("Genera cuadruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1312 "parser.y"
    {g_queue_push_head(POperadores,20);/*operador multiplica*/;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1313 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1315 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1316 "parser.y"
    {
		verifica_existe_procs(id_a_verificar);
					
		//Regla 36
		g_queue_push_head(PFunciones,id_a_verificar);
		//ERA
		generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
		g_queue_push_head(PParametros,0);
			
	;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1325 "parser.y"
    {
		verifica_existe_procs(id_a_verificar);
		//Regla 39
		char *func = g_queue_peek_head(PFunciones);
		funcion *ft = g_hash_table_lookup(dir_procs,(gpointer)func);
	
		g_queue_pop_head(PFunciones);
		int contador_parametros = g_queue_pop_head(PParametros);
		
		if(g_queue_get_length(ft->parametros) != contador_parametros){
			printf("Error: Menos parámetros de los esperados en la linea %d\n",yylineno);
			exit(1);
		}
		//Regla 40
		generar_cuadruplo_funcion(24,func,ft->dir_inicial,-1);

		//Regla 47
		inserta_procs_factor(id_a_verificar);
	;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1344 "parser.y"
    {verifica_existe_var(id_a_verificar);
         	
         	;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1348 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1350 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 3480 "parser.tab.c"
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
#line 1353 "parser.y"
 
main() { 
objeto = fopen("codigo.obj", "w");
crear_pilas_tablas();
  yyparse(); 
//Impreison del directorio de procedimeintos en consola
imprime(dir_procs); 

//Generar cuadruplo final END
generar_cuadruplo(36,-1,-1,-1);



//Escirbir el directorio de procedimientos
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


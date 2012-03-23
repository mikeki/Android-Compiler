
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

int traduce_tipo(char tipo);

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
	tabla_constantes = g_hash_table_new(g_str_hash, g_str_equal);
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
		printf("ALta Variable: %s %d\n",name, virtual);
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
	variable *local = g_slice_new(variable);
	variable *global = g_slice_new(variable);
	local = g_hash_table_lookup(tabla->var_table,(gpointer)name);
	if(local == NULL){
		funcion *tabla = g_hash_table_lookup(dir_procs,"programa");
		global = g_hash_table_lookup(tabla->var_table,(gpointer)name);
		if(global == NULL){
			printf("Error de Semantica variable %s no declarada\n",name);
			exit(1);
		}else{
		  g_queue_push_head(PTipos,traduce_tipo(global->tipo)+1);
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

	char tnuevo = cubo[tipo1-1][tipo2-1][operador];
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
		g_queue_push_head(PTipos,traduce_tipo(tnuevo)+1);
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
Descripcion: Imprime el resultado de lo que se guardo en una tabla

Parametros: GHashTable *a
Salida:void
*/
void imprime(GHashTable *a){
	printf("Lista:");
	g_hash_table_foreach(a,(GHFunc)printf,NULL);
	
	
	printf("\n");
	
	
}



/* Line 189 of yacc.c  */
#line 668 "parser.tab.c"

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
#line 594 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 764 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 776 "parser.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   239

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNRULES -- Number of states.  */
#define YYNSTATES  256

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
       0,     0,     3,     4,    11,    14,    17,    18,    21,    22,
      26,    27,    31,    34,    38,    39,    41,    43,    46,    47,
      48,    58,    61,    62,    64,    65,    66,    72,    75,    76,
      78,    80,    82,    84,    86,    88,    90,    92,    94,    96,
      98,   100,   102,   104,   106,   108,   110,   112,   114,   116,
     118,   119,   123,   125,   127,   128,   134,   136,   137,   141,
     142,   146,   148,   150,   153,   155,   157,   159,   161,   164,
     167,   171,   175,   177,   179,   181,   183,   185,   194,   196,
     198,   201,   202,   204,   208,   216,   225,   227,   228,   234,
     236,   239,   242,   245,   246,   250,   258,   264,   266,   267,
     272,   274,   276,   278,   280,   282,   284,   287,   288,   292,
     295,   297,   298,   301,   304,   305,   306,   310,   311,   315,
     316,   317,   321,   322,   326,   327,   328,   332,   335,   336,
     337,   341,   342,   346,   348,   351,   353,   354,   355,   359,
     360,   364,   365,   369,   370,   371,   375,   376,   380,   381,
     385,   386,   388,   390,   392,   393,   399,   401,   402,   405,
     407,   409,   410,   411,   415,   419,   420,   422,   424
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      54,     0,    -1,    -1,    30,    50,    55,    34,    56,    69,
      -1,    57,    58,    -1,    59,    57,    -1,    -1,    65,    58,
      -1,    -1,    72,    60,    33,    -1,    -1,    50,    61,    62,
      -1,    32,    60,    -1,    37,    63,    64,    -1,    -1,   104,
      -1,   116,    -1,    32,    60,    -1,    -1,    -1,    13,    50,
      66,    41,    68,    42,    35,    67,    36,    -1,    74,    67,
      -1,    -1,   110,    -1,    -1,    -1,    23,    70,    35,    71,
      36,    -1,    75,    71,    -1,    -1,    14,    -1,    15,    -1,
      31,    -1,    20,    -1,    19,    -1,    52,    -1,    49,    -1,
      48,    -1,    51,    -1,    24,    -1,     9,    -1,    25,    -1,
      26,    -1,    75,    -1,    82,    -1,    76,    -1,    92,    -1,
     100,    -1,   105,    -1,   106,    -1,    59,    -1,    -1,    50,
      77,    78,    -1,    79,    -1,    83,    -1,    -1,    41,    81,
      42,    80,    33,    -1,   114,    -1,    -1,    18,   116,    33,
      -1,    -1,    85,    84,    33,    -1,    86,    -1,    88,    -1,
      37,    87,    -1,   104,    -1,   116,    -1,    89,    -1,    90,
      -1,    43,    43,    -1,    44,    44,    -1,    43,    37,    91,
      -1,    44,    37,    91,    -1,    52,    -1,    48,    -1,    50,
      -1,    93,    -1,    97,    -1,    10,    41,    94,    42,    35,
      71,    36,    95,    -1,   116,    -1,   108,    -1,    11,    96,
      -1,    -1,    92,    -1,    35,    71,    36,    -1,    16,    41,
     131,    42,    35,    98,    36,    -1,    17,   150,    37,    38,
      35,    71,    36,    99,    -1,    98,    -1,    -1,    21,    41,
     101,    42,    33,    -1,   102,    -1,    73,   103,    -1,   131,
     103,    -1,    47,   102,    -1,    -1,    22,    41,    42,    -1,
      12,    41,   116,    42,    35,    71,    36,    -1,   109,    41,
     107,    42,    33,    -1,   114,    -1,    -1,   109,    41,   107,
      42,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,    72,   111,    -1,    -1,    50,   112,
     113,    -1,    32,   111,    -1,   110,    -1,    -1,   131,   115,
      -1,    32,   114,    -1,    -1,    -1,   120,   117,   118,    -1,
      -1,    28,   119,   116,    -1,    -1,    -1,   124,   121,   122,
      -1,    -1,    27,   123,   120,    -1,    -1,    -1,   131,   125,
     126,    -1,   127,   124,    -1,    -1,    -1,    38,   128,   130,
      -1,    -1,    39,   129,   130,    -1,    40,    -1,    37,    37,
      -1,    37,    -1,    -1,    -1,   136,   132,   133,    -1,    -1,
      43,   134,   131,    -1,    -1,    44,   135,   131,    -1,    -1,
      -1,   141,   137,   138,    -1,    -1,    45,   139,   136,    -1,
      -1,    46,   140,   136,    -1,    -1,   142,    -1,   145,    -1,
     147,    -1,    -1,   144,    41,   143,   116,    42,    -1,    29,
      -1,    -1,   146,    73,    -1,    44,    -1,    29,    -1,    -1,
      -1,    50,   148,   149,    -1,    41,    81,    42,    -1,    -1,
      50,    -1,    52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   614,   614,   614,   615,   616,   617,   618,   619,   621,
     622,   622,   623,   624,   625,   626,   627,   628,   629,   631,
     631,   632,   633,   634,   635,   637,   637,   639,   640,   642,
     643,   644,   645,   646,   648,   649,   650,   651,   652,   653,
     654,   655,   657,   658,   660,   661,   662,   663,   664,   665,
     667,   667,   668,   669,   671,   671,   673,   674,   676,   678,
     678,   679,   680,   681,   682,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   694,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   704,   705,   706,   708,   709,
     710,   711,   712,   713,   715,   717,   719,   720,   721,   722,
     723,   724,   725,   726,   727,   728,   730,   731,   731,   732,
     733,   734,   735,   736,   737,   739,   739,   743,   743,   744,
     746,   746,   750,   750,   751,   753,   753,   757,   758,   759,
     759,   760,   760,   761,   762,   763,   767,   770,   769,   774,
     774,   775,   775,   776,   779,   778,   784,   784,   785,   785,
     786,   788,   789,   790,   791,   791,   800,   801,   802,   807,
     808,   809,   810,   810,   811,   812,   822,   823,   824
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
  "$accept", "programa", "$@1", "programap", "programapp", "programappp",
  "vars", "vars_id", "$@2", "varsip", "var_init", "var_initp", "funcion",
  "$@3", "funcionp", "funcionpp", "main", "$@4", "bloque", "tipo",
  "varcte", "estatutofuncion", "estatuto", "empieza_id", "$@5",
  "empieza_idp", "ejecuta_funcion", "$@6", "paramsf", "regresa",
  "asignacion", "$@7", "asignacionp", "asigp", "lea", "asigpp", "ap",
  "app", "atipo", "condicion", "c", "condicion_exp", "sip", "sipp", "cp",
  "cuandop", "cuandopp", "escritura", "escriturap", "escriturapp", "e",
  "lectura", "ciclo", "accion", "accionp", "accionsi", "acciones",
  "params", "paramsp", "$@8", "paramspp", "params2", "params2p", "mmexp",
  "$@9", "mmexpp", "$@10", "mexp", "$@11", "mexpp", "$@12", "expresion",
  "$@13", "expresionp", "ep", "$@14", "$@15", "epp", "exp", "$@16", "expp",
  "$@17", "$@18", "termino", "$@19", "terminop", "$@20", "$@21", "factor",
  "factorp", "$@22", "nf", "factorpp", "f", "factorppp", "$@23", "fun_var",
  "varselecciona", 0
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
       0,    53,    55,    54,    56,    57,    57,    58,    58,    59,
      61,    60,    62,    62,    62,    63,    63,    64,    64,    66,
      65,    67,    67,    68,    68,    70,    69,    71,    71,    72,
      72,    72,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      77,    76,    78,    78,    80,    79,    81,    81,    82,    84,
      83,    85,    85,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    91,    92,    92,    93,    94,    94,
      95,    95,    96,    96,    97,    98,    99,    99,   100,   101,
     102,   102,   103,   103,   104,   105,   106,   107,   107,   108,
     109,   109,   109,   109,   109,   109,   110,   112,   111,   113,
     113,   113,   114,   115,   115,   117,   116,   119,   118,   118,
     121,   120,   123,   122,   122,   125,   124,   126,   126,   128,
     127,   129,   127,   127,   127,   130,   130,   132,   131,   134,
     133,   135,   133,   133,   137,   136,   139,   138,   140,   138,
     138,   141,   141,   141,   143,   142,   144,   144,   145,   146,
     146,   146,   148,   147,   149,   149,   150,   150,   150
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     2,     2,     0,     2,     0,     3,
       0,     3,     2,     3,     0,     1,     1,     2,     0,     0,
       9,     2,     0,     1,     0,     0,     5,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     1,     0,     5,     1,     0,     3,     0,
       3,     1,     1,     2,     1,     1,     1,     1,     2,     2,
       3,     3,     1,     1,     1,     1,     1,     8,     1,     1,
       2,     0,     1,     3,     7,     8,     1,     0,     5,     1,
       2,     2,     2,     0,     3,     7,     5,     1,     0,     4,
       1,     1,     1,     1,     1,     1,     2,     0,     3,     2,
       1,     0,     2,     2,     0,     0,     3,     0,     3,     0,
       0,     3,     0,     3,     0,     0,     3,     2,     0,     0,
       3,     0,     3,     1,     2,     1,     0,     0,     3,     0,
       3,     0,     3,     0,     0,     3,     0,     3,     0,     3,
       0,     1,     1,     1,     0,     5,     1,     0,     2,     1,
       1,     0,     0,     3,     3,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,    29,    30,    33,
      32,    31,     0,     8,     6,     0,    25,     3,     0,     4,
       8,     5,    10,     0,     0,    19,     7,    14,     9,    28,
       0,     0,   161,    11,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,    50,    49,     0,    28,    44,    45,
      75,    76,    46,    47,    48,     0,    24,    12,     0,   160,
     159,   162,    18,    15,    16,   115,   120,   125,   137,   144,
     151,     0,   152,     0,   153,   161,   161,   161,   157,     0,
      26,    27,   161,     0,     0,    23,     0,   165,     0,    13,
     119,   124,   128,   143,   150,   154,    39,    38,    40,    41,
      36,    35,    37,    34,   158,     0,    79,     0,    78,     0,
       0,    93,     0,    89,    93,   161,   161,     0,     0,    51,
      52,    53,    59,    61,    62,    66,    67,     0,    97,   114,
       0,   107,   106,    94,   161,   163,    17,   117,   116,   122,
     121,     0,   129,   131,   133,   126,   161,   139,   141,   138,
     146,   148,   145,   161,     0,   161,     0,     0,   157,    90,
       0,    91,    63,    64,    65,     0,    56,     0,    68,     0,
      69,     0,     0,   161,   112,    22,   111,     0,   161,   161,
     134,   136,   136,   127,   161,   161,   161,   161,     0,    28,
       0,    28,     0,    92,    88,    54,    73,    74,    72,    70,
      71,    60,    96,   113,   161,     0,    22,    42,    43,     0,
     110,   108,   164,   118,   123,   135,   130,   132,   140,   142,
     147,   149,   155,     0,    99,     0,     0,     0,     0,     0,
      20,    21,   109,    81,    95,   166,   168,   167,     0,    84,
      55,    58,     0,    77,     0,    28,    82,    80,     0,     0,
      28,    83,     0,    87,    86,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    12,    13,    19,    45,    23,    27,    33,
      62,    89,    20,    30,   205,    83,    17,    24,    46,    15,
     111,   206,    47,    48,    79,   119,   120,   228,   165,   208,
     121,   171,   122,   123,   162,   124,   125,   126,   199,    49,
      50,   105,   243,   247,    51,   227,   255,    52,   112,   113,
     159,    63,    53,    54,   127,   106,    55,    85,   132,   176,
     211,   128,   174,    64,    90,   138,   178,    65,    91,   140,
     179,    66,    92,   145,   146,   181,   182,   216,    67,    93,
     149,   184,   185,    68,    94,   152,   186,   187,    69,    70,
     153,    71,    72,    73,    74,    87,   135,   238
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -168
static const yytype_int16 yypact[] =
{
       6,    -1,    58,  -168,  -168,    32,   153,  -168,  -168,  -168,
    -168,  -168,    57,    83,   153,    48,  -168,  -168,    55,  -168,
      83,  -168,  -168,    76,    82,  -168,  -168,    13,  -168,    87,
      88,    48,    15,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
      93,    94,    97,    98,  -168,  -168,    92,    87,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,    99,   153,  -168,   100,   102,
    -168,  -168,   113,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,   105,  -168,   101,  -168,    26,    33,    33,   107,    10,
    -168,  -168,    31,   112,   114,  -168,   120,   106,    48,  -168,
      96,   147,    49,    25,    74,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,   133,  -168,   135,  -168,   136,
     137,   130,   138,  -168,   130,    15,   119,    41,    -2,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,   139,  -168,   154,
     150,  -168,  -168,  -168,   119,  -168,  -168,  -168,  -168,  -168,
    -168,   152,  -168,  -168,  -168,  -168,    33,  -168,  -168,  -168,
    -168,  -168,  -168,    33,   155,    31,   156,   157,   107,  -168,
     160,  -168,  -168,  -168,  -168,   145,  -168,   -32,  -168,   -32,
    -168,   161,   162,    33,  -168,     7,   151,   146,    33,    33,
    -168,   159,   159,  -168,    33,    33,    33,    33,   158,    87,
     163,    87,   180,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,    33,   165,     7,  -168,  -168,   114,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,   166,  -168,   168,    63,   170,   174,   175,
    -168,  -168,  -168,   188,  -168,  -168,  -168,  -168,   172,  -168,
    -168,  -168,    36,  -168,   173,    87,  -168,  -168,   177,   178,
      87,  -168,   179,   180,  -168,  -168
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,  -168,  -168,   196,   193,    34,   -24,  -168,  -168,
    -168,  -168,  -168,  -168,    11,  -168,  -168,  -168,   -47,   -53,
     143,  -168,  -167,  -168,  -168,  -168,  -168,  -168,    84,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,    50,   -22,
    -168,  -168,  -168,  -168,  -168,   -31,  -168,  -168,  -168,    65,
     110,   111,  -168,  -168,    66,  -168,   164,    51,    16,  -168,
    -168,  -110,  -168,   -74,  -168,  -168,  -168,    52,  -168,  -168,
    -168,    86,  -168,  -168,  -168,  -168,  -168,    46,   -73,  -168,
    -168,  -168,  -168,   -65,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -158
static const yytype_int16 yytable[] =
{
      81,   108,   109,    84,   110,   114,   166,    57,   207,   129,
      34,    35,    36,    37,    38,    39,   196,    40,   197,    41,
     198,     7,     8,    42,   166,   204,     9,    10,    43,    34,
      35,    36,    37,    38,    39,   169,     1,    58,    11,   207,
      14,   164,   170,   129,    59,    31,    40,   115,    14,     3,
      32,   116,    42,   117,   118,    59,  -157,    44,     4,    60,
      59,   129,    59,   203,   136,    61,     6,  -157,   147,   148,
      60,   245,  -157,   -98,  -157,    60,    61,    60,   167,   188,
      16,    61,   129,    61,   168,   114,   141,   142,   143,   144,
      34,    35,    36,    37,    38,    39,    18,    40,    22,    41,
     129,     7,     8,    42,   213,    25,     9,    10,    43,    28,
      96,   218,   219,   235,   236,   237,    96,    29,    11,   150,
     151,   220,   221,    84,   137,    97,    98,    99,    80,    56,
     229,    97,    98,    99,    75,    76,    59,    44,    77,    78,
      82,    86,   223,  -156,   225,    88,    95,   134,    59,   100,
     101,    60,   102,   103,   130,   100,   101,    61,   102,   103,
    -157,   -57,   133,    60,   131,     7,     8,     7,     8,    61,
       9,    10,     9,    10,   139,   154,   155,   158,   156,   157,
     160,   172,    11,   209,    11,   175,   173,   195,   212,   180,
     189,   191,   192,   194,   201,   202,   215,   226,   249,   242,
     222,   230,   233,   252,   234,   224,   239,   240,   241,   244,
      21,   248,   250,    26,   251,   253,   104,   231,   177,   200,
     246,   190,   254,   193,   161,   232,   163,   210,   217,     0,
       0,   214,   183,     0,     0,     0,     0,     0,     0,   107
};

static const yytype_int16 yycheck[] =
{
      47,    75,    76,    56,    77,    78,   116,    31,   175,    82,
       3,     4,     5,     6,     7,     8,    48,    10,    50,    12,
      52,    14,    15,    16,   134,    18,    19,    20,    21,     3,
       4,     5,     6,     7,     8,    37,    30,    22,    31,   206,
       6,   115,    44,   116,    29,    32,    10,    37,    14,    50,
      37,    41,    16,    43,    44,    29,    41,    50,     0,    44,
      29,   134,    29,   173,    88,    50,    34,    41,    43,    44,
      44,    35,    41,    42,    41,    44,    50,    44,    37,   153,
      23,    50,   155,    50,    43,   158,    37,    38,    39,    40,
       3,     4,     5,     6,     7,     8,    13,    10,    50,    12,
     173,    14,    15,    16,   178,    50,    19,    20,    21,    33,
       9,   184,   185,    50,    51,    52,     9,    35,    31,    45,
      46,   186,   187,   176,    28,    24,    25,    26,    36,    41,
     204,    24,    25,    26,    41,    41,    29,    50,    41,    41,
      41,    41,   189,    41,   191,    32,    41,    41,    29,    48,
      49,    44,    51,    52,    42,    48,    49,    50,    51,    52,
      41,    42,    42,    44,    50,    14,    15,    14,    15,    50,
      19,    20,    19,    20,    27,    42,    41,    47,    42,    42,
      42,    42,    31,    32,    31,    35,    32,    42,    42,    37,
      35,    35,    35,    33,    33,    33,    37,    17,   245,    11,
      42,    36,    36,   250,    36,    42,    36,    33,    33,    37,
      14,    38,    35,    20,    36,    36,    73,   206,   134,   169,
     242,   155,   253,   158,   114,   209,   115,   176,   182,    -1,
      -1,   179,   146,    -1,    -1,    -1,    -1,    -1,    -1,    75
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    54,    50,     0,    55,    34,    14,    15,    19,
      20,    31,    56,    57,    59,    72,    23,    69,    13,    58,
      65,    57,    50,    60,    70,    50,    58,    61,    33,    35,
      66,    32,    37,    62,     3,     4,     5,     6,     7,     8,
      10,    12,    16,    21,    50,    59,    71,    75,    76,    92,
      93,    97,   100,   105,   106,   109,    41,    60,    22,    29,
      44,    50,    63,   104,   116,   120,   124,   131,   136,   141,
     142,   144,   145,   146,   147,    41,    41,    41,    41,    77,
      36,    71,    41,    68,    72,   110,    41,   148,    32,    64,
     117,   121,   125,   132,   137,    41,     9,    24,    25,    26,
      48,    49,    51,    52,    73,    94,   108,   109,   116,   116,
     131,    73,   101,   102,   131,    37,    41,    43,    44,    78,
      79,    83,    85,    86,    88,    89,    90,   107,   114,   131,
      42,    50,   111,    42,    41,   149,    60,    28,   118,    27,
     122,    37,    38,    39,    40,   126,   127,    43,    44,   133,
      45,    46,   138,   143,    42,    41,    42,    42,    47,   103,
      42,   103,    87,   104,   116,    81,   114,    37,    43,    37,
      44,    84,    42,    32,   115,    35,   112,    81,   119,   123,
      37,   128,   129,   124,   134,   135,   139,   140,   116,    35,
     107,    35,    35,   102,    33,    42,    48,    50,    52,    91,
      91,    33,    33,   114,    18,    67,    74,    75,    82,    32,
     110,   113,    42,   116,   120,    37,   130,   130,   131,   131,
     136,   136,    42,    71,    42,    71,    17,    98,    80,   116,
      36,    67,   111,    36,    36,    50,    51,    52,   150,    36,
      33,    33,    11,    95,    37,    35,    92,    96,    38,    71,
      35,    36,    71,    36,    98,    99
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
#line 614 "parser.y"
    {insert_proc_to_table("programa");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 622 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 631 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 637 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 642 "parser.y"
    {tipo_actual= 'I';;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 643 "parser.y"
    {tipo_actual= 'F';;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 644 "parser.y"
    {tipo_actual= 'C';;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 645 "parser.y"
    {tipo_actual= 'S';;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 646 "parser.y"
    {tipo_actual= 'L';;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 648 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 649 "parser.y"
    {insert_constante_to_table(yylval.str,2);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 650 "parser.y"
    {insert_constante_to_table(yylval.str,3);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 651 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 654 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 655 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 667 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 671 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 678 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 690 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 691 "parser.y"
    {insert_constante_to_table(yylval.integer,2);;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 692 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 731 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 739 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 17){
			generar_cuadruplo_expresion();		
	};}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 743 "parser.y"
    {g_queue_push_head(POperadores,17);/*operador or*/;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 746 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 16){
			generar_cuadruplo_expresion();		
	};}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 750 "parser.y"
    {g_queue_push_head(POperadores,16);/*operador and*/;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 753 "parser.y"
    {
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
			generar_cuadruplo_expresion();		
	};}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 759 "parser.y"
    {g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 760 "parser.y"
    {g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 761 "parser.y"
    {g_queue_push_head(POperadores,11);/*operador diferente*/;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 762 "parser.y"
    {g_queue_push_head(POperadores,15);/*operador igual igual*/;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 763 "parser.y"
    {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 770 "parser.y"
    {if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 774 "parser.y"
    {g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 775 "parser.y"
    {g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 779 "parser.y"
    {if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 784 "parser.y"
    {g_queue_push_head(POperadores,7);/*operador multiplica*/;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 785 "parser.y"
    {g_queue_push_head(POperadores,8);/*operador division*/;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 791 "parser.y"
    {g_queue_push_head(POperadores,'(');;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 791 "parser.y"
    {if(g_queue_peek_head(POperadores) == '('){
		g_queue_pop_head(POperadores);
		}else{
			printf("Mala construccion de expresion");
		};
		if(g_queue_peek_head(POperadores) == 18){
			generar_cuadruplo_expresion_unaria();
		}
		;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 800 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 802 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 807 "parser.y"
    {g_queue_push_head(POperadores,20);/*operador multiplica*/;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 808 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 810 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 811 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 812 "parser.y"
    {verifica_existe_var(id_a_verificar);
         	//Obteniendo el tipo de variable en la tabla d evariables
		funcion *tabla = g_slice_new(funcion);
		tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
		variable *var = g_slice_new(variable);
		var = g_hash_table_lookup(tabla->var_table,(gpointer)id_a_verificar);
		g_queue_push_head(POperandos,var->dir_virtual);
		g_queue_push_head(PTipos,traduce_tipo(var->tipo)+1);
         	;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 822 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 823 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 824 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 2617 "parser.tab.c"
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
#line 827 "parser.y"
 
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


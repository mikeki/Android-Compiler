
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
extern int yylineno;
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
CUBO SEMANTICO
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
	cuadruplos = g_queue_new();
}

/*
Descripcion: Funcion que se encarga de insetrar un procedimiento, programa global
y la rutina principal

Parametros: char * name
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
Descripcion: Inserta una variable en el proceso actual en su tabla de 
variables correspondiente.

Parametros: char *name
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
Descripcion: Verificar en el directorio de procedimientos si existe el procedimiento
mandado como parametro.Regresa error de semantica si no cumple.

Parametros: char *name
Salida: void
*/
void verifica_existe_procs(char *name){
	if(g_hash_table_lookup(dir_procs,(gpointer)name) == NULL){
		printf("Error: Función %s no declarada en la línea %d\n",name,yylineno);
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
Descripcion: Función que se encarga de regresar el string correspondiente
del tipo que se le etsa mandando como paramtero

Parametros: int tipo
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
Descripcion: Función que se encaraga de escribir en un arhcivo de codigo
objeto los cuadruplos que reciba.

Parametros: int operador, int operando1, int operando2, int resultadotmp
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
Descripcion: Se encarga de obtener los opendos, tipos d eoperandos
y el operador para generar el cuadruplo para asignacionde variables 
asimsmo durante la declaracion de variables se distingue por no usar
temporales.

Parametros: 
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
	if(tnuevo == 'E'){
		
		printf("Error: No se puede hacer la asignación de %s a %s en la línea %d \n",traduce_tipo2(tipo2),traduce_tipo2(tipo1),yylineno);
		exit(1);
	}else{
		
		generar_cuadruplo(operador,operando2,-1,operando1);
		
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
	printf("op1: %d ", operando1);
	int operador = g_queue_pop_head(POperadores);
	printf("oper: %d ", operador);
	int tipo1 = g_queue_pop_head(PTipos);
	printf("tipo1: %d\n", tipo1);

	if(operador == 1 || operador == 4){
		operador++;
	}

	char tnuevo = cubo[operador-1][tipo1-1][5];
	if(tnuevo == 'E'){
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
#line 781 "parser.tab.c"

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
#line 707 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 877 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 889 "parser.tab.c"

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
#define YYLAST   234

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  114
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNRULES -- Number of states.  */
#define YYNSTATES  272

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
      26,    27,    31,    34,    35,    36,    37,    44,    45,    47,
      49,    52,    53,    54,    65,    67,    68,    71,    72,    74,
      75,    76,    82,    85,    86,    88,    90,    92,    94,    96,
      98,   100,   102,   104,   106,   108,   110,   112,   114,   116,
     118,   120,   122,   124,   126,   128,   129,   133,   135,   137,
     138,   144,   146,   147,   151,   152,   156,   158,   160,   161,
     165,   167,   169,   170,   174,   175,   179,   181,   184,   186,
     189,   191,   193,   195,   197,   199,   200,   210,   212,   214,
     215,   219,   220,   222,   226,   234,   235,   236,   247,   249,
     250,   251,   258,   259,   263,   265,   267,   268,   272,   273,
     277,   278,   279,   289,   295,   297,   298,   303,   305,   307,
     309,   311,   313,   315,   318,   319,   323,   326,   328,   329,
     332,   335,   336,   337,   341,   342,   346,   347,   348,   352,
     353,   357,   358,   359,   363,   366,   367,   368,   372,   373,
     377,   379,   382,   384,   385,   386,   390,   391,   395,   396,
     400,   401,   402,   406,   407,   411,   412,   416,   417,   419,
     421,   423,   424,   430,   432,   433,   436,   438,   440,   441,
     442,   446,   450,   451,   453,   455
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      54,     0,    -1,    -1,    30,    50,    55,    34,    56,    73,
      -1,    57,    58,    -1,    59,    57,    -1,    -1,    68,    58,
      -1,    -1,    76,    60,    33,    -1,    -1,    50,    61,    62,
      -1,    32,    60,    -1,    -1,    -1,    -1,    63,    37,    64,
      66,    65,    67,    -1,    -1,   118,    -1,   132,    -1,    32,
      60,    -1,    -1,    -1,    13,    70,    50,    69,    41,    72,
      42,    35,    71,    36,    -1,    76,    -1,    -1,    78,    71,
      -1,    -1,   126,    -1,    -1,    -1,    23,    74,    35,    75,
      36,    -1,    79,    75,    -1,    -1,    14,    -1,    15,    -1,
      31,    -1,    20,    -1,    19,    -1,    52,    -1,    49,    -1,
      48,    -1,    51,    -1,    24,    -1,     9,    -1,    25,    -1,
      26,    -1,    79,    -1,    86,    -1,    80,    -1,    99,    -1,
     111,    -1,   119,    -1,   122,    -1,    59,    -1,    -1,    50,
      81,    82,    -1,    83,    -1,    87,    -1,    -1,    41,    85,
      42,    84,    33,    -1,   130,    -1,    -1,    18,   132,    33,
      -1,    -1,    88,    89,    33,    -1,    90,    -1,    93,    -1,
      -1,    37,    91,    92,    -1,   118,    -1,   132,    -1,    -1,
      43,    94,    96,    -1,    -1,    44,    95,    97,    -1,    43,
      -1,    37,    98,    -1,    44,    -1,    37,    98,    -1,    52,
      -1,    48,    -1,    50,    -1,   100,    -1,   106,    -1,    -1,
      10,    41,   102,   101,    42,    35,    75,    36,   103,    -1,
     132,    -1,   124,    -1,    -1,    11,   104,   105,    -1,    -1,
      99,    -1,    35,    75,    36,    -1,    16,    41,   147,    42,
      35,   107,    36,    -1,    -1,    -1,    17,   166,   108,    37,
      38,    35,    75,    36,   109,   110,    -1,   107,    -1,    -1,
      -1,    21,    41,   113,    42,   112,    33,    -1,    -1,   115,
     114,   116,    -1,    77,    -1,   147,    -1,    -1,    47,   117,
     113,    -1,    -1,    22,    41,    42,    -1,    -1,    -1,    12,
     120,    41,   132,    42,    35,   121,    75,    36,    -1,   125,
      41,   123,    42,    33,    -1,   130,    -1,    -1,   125,    41,
     123,    42,    -1,     3,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,    76,   127,    -1,    -1,    50,
     128,   129,    -1,    32,   127,    -1,   126,    -1,    -1,   147,
     131,    -1,    32,   130,    -1,    -1,    -1,   136,   133,   134,
      -1,    -1,    28,   135,   132,    -1,    -1,    -1,   140,   137,
     138,    -1,    -1,    27,   139,   136,    -1,    -1,    -1,   147,
     141,   142,    -1,   143,   140,    -1,    -1,    -1,    38,   144,
     146,    -1,    -1,    39,   145,   146,    -1,    40,    -1,    37,
      37,    -1,    37,    -1,    -1,    -1,   152,   148,   149,    -1,
      -1,    43,   150,   147,    -1,    -1,    44,   151,   147,    -1,
      -1,    -1,   157,   153,   154,    -1,    -1,    45,   155,   152,
      -1,    -1,    46,   156,   152,    -1,    -1,   158,    -1,   161,
      -1,   163,    -1,    -1,   160,    41,   159,   132,    42,    -1,
      29,    -1,    -1,   162,    77,    -1,    44,    -1,    29,    -1,
      -1,    -1,    50,   164,   165,    -1,    41,    85,    42,    -1,
      -1,    50,    -1,    52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   727,   727,   727,   728,   729,   730,   731,   732,   734,
     735,   735,   736,   737,   737,   737,   737,   741,   742,   743,
     744,   745,   747,   747,   748,   749,   750,   751,   752,   753,
     755,   755,   757,   758,   760,   761,   762,   763,   764,   766,
     767,   768,   769,   770,   771,   772,   773,   775,   776,   778,
     779,   780,   781,   782,   783,   785,   785,   786,   787,   789,
     789,   791,   792,   794,   796,   796,   797,   798,   799,   799,
     802,   803,   805,   805,   806,   806,   807,   808,   809,   810,
     812,   813,   814,   816,   817,   818,   818,   841,   842,   843,
     843,   855,   856,   857,   858,   871,   886,   871,   898,   899,
     901,   901,   906,   906,   911,   912,   913,   913,   914,   916,
     918,   919,   918,   940,   941,   942,   943,   944,   945,   946,
     947,   948,   949,   951,   952,   952,   953,   954,   955,   956,
     957,   958,   960,   960,   965,   965,   966,   968,   968,   973,
     973,   974,   976,   976,   981,   982,   983,   983,   984,   984,
     985,   986,   987,   991,   994,   993,   998,   998,   999,   999,
    1000,  1003,  1002,  1008,  1008,  1009,  1009,  1010,  1012,  1013,
    1014,  1015,  1015,  1025,  1026,  1027,  1033,  1034,  1035,  1036,
    1036,  1037,  1038,  1051,  1052,  1053
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
  "vars", "vars_id", "$@2", "varsip", "$@3", "$@4", "$@5", "var_init",
  "var_initp", "funcion", "$@6", "tipof", "funcionp", "funcionpp", "main",
  "$@7", "bloque", "tipo", "varcte", "estatutofuncion", "estatuto",
  "empieza_id", "$@8", "empieza_idp", "ejecuta_funcion", "$@9", "paramsf",
  "regresa", "asignacion", "$@10", "asignacionp", "asigp", "$@11", "lea",
  "ap", "$@12", "$@13", "maiap", "miap", "atipo", "condicion", "c", "$@14",
  "condicion_exp", "sip", "$@15", "sipp", "cp", "cuandop", "$@16", "$@17",
  "cuandopp", "escritura", "$@18", "escriturap", "$@19", "escriturapp",
  "e", "$@20", "lectura", "ciclo", "$@21", "$@22", "accion", "accionp",
  "accionsi", "acciones", "params", "paramsp", "$@23", "paramspp",
  "params2", "params2p", "mmexp", "$@24", "mmexpp", "$@25", "mexp", "$@26",
  "mexpp", "$@27", "expresion", "$@28", "expresionp", "ep", "$@29", "$@30",
  "epp", "exp", "$@31", "expp", "$@32", "$@33", "termino", "$@34",
  "terminop", "$@35", "$@36", "factor", "factorp", "$@37", "nf",
  "factorpp", "f", "factorppp", "$@38", "fun_var", "varselecciona", 0
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
      61,    60,    62,    63,    64,    65,    62,    62,    66,    66,
      67,    67,    69,    68,    70,    70,    71,    71,    72,    72,
      74,    73,    75,    75,    76,    76,    76,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    79,
      79,    79,    79,    79,    79,    81,    80,    82,    82,    84,
      83,    85,    85,    86,    88,    87,    89,    89,    91,    90,
      92,    92,    94,    93,    95,    93,    96,    96,    97,    97,
      98,    98,    98,    99,    99,   101,   100,   102,   102,   104,
     103,   103,   105,   105,   106,   108,   109,   107,   110,   110,
     112,   111,   114,   113,   115,   115,   117,   116,   116,   118,
     120,   121,   119,   122,   123,   123,   124,   125,   125,   125,
     125,   125,   125,   126,   128,   127,   129,   129,   129,   130,
     131,   131,   133,   132,   135,   134,   134,   137,   136,   139,
     138,   138,   141,   140,   142,   142,   144,   143,   145,   143,
     143,   143,   146,   146,   148,   147,   150,   149,   151,   149,
     149,   153,   152,   155,   154,   156,   154,   154,   157,   157,
     157,   159,   158,   160,   160,   161,   162,   162,   162,   164,
     163,   165,   165,   166,   166,   166
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     2,     2,     0,     2,     0,     3,
       0,     3,     2,     0,     0,     0,     6,     0,     1,     1,
       2,     0,     0,    10,     1,     0,     2,     0,     1,     0,
       0,     5,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     1,     1,     0,
       5,     1,     0,     3,     0,     3,     1,     1,     0,     3,
       1,     1,     0,     3,     0,     3,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     0,     9,     1,     1,     0,
       3,     0,     1,     3,     7,     0,     0,    10,     1,     0,
       0,     6,     0,     3,     1,     1,     0,     3,     0,     3,
       0,     0,     9,     5,     1,     0,     4,     1,     1,     1,
       1,     1,     1,     2,     0,     3,     2,     1,     0,     2,
       2,     0,     0,     3,     0,     3,     0,     0,     3,     0,
       3,     0,     0,     3,     2,     0,     0,     3,     0,     3,
       1,     2,     1,     0,     0,     3,     0,     3,     0,     3,
       0,     0,     3,     0,     3,     0,     3,     0,     1,     1,
       1,     0,     5,     1,     0,     2,     1,     1,     0,     0,
       3,     3,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,    34,    35,    38,
      37,    36,     0,     8,     6,     0,    30,     3,    25,     4,
       8,     5,    10,     0,     0,     0,    24,     7,    13,     9,
      33,    22,     0,    11,     0,   117,   118,   119,   120,   121,
     122,     0,   110,     0,     0,    55,    54,     0,    33,    49,
      50,    83,    84,    51,    52,    53,     0,     0,    12,    14,
     178,     0,   178,   174,    64,    31,    32,   178,    29,   178,
     177,   176,   179,    85,    88,     0,    87,   132,   137,   142,
     154,   161,   168,     0,   169,     0,   170,   178,     0,    44,
      43,    45,    46,    41,    40,    42,    39,   104,     0,   102,
     105,   178,    56,    57,    58,     0,     0,   114,   131,     0,
       0,    28,     0,    15,    18,    19,   182,     0,   178,   136,
     141,   145,   160,   167,   171,   175,     0,     0,   100,   108,
       0,    61,    68,    72,    74,     0,    66,    67,     0,   178,
     129,     0,   124,   123,     0,    21,   178,   180,     0,     0,
     134,   133,   139,   138,     0,   146,   148,   150,   143,   178,
     156,   158,   155,   163,   165,   162,   178,     0,     0,     0,
     106,   103,    59,   178,     0,     0,    65,   113,   130,    27,
     128,   109,     0,    16,     0,    33,   116,   178,   178,   151,
     153,   153,   144,   178,   178,   178,   178,     0,   111,     0,
       0,   101,   174,     0,    69,    70,    71,     0,    76,    73,
       0,    78,    75,   178,     0,    27,    47,    48,     0,   127,
     125,    20,   181,     0,   135,   140,   152,   147,   149,   157,
     159,   164,   166,   172,    33,   183,   185,   184,    95,    94,
     107,    60,    81,    82,    80,    77,    79,     0,    23,    26,
     126,    91,     0,     0,    63,    89,    86,   112,     0,     0,
       0,    33,    92,    90,    33,     0,     0,    93,    96,    99,
      98,    97
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    12,    13,    19,    46,    23,    28,    33,
      34,    69,   145,   113,   183,    20,    57,    25,   214,   109,
      17,    24,    47,    15,    97,   215,    48,    49,    64,   102,
     103,   203,   130,   217,   104,   105,   135,   136,   173,   204,
     137,   174,   175,   209,   212,   245,    50,    51,   117,    73,
     256,   259,   263,    52,   200,   253,   269,   271,    53,   169,
      98,   129,    99,   171,   202,   114,    54,    61,   234,    55,
     106,    74,    56,   111,   143,   180,   220,   107,   140,    76,
     119,   151,   187,    77,   120,   153,   188,    78,   121,   158,
     159,   190,   191,   227,    79,   122,   162,   193,   194,    80,
     123,   165,   195,   196,    81,    82,   166,    83,    84,    85,
      86,   116,   147,   238
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -174
static const yytype_int16 yypact[] =
{
      32,    16,    67,  -174,  -174,    48,   142,  -174,  -174,  -174,
    -174,  -174,    53,    80,   142,    51,  -174,  -174,   142,  -174,
      80,  -174,  -174,    75,    83,    70,  -174,  -174,   -25,  -174,
      49,  -174,    51,  -174,    87,  -174,  -174,  -174,  -174,  -174,
    -174,    84,  -174,    98,   100,  -174,  -174,    92,    49,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,   101,   108,  -174,  -174,
      42,   119,   114,    65,   127,  -174,  -174,   104,   142,    90,
     128,  -174,  -174,  -174,  -174,   129,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,   130,  -174,    78,  -174,   114,   132,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,   133,  -174,
    -174,   109,  -174,  -174,  -174,    41,   134,  -174,   140,   135,
      82,  -174,   137,  -174,  -174,  -174,   138,   139,   104,   152,
     155,    58,   -11,   -10,  -174,  -174,   141,   149,  -174,   143,
     145,  -174,  -174,  -174,  -174,   156,  -174,  -174,   158,   114,
    -174,   150,  -174,  -174,   146,   160,   109,  -174,   159,   151,
    -174,  -174,  -174,  -174,   161,  -174,  -174,  -174,  -174,   114,
    -174,  -174,  -174,  -174,  -174,  -174,   114,   162,   178,   163,
    -174,  -174,  -174,    90,    -6,   -27,  -174,  -174,  -174,     8,
      91,  -174,    51,  -174,   157,    49,  -174,   114,   114,  -174,
     164,   164,  -174,   114,   114,   114,   114,   165,  -174,   115,
     166,  -174,    65,   167,  -174,  -174,  -174,    25,  -174,  -174,
      25,  -174,  -174,   114,   168,     8,  -174,  -174,    82,  -174,
    -174,  -174,  -174,   169,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,    49,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,   170,  -174,  -174,
    -174,   195,   172,   173,  -174,  -174,  -174,  -174,   171,     9,
     176,    49,  -174,  -174,    49,   179,   181,  -174,  -174,   178,
    -174,  -174
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,  -174,  -174,   198,   194,    24,   -30,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,     3,  -174,
    -174,  -174,   -48,   -17,   136,  -174,  -173,  -174,  -174,  -174,
    -174,  -174,    73,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,    10,   -37,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   -46,  -174,  -174,  -174,  -174,  -174,
      22,  -174,  -174,  -174,  -174,    52,  -174,  -174,  -174,  -174,
     110,  -174,   174,    46,    11,  -174,  -174,   -67,  -174,   -66,
    -174,  -174,  -174,    39,  -174,  -174,  -174,    71,  -174,  -174,
    -174,  -174,  -174,    40,   -58,  -174,  -174,  -174,  -174,  -155,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -175
static const yytype_int16 yytable[] =
{
      66,    26,    58,   115,    88,   100,   216,    32,   -17,   108,
     210,    35,    36,    37,    38,    39,    40,   211,    41,    41,
      42,   126,     7,     8,    43,    43,   213,     9,    10,    44,
      14,   207,   160,   161,   131,   163,   164,   208,    14,    11,
     231,   232,   216,   108,   261,    35,    36,    37,    38,    39,
      40,   110,    35,    36,    37,    38,    39,    40,    45,    41,
     108,    42,     1,     7,     8,    43,     3,     4,     9,    10,
      44,    70,   178,   242,    89,   243,    16,   244,   132,   131,
      11,   108,     6,  -174,   133,   134,    71,    89,   108,    90,
      91,    92,    72,    18,    70,   154,   155,   156,   157,    45,
     197,    22,    90,    91,    92,     7,     8,   206,    29,    71,
       9,    10,   112,    93,    94,    72,    95,    96,    30,    70,
      31,   224,    11,   218,    59,    60,    93,    94,    65,    95,
      96,  -174,   142,    70,    71,   229,   230,   223,    70,    62,
      72,    63,    67,    70,   100,  -174,  -115,   247,    71,    68,
    -174,   -62,   221,    71,    72,  -174,     7,     8,    71,    72,
      87,     9,    10,   110,    72,   235,   236,   237,   101,  -173,
     118,   124,   139,    11,   127,   128,   138,   141,   144,   146,
     150,   148,   152,   167,   168,   179,   252,   172,   181,   176,
     170,   177,   182,   186,   185,   199,   201,   198,   189,   222,
     241,   226,   239,   254,   248,   251,   255,   233,   257,   260,
     258,   264,    21,   265,    27,   267,   266,   268,   249,   184,
     246,   125,   262,   270,   240,   205,   219,   225,   149,   250,
     192,   228,     0,     0,    75
};

static const yytype_int16 yycheck[] =
{
      48,    18,    32,    69,    62,    63,   179,    32,    33,    67,
      37,     3,     4,     5,     6,     7,     8,    44,    10,    10,
      12,    87,    14,    15,    16,    16,    18,    19,    20,    21,
       6,    37,    43,    44,   101,    45,    46,    43,    14,    31,
     195,   196,   215,   101,    35,     3,     4,     5,     6,     7,
       8,    68,     3,     4,     5,     6,     7,     8,    50,    10,
     118,    12,    30,    14,    15,    16,    50,     0,    19,    20,
      21,    29,   139,    48,     9,    50,    23,    52,    37,   146,
      31,   139,    34,    41,    43,    44,    44,     9,   146,    24,
      25,    26,    50,    13,    29,    37,    38,    39,    40,    50,
     166,    50,    24,    25,    26,    14,    15,   173,    33,    44,
      19,    20,    22,    48,    49,    50,    51,    52,    35,    29,
      50,   187,    31,    32,    37,    41,    48,    49,    36,    51,
      52,    41,    50,    29,    44,   193,   194,   185,    29,    41,
      50,    41,    41,    29,   202,    41,    42,   213,    44,    41,
      41,    42,   182,    44,    50,    41,    14,    15,    44,    50,
      41,    19,    20,   180,    50,    50,    51,    52,    41,    41,
      41,    41,    32,    31,    42,    42,    42,    42,    41,    41,
      28,    42,    27,    42,    35,    35,   234,    42,    42,    33,
      47,    33,    32,    42,    35,    17,    33,    35,    37,    42,
      33,    37,    36,    33,    36,    36,    11,    42,    36,    38,
      37,    35,    14,   261,    20,    36,   264,    36,   215,   146,
     210,    85,   259,   269,   202,   173,   180,   188,   118,   218,
     159,   191,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    54,    50,     0,    55,    34,    14,    15,    19,
      20,    31,    56,    57,    59,    76,    23,    73,    13,    58,
      68,    57,    50,    60,    74,    70,    76,    58,    61,    33,
      35,    50,    32,    62,    63,     3,     4,     5,     6,     7,
       8,    10,    12,    16,    21,    50,    59,    75,    79,    80,
      99,   100,   106,   111,   119,   122,   125,    69,    60,    37,
      41,   120,    41,    41,    81,    36,    75,    41,    41,    64,
      29,    44,    50,   102,   124,   125,   132,   136,   140,   147,
     152,   157,   158,   160,   161,   162,   163,    41,   147,     9,
      24,    25,    26,    48,    49,    51,    52,    77,   113,   115,
     147,    41,    82,    83,    87,    88,   123,   130,   147,    72,
      76,   126,    22,    66,   118,   132,   164,   101,    41,   133,
     137,   141,   148,   153,    41,    77,   132,    42,    42,   114,
      85,   130,    37,    43,    44,    89,    90,    93,    42,    32,
     131,    42,    50,   127,    41,    65,    41,   165,    42,   123,
      28,   134,    27,   138,    37,    38,    39,    40,   142,   143,
      43,    44,   149,    45,    46,   154,   159,    42,    35,   112,
      47,   116,    42,    91,    94,    95,    33,    33,   130,    35,
     128,    42,    32,    67,    85,    35,    42,   135,   139,    37,
     144,   145,   140,   150,   151,   155,   156,   132,    35,    17,
     107,    33,   117,    84,    92,   118,   132,    37,    43,    96,
      37,    44,    97,    18,    71,    78,    79,    86,    32,   126,
     129,    60,    42,    75,   132,   136,    37,   146,   146,   147,
     147,   152,   152,    42,   121,    50,    51,    52,   166,    36,
     113,    33,    48,    50,    52,    98,    98,   132,    36,    71,
     127,    36,    75,   108,    33,    11,   103,    36,    37,   104,
      38,    35,    99,   105,    35,    75,    75,    36,    36,   109,
     107,   110
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
#line 727 "parser.y"
    {insert_proc_to_table("programa");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 735 "parser.y"
    {id_a_verificar = yylval.str; insert_var_to_table(yylval.str);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 737 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 737 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 737 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 747 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 749 "parser.y"
    {tipo_actual= 'V';;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 755 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 760 "parser.y"
    {tipo_actual= 'I';;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 761 "parser.y"
    {tipo_actual= 'F';;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 762 "parser.y"
    {tipo_actual= 'C';;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 763 "parser.y"
    {tipo_actual= 'S';;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 764 "parser.y"
    {tipo_actual= 'L';;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 766 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 767 "parser.y"
    {insert_constante_to_table(yylval.str,3);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 768 "parser.y"
    {insert_constante_to_table(yylval.str,2);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 769 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 772 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 773 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 785 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 789 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 799 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 799 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 805 "parser.y"
    {g_queue_push_head(POperadores,1);/*operador +*/;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 806 "parser.y"
    {g_queue_push_head(POperadores,4);/*operador -*/;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 807 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 808 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 809 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 810 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 812 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 813 "parser.y"
    {insert_constante_to_table(yylval.integer,2);;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 814 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 818 "parser.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 832 "parser.y"
    {
		int final = g_queue_pop_head(PSaltos);
		//printf("salto %d\n",final);
		//Rellenar goto con el contador de cuadruplos para el final
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,(guint)final-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,final-1);
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 843 "parser.y"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 858 "parser.y"
    {
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
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 871 "parser.y"
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

  case 96:

/* Line 1455 of yacc.c  */
#line 886 "parser.y"
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
	;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 901 "parser.y"
    {
		int operando1 = (int)g_queue_pop_head(POperandos);	
		int tipo1 = g_queue_pop_head(PTipos);
		generar_cuadruplo(25,operando1,-1,-1);
		;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 906 "parser.y"
    { if(g_queue_peek_head(POperadores) == 9){
		printf("Genera cuadruplo .\n");
		generar_cuadruplo_expresion();		
		};}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 913 "parser.y"
    {g_queue_push_head(POperadores,9);/*operador concatenacion(.)*/;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
    {insert_constante_to_table("Lectura de pantalla",3);;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 918 "parser.y"
    {g_queue_push_head(PSaltos,contador_cuadruplos); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 919 "parser.y"
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

  case 112:

/* Line 1455 of yacc.c  */
#line 929 "parser.y"
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

  case 124:

/* Line 1455 of yacc.c  */
#line 952 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 960 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 17){
  			printf("Genera cuadruplo or \n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 965 "parser.y"
    {g_queue_push_head(POperadores,17);/*operador or*/;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 968 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 16){
  			printf("Genera cuadruplo and /\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 973 "parser.y"
    {g_queue_push_head(POperadores,16);/*operador and*/;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 976 "parser.y"
    {
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
  			printf("Genera cuadruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 983 "parser.y"
    {g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 984 "parser.y"
    {g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 985 "parser.y"
    {g_queue_push_head(POperadores,11);/*operador diferente*/;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 986 "parser.y"
    {g_queue_push_head(POperadores,15);/*operador igual igual*/;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 987 "parser.y"
    {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 994 "parser.y"
    {if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 998 "parser.y"
    {g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 999 "parser.y"
    {g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1003 "parser.y"
    {if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1008 "parser.y"
    {g_queue_push_head(POperadores,7);/*operador multiplica*/;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1009 "parser.y"
    {g_queue_push_head(POperadores,8);/*operador division*/;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
    {g_queue_push_head(POperadores,'(');;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
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

  case 173:

/* Line 1455 of yacc.c  */
#line 1025 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1027 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		printf("Genera cuadruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1033 "parser.y"
    {g_queue_push_head(POperadores,20);/*operador multiplica*/;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1034 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1036 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1037 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1038 "parser.y"
    {verifica_existe_var(id_a_verificar);
         	//Obteniendo el tipo de variable en la tabla d evariables
		/*
		funcion *tabla = g_slice_new(funcion);
		tabla = g_hash_table_lookup(dir_procs,(gpointer)proc_actual);
		variable *var = g_slice_new(variable);
		var = g_hash_table_lookup(tabla->var_table,(gpointer)id_a_verificar);
		
		g_queue_push_head(POperandos,var->dir_virtual);
		g_queue_push_head(PTipos,traduce_tipo(var->tipo)+1);
		*/
         	;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1051 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1052 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1053 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 3036 "parser.tab.c"
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
#line 1056 "parser.y"
 
main() { 
objeto = fopen("codigo.obj", "w");
crear_pilas_tablas();
  yyparse(); 
imprime(dir_procs); 



//Escirbri en el arhcivo los cuadruplos
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


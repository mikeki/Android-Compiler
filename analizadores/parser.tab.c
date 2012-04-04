
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
static GQueue *PSwitch;

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
	g_queue_push_tail(proc->parametros,tipo_actual);

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
#line 840 "parser.tab.c"

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
#line 766 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 936 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 948 "parser.tab.c"

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
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  119
/* YYNRULES -- Number of rules.  */
#define YYNRULES  191
/* YYNRULES -- Number of states.  */
#define YYNSTATES  280

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
      49,    52,    53,    54,    66,    69,    70,    72,    73,    74,
      78,    79,    81,    82,    83,    84,    92,    95,    96,    99,
     100,   102,   104,   106,   108,   110,   112,   114,   116,   118,
     120,   122,   124,   126,   128,   130,   132,   134,   136,   138,
     140,   141,   145,   147,   149,   150,   156,   158,   159,   163,
     164,   168,   170,   172,   173,   177,   179,   181,   182,   186,
     187,   191,   193,   196,   198,   201,   203,   205,   207,   209,
     211,   212,   222,   224,   226,   227,   231,   232,   234,   238,
     239,   248,   249,   250,   261,   263,   264,   265,   272,   273,
     277,   279,   281,   282,   286,   287,   291,   292,   293,   303,
     309,   311,   312,   317,   319,   321,   323,   325,   327,   329,
     332,   333,   337,   340,   342,   343,   346,   349,   350,   351,
     355,   356,   360,   361,   362,   366,   367,   371,   372,   373,
     377,   380,   381,   382,   386,   387,   391,   393,   396,   398,
     399,   400,   404,   405,   409,   410,   414,   415,   416,   420,
     421,   425,   426,   430,   431,   433,   435,   437,   438,   444,
     446,   447,   450,   452,   454,   455,   456,   460,   464,   465,
     467,   469
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      54,     0,    -1,    -1,    30,    50,    55,    34,    56,    75,
      -1,    57,    58,    -1,    59,    57,    -1,    -1,    68,    58,
      -1,    -1,    80,    60,    33,    -1,    -1,    50,    61,    62,
      -1,    32,    60,    -1,    -1,    -1,    -1,    63,    37,    64,
      66,    65,    67,    -1,    -1,   123,    -1,   137,    -1,    32,
      60,    -1,    -1,    -1,    13,    71,    50,    69,    41,    74,
      42,    35,    70,    72,    36,    -1,    59,    70,    -1,    -1,
      80,    -1,    -1,    -1,    73,    82,    72,    -1,    -1,   131,
      -1,    -1,    -1,    -1,    23,    76,    35,    78,    77,    79,
      36,    -1,    59,    78,    -1,    -1,    83,    79,    -1,    -1,
      14,    -1,    15,    -1,    31,    -1,    20,    -1,    19,    -1,
      52,    -1,    49,    -1,    48,    -1,    51,    -1,    24,    -1,
       9,    -1,    25,    -1,    26,    -1,    83,    -1,    90,    -1,
      84,    -1,   103,    -1,   116,    -1,   124,    -1,   127,    -1,
      -1,    50,    85,    86,    -1,    87,    -1,    91,    -1,    -1,
      41,    89,    42,    88,    33,    -1,   135,    -1,    -1,    18,
     137,    33,    -1,    -1,    92,    93,    33,    -1,    94,    -1,
      97,    -1,    -1,    37,    95,    96,    -1,   123,    -1,   137,
      -1,    -1,    43,    98,   100,    -1,    -1,    44,    99,   101,
      -1,    43,    -1,    37,   102,    -1,    44,    -1,    37,   102,
      -1,    52,    -1,    48,    -1,    50,    -1,   104,    -1,   110,
      -1,    -1,    10,    41,   106,   105,    42,    35,    79,    36,
     107,    -1,   137,    -1,   129,    -1,    -1,    11,   108,   109,
      -1,    -1,   103,    -1,    35,    79,    36,    -1,    -1,    16,
      41,   152,    42,    35,   111,   112,    36,    -1,    -1,    -1,
      17,   171,   113,    37,    38,    35,    79,    36,   114,   115,
      -1,   112,    -1,    -1,    -1,    21,    41,   118,    42,   117,
      33,    -1,    -1,   120,   119,   121,    -1,    81,    -1,   152,
      -1,    -1,    47,   122,   118,    -1,    -1,    22,    41,    42,
      -1,    -1,    -1,    12,   125,    41,   137,    42,    35,   126,
      79,    36,    -1,   130,    41,   128,    42,    33,    -1,   135,
      -1,    -1,   130,    41,   128,    42,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,    80,
     132,    -1,    -1,    50,   133,   134,    -1,    32,   132,    -1,
     131,    -1,    -1,   152,   136,    -1,    32,   135,    -1,    -1,
      -1,   141,   138,   139,    -1,    -1,    28,   140,   137,    -1,
      -1,    -1,   145,   142,   143,    -1,    -1,    27,   144,   141,
      -1,    -1,    -1,   152,   146,   147,    -1,   148,   145,    -1,
      -1,    -1,    38,   149,   151,    -1,    -1,    39,   150,   151,
      -1,    40,    -1,    37,    37,    -1,    37,    -1,    -1,    -1,
     157,   153,   154,    -1,    -1,    43,   155,   152,    -1,    -1,
      44,   156,   152,    -1,    -1,    -1,   162,   158,   159,    -1,
      -1,    45,   160,   157,    -1,    -1,    46,   161,   157,    -1,
      -1,   163,    -1,   166,    -1,   168,    -1,    -1,   165,    41,
     164,   137,    42,    -1,    29,    -1,    -1,   167,    81,    -1,
      44,    -1,    29,    -1,    -1,    -1,    50,   169,   170,    -1,
      41,    89,    42,    -1,    -1,    50,    -1,    52,    -1,    51,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   786,   786,   786,   787,   788,   789,   790,   791,   793,
     794,   794,   795,   796,   796,   796,   796,   800,   801,   802,
     803,   804,   806,   806,   821,   822,   823,   824,   825,   825,
     826,   827,   828,   830,   830,   830,   831,   832,   833,   834,
     836,   837,   838,   839,   840,   842,   843,   844,   845,   846,
     847,   848,   849,   851,   852,   854,   855,   856,   857,   858,
     860,   860,   861,   862,   864,   864,   866,   867,   869,   871,
     871,   872,   873,   874,   874,   877,   878,   880,   880,   881,
     881,   882,   883,   884,   885,   887,   888,   889,   891,   892,
     893,   893,   915,   916,   917,   917,   929,   930,   931,   932,
     932,   951,   966,   951,   982,   983,   985,   985,   990,   990,
     995,   996,   997,   997,   998,  1000,  1002,  1003,  1002,  1024,
    1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1035,
    1036,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1044,  1044,
    1049,  1049,  1050,  1052,  1052,  1057,  1057,  1058,  1060,  1060,
    1065,  1066,  1067,  1067,  1068,  1068,  1069,  1070,  1071,  1075,
    1078,  1077,  1082,  1082,  1083,  1083,  1084,  1087,  1086,  1092,
    1092,  1093,  1093,  1094,  1096,  1097,  1098,  1099,  1099,  1109,
    1110,  1111,  1117,  1118,  1119,  1120,  1120,  1121,  1122,  1135,
    1136,  1137
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
  "var_initp", "funcion", "$@6", "funcionv", "tipof", "funcionp", "$@7",
  "funcionpp", "main", "$@8", "$@9", "mainv", "bloque", "tipo", "varcte",
  "estatutofuncion", "estatuto", "empieza_id", "$@10", "empieza_idp",
  "ejecuta_funcion", "$@11", "paramsf", "regresa", "asignacion", "$@12",
  "asignacionp", "asigp", "$@13", "lea", "ap", "$@14", "$@15", "maiap",
  "miap", "atipo", "condicion", "c", "$@16", "condicion_exp", "sip",
  "$@17", "sipp", "cp", "$@18", "cuandop", "$@19", "$@20", "cuandopp",
  "escritura", "$@21", "escriturap", "$@22", "escriturapp", "e", "$@23",
  "lectura", "ciclo", "$@24", "$@25", "accion", "accionp", "accionsi",
  "acciones", "params", "paramsp", "$@26", "paramspp", "params2",
  "params2p", "mmexp", "$@27", "mmexpp", "$@28", "mexp", "$@29", "mexpp",
  "$@30", "expresion", "$@31", "expresionp", "ep", "$@32", "$@33", "epp",
  "exp", "$@34", "expp", "$@35", "$@36", "termino", "$@37", "terminop",
  "$@38", "$@39", "factor", "factorp", "$@40", "nf", "factorpp", "f",
  "factorppp", "$@41", "fun_var", "varselecciona", 0
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
      67,    67,    69,    68,    70,    70,    71,    71,    73,    72,
      72,    74,    74,    76,    77,    75,    78,    78,    79,    79,
      80,    80,    80,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    83,    83,    83,    83,    83,
      85,    84,    86,    86,    88,    87,    89,    89,    90,    92,
      91,    93,    93,    95,    94,    96,    96,    98,    97,    99,
      97,   100,   100,   101,   101,   102,   102,   102,   103,   103,
     105,   104,   106,   106,   108,   107,   107,   109,   109,   111,
     110,   113,   114,   112,   115,   115,   117,   116,   119,   118,
     120,   120,   122,   121,   121,   123,   125,   126,   124,   127,
     128,   128,   129,   130,   130,   130,   130,   130,   130,   131,
     133,   132,   134,   134,   134,   135,   136,   136,   138,   137,
     140,   139,   139,   142,   141,   144,   143,   143,   146,   145,
     147,   147,   149,   148,   150,   148,   148,   148,   151,   151,
     153,   152,   155,   154,   156,   154,   154,   158,   157,   160,
     159,   161,   159,   159,   162,   162,   162,   164,   163,   165,
     165,   166,   167,   167,   167,   169,   168,   170,   170,   171,
     171,   171
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     2,     2,     0,     2,     0,     3,
       0,     3,     2,     0,     0,     0,     6,     0,     1,     1,
       2,     0,     0,    11,     2,     0,     1,     0,     0,     3,
       0,     1,     0,     0,     0,     7,     2,     0,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     1,     0,     5,     1,     0,     3,     0,
       3,     1,     1,     0,     3,     1,     1,     0,     3,     0,
       3,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       0,     9,     1,     1,     0,     3,     0,     1,     3,     0,
       8,     0,     0,    10,     1,     0,     0,     6,     0,     3,
       1,     1,     0,     3,     0,     3,     0,     0,     9,     5,
       1,     0,     4,     1,     1,     1,     1,     1,     1,     2,
       0,     3,     2,     1,     0,     2,     2,     0,     0,     3,
       0,     3,     0,     0,     3,     0,     3,     0,     0,     3,
       2,     0,     0,     3,     0,     3,     1,     2,     1,     0,
       0,     3,     0,     3,     0,     3,     0,     0,     3,     0,
       3,     0,     3,     0,     1,     1,     1,     0,     5,     1,
       0,     2,     1,     1,     0,     0,     3,     3,     0,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,    40,    41,    44,
      43,    42,     0,     8,     6,     0,    33,     3,    27,     4,
       8,     5,    10,     0,     0,     0,    26,     7,    13,     9,
      37,    22,     0,    11,     0,    37,    34,     0,    12,    14,
      36,    39,    32,   184,   123,   124,   125,   126,   127,   128,
       0,   116,     0,     0,    60,     0,    39,    55,    56,    88,
      89,    57,    58,    59,     0,     0,     0,    31,     0,   183,
     182,   185,    15,    18,    19,   138,   143,   148,   160,   167,
     174,     0,   175,     0,   176,   184,     0,   184,   180,    69,
      35,    38,   184,     0,   130,   129,     0,   188,    21,   142,
     147,   151,   166,   173,   177,    50,    49,    51,    52,    47,
      46,    48,    45,   181,    90,    93,     0,    92,   184,     0,
     110,     0,   108,   111,   184,    61,    62,    63,     0,     0,
     120,   137,    25,   134,   115,   184,   186,     0,    16,   140,
     139,   145,   144,     0,   152,   154,   156,   149,   184,   162,
     164,   161,   169,   171,   168,   184,     0,   184,     0,     0,
     106,   114,     0,    66,    73,    77,    79,     0,    71,    72,
       0,   184,   135,    25,    28,     0,   133,   131,     0,    20,
     184,   184,   157,   159,   159,   150,   184,   184,   184,   184,
       0,     0,     0,     0,    99,     0,   112,   109,    64,   184,
       0,     0,    70,   119,   136,    24,     0,     0,   132,   187,
     141,   146,   158,   153,   155,   163,   165,   170,   172,   178,
      39,   122,   117,     0,   107,   180,     0,    74,    75,    76,
       0,    81,    78,     0,    83,    80,    23,   184,    28,    53,
      54,     0,    39,     0,     0,   113,    65,    86,    87,    85,
      82,    84,     0,    29,    96,     0,   189,   191,   190,   101,
     100,    68,    94,    91,   118,     0,     0,     0,    39,    97,
      95,     0,     0,    39,    98,     0,   102,   105,   104,   103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    12,    13,    19,    14,    23,    28,    33,
      34,    43,    98,    72,   138,    20,    37,   174,    25,   206,
     207,    65,    17,    24,    41,    36,    55,    15,   120,   238,
      56,    57,    89,   125,   126,   226,   162,   240,   127,   128,
     167,   168,   199,   227,   169,   200,   201,   232,   235,   250,
      58,    59,   156,   114,   263,   266,   270,    60,   223,   244,
     265,   277,   279,    61,   195,   121,   161,   122,   197,   225,
      73,    62,    86,   242,    63,   129,   115,    64,    67,    95,
     133,   177,   130,   172,    74,    99,   140,   180,    75,   100,
     142,   181,    76,   101,   147,   148,   183,   184,   213,    77,
     102,   151,   186,   187,    78,   103,   154,   188,   189,    79,
      80,   155,    81,    82,    83,    84,    97,   136,   259
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -115
static const yytype_int16 yypact[] =
{
     -16,   -25,    29,  -115,  -115,     7,   135,  -115,  -115,  -115,
    -115,  -115,    28,    42,   135,     8,  -115,  -115,   135,  -115,
      42,  -115,  -115,    37,    53,    41,  -115,  -115,    44,  -115,
     135,  -115,     8,  -115,    64,   135,  -115,    62,  -115,  -115,
    -115,    32,   135,   -18,  -115,  -115,  -115,  -115,  -115,  -115,
      65,  -115,    75,    78,  -115,    84,    32,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,    90,    91,    85,  -115,    93,   100,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,   103,  -115,    74,  -115,    61,   110,    80,    88,   111,
    -115,  -115,    31,   121,  -115,  -115,   115,   117,   129,   134,
     136,   130,    36,    39,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,   124,  -115,    80,   131,
    -115,   132,  -115,  -115,    45,  -115,  -115,  -115,     6,   133,
    -115,   139,   135,   128,  -115,    45,  -115,     8,  -115,  -115,
    -115,  -115,  -115,   140,  -115,  -115,  -115,  -115,    80,  -115,
    -115,  -115,  -115,  -115,  -115,    80,   137,    31,   138,   141,
    -115,   125,   142,  -115,  -115,  -115,  -115,   145,  -115,  -115,
     148,    80,  -115,   135,   146,    85,  -115,  -115,   143,  -115,
      80,    80,  -115,   150,   150,  -115,    80,    80,    80,    80,
     147,   153,   149,   155,  -115,   159,  -115,  -115,  -115,   -18,
       9,    10,  -115,  -115,  -115,  -115,   157,    12,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
      32,  -115,  -115,   166,  -115,    88,   161,  -115,  -115,  -115,
      11,  -115,  -115,    11,  -115,  -115,  -115,    80,   146,  -115,
    -115,   160,    32,    77,   162,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,   164,  -115,   184,   163,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,   165,    -4,   167,    32,  -115,
    -115,   168,   170,    32,  -115,   171,  -115,   166,  -115,  -115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,  -115,  -115,   186,   181,   -28,   -27,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,    35,  -115,   -34,
    -115,  -115,  -115,  -115,  -115,   174,   -56,   -15,   127,  -115,
       4,  -115,  -115,  -115,  -115,  -115,    79,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   -20,
     -51,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   -61,
    -115,  -115,  -115,  -115,  -115,    -7,  -115,  -115,  -115,  -115,
      20,  -115,  -115,  -115,  -115,    63,  -115,   144,    89,    46,
    -115,  -115,  -114,  -115,   -84,  -115,  -115,  -115,    43,  -115,
    -115,  -115,    82,  -115,  -115,  -115,  -115,  -115,    47,   -79,
    -115,  -115,  -115,  -115,   -95,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -181
static const yytype_int16 yytable[] =
{
      91,   117,    35,    26,    68,    38,    50,    35,   119,   123,
     163,    69,    52,   131,     1,    44,    45,    46,    47,    48,
      49,   163,    50,  -180,    51,     3,    70,    66,    52,     4,
     237,   268,    71,    53,   158,    44,    45,    46,    47,    48,
      49,     6,    50,   164,    51,   131,   230,   233,    52,   165,
     166,    16,   231,    53,   234,    18,   131,   204,    22,   247,
      69,   248,    54,   249,    44,    45,    46,    47,    48,    49,
      29,   190,  -180,  -121,    69,    70,    32,   -17,   131,   149,
     150,    71,    54,   105,   152,   153,  -180,   -67,    30,    70,
      69,    31,   131,   217,   218,    71,   210,   105,   106,   107,
     108,    39,  -180,    42,   173,    70,    85,   215,   216,    69,
     179,    71,   106,   107,   108,   229,    87,    69,    66,    88,
      90,  -180,   109,   110,    70,   111,   112,   256,   257,   258,
      71,    92,    70,    93,    96,    94,   109,   110,    71,   111,
     112,  -179,     7,     8,   104,   173,   123,     9,    10,     7,
       8,   118,   124,   252,     9,    10,   132,   134,   135,    11,
     175,   137,   139,   141,   241,   157,    11,   143,   144,   145,
     146,   171,   196,   159,   160,   170,   194,   182,   202,   191,
     193,   203,   -30,   243,   198,   209,   255,   212,   220,   219,
     222,   221,   224,   236,   246,   262,   254,   261,   260,   264,
      21,    27,   267,   273,   253,   271,   274,   276,   205,    40,
     113,   239,   272,   251,   178,   269,   278,   275,   245,   228,
     192,   208,   176,     0,   211,     0,     0,     0,     0,   116,
     185,   214
};

static const yytype_int16 yycheck[] =
{
      56,    85,    30,    18,    22,    32,    10,    35,    87,    88,
     124,    29,    16,    92,    30,     3,     4,     5,     6,     7,
       8,   135,    10,    41,    12,    50,    44,    42,    16,     0,
      18,    35,    50,    21,   118,     3,     4,     5,     6,     7,
       8,    34,    10,    37,    12,   124,    37,    37,    16,    43,
      44,    23,    43,    21,    44,    13,   135,   171,    50,    48,
      29,    50,    50,    52,     3,     4,     5,     6,     7,     8,
      33,   155,    41,    42,    29,    44,    32,    33,   157,    43,
      44,    50,    50,     9,    45,    46,    41,    42,    35,    44,
      29,    50,   171,   188,   189,    50,   180,     9,    24,    25,
      26,    37,    41,    41,   132,    44,    41,   186,   187,    29,
     137,    50,    24,    25,    26,   199,    41,    29,   133,    41,
      36,    41,    48,    49,    44,    51,    52,    50,    51,    52,
      50,    41,    44,    42,    41,    50,    48,    49,    50,    51,
      52,    41,    14,    15,    41,   173,   225,    19,    20,    14,
      15,    41,    41,   237,    19,    20,    35,    42,    41,    31,
      32,    32,    28,    27,   220,    41,    31,    37,    38,    39,
      40,    32,    47,    42,    42,    42,    35,    37,    33,    42,
      42,    33,    36,    17,    42,    42,   242,    37,    35,    42,
      35,    42,    33,    36,    33,    11,    36,    33,    36,    36,
      14,    20,    37,    35,   238,    38,    36,    36,   173,    35,
      83,   207,   268,   233,   135,   266,   277,   273,   225,   199,
     157,   175,   133,    -1,   181,    -1,    -1,    -1,    -1,    85,
     148,   184
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    54,    50,     0,    55,    34,    14,    15,    19,
      20,    31,    56,    57,    59,    80,    23,    75,    13,    58,
      68,    57,    50,    60,    76,    71,    80,    58,    61,    33,
      35,    50,    32,    62,    63,    59,    78,    69,    60,    37,
      78,    77,    41,    64,     3,     4,     5,     6,     7,     8,
      10,    12,    16,    21,    50,    79,    83,    84,   103,   104,
     110,   116,   124,   127,   130,    74,    80,   131,    22,    29,
      44,    50,    66,   123,   137,   141,   145,   152,   157,   162,
     163,   165,   166,   167,   168,    41,   125,    41,    41,    85,
      36,    79,    41,    42,    50,   132,    41,   169,    65,   138,
     142,   146,   153,   158,    41,     9,    24,    25,    26,    48,
      49,    51,    52,    81,   106,   129,   130,   137,    41,   152,
      81,   118,   120,   152,    41,    86,    87,    91,    92,   128,
     135,   152,    35,   133,    42,    41,   170,    32,    67,    28,
     139,    27,   143,    37,    38,    39,    40,   147,   148,    43,
      44,   154,    45,    46,   159,   164,   105,    41,   137,    42,
      42,   119,    89,   135,    37,    43,    44,    93,    94,    97,
      42,    32,   136,    59,    70,    32,   131,   134,    89,    60,
     140,   144,    37,   149,   150,   145,   155,   156,   160,   161,
     137,    42,   128,    42,    35,   117,    47,   121,    42,    95,
      98,    99,    33,    33,   135,    70,    72,    73,   132,    42,
     137,   141,    37,   151,   151,   152,   152,   157,   157,    42,
      35,    42,    35,   111,    33,   122,    88,    96,   123,   137,
      37,    43,   100,    37,    44,   101,    36,    18,    82,    83,
      90,    79,   126,    17,   112,   118,    33,    48,    50,    52,
     102,   102,   137,    72,    36,    79,    50,    51,    52,   171,
      36,    33,    11,   107,    36,   113,   108,    37,    35,   103,
     109,    38,    79,    35,    36,    79,    36,   114,   112,   115
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
#line 786 "parser.y"
    {tipo_actual = 'V'; insert_proc_to_table("programa");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 794 "parser.y"
    {id_a_verificar = yylval.str; insert_var_to_table(yylval.str);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 806 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 806 "parser.y"
    {
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
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 824 "parser.y"
    {tipo_actual= 'V';;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 825 "parser.y"
    {insert_dir_inicial();;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 830 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 830 "parser.y"
    {insert_dir_inicial();;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 836 "parser.y"
    {tipo_actual= 'I';;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 837 "parser.y"
    {tipo_actual= 'F';;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 838 "parser.y"
    {tipo_actual= 'C';;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 839 "parser.y"
    {tipo_actual= 'S';;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 840 "parser.y"
    {tipo_actual= 'L';;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 842 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 843 "parser.y"
    {insert_constante_to_table(yylval.str,3);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 844 "parser.y"
    {insert_constante_to_table(yylval.str,2);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 845 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 848 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 849 "parser.y"
    {insert_constante_to_table(yylval.str,5);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 860 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 864 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 871 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 874 "parser.y"
    {g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 874 "parser.y"
    {
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 880 "parser.y"
    {g_queue_push_head(POperadores,1);/*operador +*/;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 881 "parser.y"
    {g_queue_push_head(POperadores,4);/*operador -*/;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 882 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 883 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 884 "parser.y"
    { generar_cuadruplo_expresion_unaria();;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 885 "parser.y"
    {generar_cuadruplo_expresion();;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 887 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 888 "parser.y"
    {insert_constante_to_table(yylval.integer,2);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 889 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 893 "parser.y"
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

  case 91:

/* Line 1455 of yacc.c  */
#line 906 "parser.y"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 917 "parser.y"
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

  case 99:

/* Line 1455 of yacc.c  */
#line 932 "parser.y"
    {
		g_queue_push_head(PSwitch,0);		
		;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 934 "parser.y"
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

  case 101:

/* Line 1455 of yacc.c  */
#line 951 "parser.y"
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

  case 102:

/* Line 1455 of yacc.c  */
#line 966 "parser.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 985 "parser.y"
    {
		int operando1 = (int)g_queue_pop_head(POperandos);	
		int tipo1 = g_queue_pop_head(PTipos);
		generar_cuadruplo(25,operando1,-1,-1);
		;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 990 "parser.y"
    { if(g_queue_peek_head(POperadores) == 9){
		printf("Genera cuadruplo .\n");
		generar_cuadruplo_expresion();		
		};}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 997 "parser.y"
    {g_queue_push_head(POperadores,9);/*operador concatenacion(.)*/;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1000 "parser.y"
    {insert_constante_to_table("Lectura de pantalla",3);;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1002 "parser.y"
    {g_queue_push_head(PSaltos,contador_cuadruplos); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1003 "parser.y"
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

  case 118:

/* Line 1455 of yacc.c  */
#line 1013 "parser.y"
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

  case 130:

/* Line 1455 of yacc.c  */
#line 1036 "parser.y"
    {insert_param_tipo();insert_var_to_table(yylval.str);/*Regla 103*/;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1044 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 17){
  			printf("Genera cuadruplo or \n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1049 "parser.y"
    {g_queue_push_head(POperadores,17);/*operador or*/;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1052 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 16){
  			printf("Genera cuadruplo and /\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1057 "parser.y"
    {g_queue_push_head(POperadores,16);/*operador and*/;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1060 "parser.y"
    {
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
  			printf("Genera cuadruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1067 "parser.y"
    {g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1068 "parser.y"
    {g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1069 "parser.y"
    {g_queue_push_head(POperadores,11);/*operador diferente*/;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1070 "parser.y"
    {g_queue_push_head(POperadores,15);/*operador igual igual*/;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1071 "parser.y"
    {int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1078 "parser.y"
    {if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1082 "parser.y"
    {g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1083 "parser.y"
    {g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1087 "parser.y"
    {if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1092 "parser.y"
    {g_queue_push_head(POperadores,7);/*operador multiplica*/;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1093 "parser.y"
    {g_queue_push_head(POperadores,8);/*operador division*/;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1099 "parser.y"
    {g_queue_push_head(POperadores,'(');;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1099 "parser.y"
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

  case 179:

/* Line 1455 of yacc.c  */
#line 1109 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1111 "parser.y"
    {
  if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		printf("Genera cuadruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1117 "parser.y"
    {g_queue_push_head(POperadores,20);/*operador multiplica*/;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1118 "parser.y"
    {g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1120 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1121 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1122 "parser.y"
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

  case 189:

/* Line 1455 of yacc.c  */
#line 1135 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1136 "parser.y"
    {insert_constante_to_table(yylval.integer,1);;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1137 "parser.y"
    {insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 3153 "parser.tab.c"
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
#line 1140 "parser.y"
 
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
while(a = g_queue_pop_head(cuadruplos)){
	fprintf(objeto,"%d,%d,%d,%d\n",a->operador,a->operando1,a->operando2,a->destino);
}

fclose(objeto);
free(dir_procs);
}

yyerror(char *s){
       printf("Error de sintaxis en la línea %d\n", yylineno);
}


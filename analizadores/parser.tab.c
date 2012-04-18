
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
				  g_queue_pop_head(POperadores);
					generar_cuadruplo(operador,operando1,operando2,operando1);
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
				generar_cuadruplo(operador,operando1,-1,operando1);
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
#line 896 "parser.tab.c"

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
#line 822 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 992 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1004 "parser.tab.c"

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
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  128
/* YYNRULES -- Number of rules.  */
#define YYNRULES  197
/* YYNRULES -- Number of states.  */
#define YYNSTATES  285

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
      49,    51,    54,    55,    56,    57,    70,    73,    74,    76,
      77,    80,    81,    83,    84,    85,    86,    87,    96,    99,
     100,   103,   104,   106,   108,   110,   112,   114,   116,   118,
     120,   122,   124,   126,   128,   130,   132,   134,   136,   138,
     140,   142,   144,   145,   149,   151,   153,   154,   155,   162,
     164,   165,   166,   167,   173,   174,   178,   180,   182,   183,
     187,   189,   191,   192,   196,   197,   201,   203,   204,   208,
     210,   211,   215,   217,   219,   221,   223,   225,   226,   236,
     238,   240,   241,   245,   246,   248,   252,   253,   262,   263,
     264,   275,   277,   278,   279,   286,   287,   291,   292,   296,
     297,   301,   302,   303,   313,   314,   320,   321,   326,   328,
     330,   332,   334,   336,   338,   341,   342,   346,   349,   350,
     351,   355,   358,   359,   360,   364,   365,   369,   370,   371,
     375,   376,   380,   381,   382,   386,   389,   390,   391,   395,
     396,   400,   402,   405,   407,   408,   409,   413,   414,   418,
     419,   423,   424,   425,   429,   430,   434,   435,   439,   440,
     442,   444,   446,   447,   453,   455,   456,   459,   461,   463,
     464,   465,   469,   470,   475,   476,   478,   480
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      54,     0,    -1,    -1,    -1,    55,    30,    50,    56,    34,
      57,    76,    -1,    58,    59,    -1,    60,    58,    -1,    -1,
      69,    59,    -1,    -1,    82,    61,    33,    -1,    -1,    50,
      62,    63,    -1,    32,    61,    -1,    -1,    -1,    -1,    64,
      37,    65,    67,    66,    68,    -1,    -1,   129,    -1,   145,
      -1,    32,    61,    -1,    -1,    -1,    -1,    13,    73,    50,
      70,    41,    75,    42,    35,    71,    72,    74,    36,    -1,
      60,    72,    -1,    -1,    82,    -1,    -1,    84,    74,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    23,    77,    35,
      78,    80,    79,    81,    36,    -1,    60,    80,    -1,    -1,
      85,    81,    -1,    -1,    14,    -1,    15,    -1,    31,    -1,
      20,    -1,    19,    -1,    52,    -1,    49,    -1,    48,    -1,
      51,    -1,    24,    -1,     9,    -1,    25,    -1,    26,    -1,
      85,    -1,    93,    -1,    86,    -1,   110,    -1,   123,    -1,
     130,    -1,   133,    -1,    -1,    50,    87,    88,    -1,    89,
      -1,    96,    -1,    -1,    -1,    41,    90,    92,    42,    91,
      33,    -1,   142,    -1,    -1,    -1,    -1,    18,    94,   145,
      95,    33,    -1,    -1,    97,    98,    33,    -1,    99,    -1,
     102,    -1,    -1,    37,   100,   101,    -1,   129,    -1,   145,
      -1,    -1,    43,   103,   105,    -1,    -1,    44,   104,   107,
      -1,    43,    -1,    -1,    37,   106,   109,    -1,    44,    -1,
      -1,    37,   108,   109,    -1,    52,    -1,    48,    -1,    50,
      -1,   111,    -1,   117,    -1,    -1,    10,    41,   113,   112,
      42,    35,    81,    36,   114,    -1,   145,    -1,   135,    -1,
      -1,    11,   115,   116,    -1,    -1,   110,    -1,    35,    81,
      36,    -1,    -1,    16,    41,   160,    42,    35,   118,   119,
      36,    -1,    -1,    -1,    17,   180,   120,    37,    38,    35,
      81,    36,   121,   122,    -1,   119,    -1,    -1,    -1,    21,
      41,   125,    42,   124,    33,    -1,    -1,   160,   126,   127,
      -1,    -1,    47,   128,   125,    -1,    -1,    22,    41,    42,
      -1,    -1,    -1,    12,   131,    41,   145,    42,    35,   132,
      81,    36,    -1,    -1,   137,   134,    41,    42,    33,    -1,
      -1,   137,   136,    41,    42,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,     8,    -1,    82,   139,
      -1,    -1,    50,   140,   141,    -1,    32,   138,    -1,    -1,
      -1,   160,   143,   144,    -1,    32,   142,    -1,    -1,    -1,
     149,   146,   147,    -1,    -1,    28,   148,   145,    -1,    -1,
      -1,   153,   150,   151,    -1,    -1,    27,   152,   149,    -1,
      -1,    -1,   160,   154,   155,    -1,   156,   153,    -1,    -1,
      -1,    38,   157,   159,    -1,    -1,    39,   158,   159,    -1,
      40,    -1,    37,    37,    -1,    37,    -1,    -1,    -1,   165,
     161,   162,    -1,    -1,    43,   163,   160,    -1,    -1,    44,
     164,   160,    -1,    -1,    -1,   170,   166,   167,    -1,    -1,
      45,   168,   165,    -1,    -1,    46,   169,   165,    -1,    -1,
     171,    -1,   174,    -1,   176,    -1,    -1,   173,    41,   172,
     145,    42,    -1,    29,    -1,    -1,   175,    83,    -1,    44,
      -1,    29,    -1,    -1,    -1,    50,   177,   178,    -1,    -1,
      41,   179,    92,    42,    -1,    -1,    50,    -1,    52,    -1,
      51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   842,   842,   842,   842,   843,   844,   845,   846,   847,
     849,   850,   850,   851,   852,   852,   852,   852,   857,   858,
     859,   860,   861,   863,   872,   863,   904,   905,   906,   909,
     911,   912,   913,   914,   916,   916,   922,   916,   926,   927,
     928,   929,   931,   932,   933,   934,   935,   937,   938,   939,
     940,   941,   942,   943,   944,   946,   947,   949,   950,   951,
     952,   953,   955,   955,   956,   957,   959,   969,   959,   985,
     986,   988,   988,   988,  1033,  1033,  1034,  1035,  1036,  1036,
    1040,  1041,  1043,  1043,  1044,  1044,  1045,  1046,  1046,  1047,
    1048,  1048,  1050,  1051,  1052,  1054,  1055,  1056,  1056,  1079,
    1080,  1081,  1081,  1094,  1095,  1096,  1097,  1097,  1117,  1132,
    1117,  1148,  1149,  1151,  1151,  1158,  1158,  1165,  1165,  1166,
    1168,  1170,  1171,  1170,  1194,  1194,  1200,  1200,  1205,  1206,
    1207,  1208,  1209,  1210,  1212,  1213,  1213,  1214,  1215,  1216,
    1216,  1247,  1248,  1250,  1250,  1256,  1256,  1257,  1259,  1259,
    1265,  1265,  1266,  1268,  1268,  1274,  1275,  1276,  1276,  1277,
    1277,  1278,  1279,  1280,  1286,  1289,  1288,  1294,  1294,  1295,
    1295,  1296,  1299,  1298,  1305,  1305,  1306,  1306,  1307,  1309,
    1310,  1311,  1312,  1312,  1326,  1327,  1328,  1335,  1336,  1337,
    1338,  1338,  1339,  1339,  1368,  1373,  1374,  1375
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
  "var_init", "var_initp", "funcion", "$@7", "$@8", "funcionv", "tipof",
  "funcionp", "funcionpp", "main", "$@9", "$@10", "$@11", "mainv",
  "bloque", "tipo", "varcte", "estatutofuncion", "estatuto", "empieza_id",
  "$@12", "empieza_idp", "ejecuta_funcion", "$@13", "$@14", "paramsf",
  "regresa", "$@15", "$@16", "asignacion", "$@17", "asignacionp", "asigp",
  "$@18", "lea", "ap", "$@19", "$@20", "maiap", "$@21", "miap", "$@22",
  "atipo", "condicion", "c", "$@23", "condicion_exp", "sip", "$@24",
  "sipp", "cp", "$@25", "cuandop", "$@26", "$@27", "cuandopp", "escritura",
  "$@28", "escriturap", "$@29", "e", "$@30", "lectura", "ciclo", "$@31",
  "$@32", "accion", "$@33", "accionsi", "$@34", "acciones", "params",
  "paramsp", "$@35", "paramspp", "params2", "$@36", "params2p", "mmexp",
  "$@37", "mmexpp", "$@38", "mexp", "$@39", "mexpp", "$@40", "expresion",
  "$@41", "expresionp", "ep", "$@42", "$@43", "epp", "exp", "$@44", "expp",
  "$@45", "$@46", "termino", "$@47", "terminop", "$@48", "$@49", "factor",
  "factorp", "$@50", "nf", "factorpp", "f", "factorppp", "$@51", "fun_var",
  "$@52", "varselecciona", 0
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
      67,    68,    68,    70,    71,    69,    72,    72,    73,    73,
      74,    74,    75,    75,    77,    78,    79,    76,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    84,    85,    85,    85,
      85,    85,    87,    86,    88,    88,    90,    91,    89,    92,
      92,    94,    95,    93,    97,    96,    98,    98,   100,    99,
     101,   101,   103,   102,   104,   102,   105,   106,   105,   107,
     108,   107,   109,   109,   109,   110,   110,   112,   111,   113,
     113,   115,   114,   114,   116,   116,   118,   117,   120,   121,
     119,   122,   122,   124,   123,   126,   125,   128,   127,   127,
     129,   131,   132,   130,   134,   133,   136,   135,   137,   137,
     137,   137,   137,   137,   138,   140,   139,   141,   141,   143,
     142,   144,   144,   146,   145,   148,   147,   147,   150,   149,
     152,   151,   151,   154,   153,   155,   155,   157,   156,   158,
     156,   156,   156,   159,   159,   161,   160,   163,   162,   164,
     162,   162,   166,   165,   168,   167,   169,   167,   167,   170,
     170,   170,   172,   171,   173,   173,   174,   175,   175,   175,
     177,   176,   179,   178,   178,   180,   180,   180
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     7,     2,     2,     0,     2,     0,
       3,     0,     3,     2,     0,     0,     0,     6,     0,     1,
       1,     2,     0,     0,     0,    12,     2,     0,     1,     0,
       2,     0,     1,     0,     0,     0,     0,     8,     2,     0,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     3,     1,     1,     0,     0,     6,     1,
       0,     0,     0,     5,     0,     3,     1,     1,     0,     3,
       1,     1,     0,     3,     0,     3,     1,     0,     3,     1,
       0,     3,     1,     1,     1,     1,     1,     0,     9,     1,
       1,     0,     3,     0,     1,     3,     0,     8,     0,     0,
      10,     1,     0,     0,     6,     0,     3,     0,     3,     0,
       3,     0,     0,     9,     0,     5,     0,     4,     1,     1,
       1,     1,     1,     1,     2,     0,     3,     2,     0,     0,
       3,     2,     0,     0,     3,     0,     3,     0,     0,     3,
       0,     3,     0,     0,     3,     2,     0,     0,     3,     0,
       3,     1,     2,     1,     0,     0,     3,     0,     3,     0,
       3,     0,     0,     3,     0,     3,     0,     3,     0,     1,
       1,     1,     0,     5,     1,     0,     2,     1,     1,     0,
       0,     3,     0,     4,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     7,    42,    43,
      46,    45,    44,     0,     9,     7,     0,    34,     4,    29,
       5,     9,     6,    11,     0,     0,     0,    28,     8,    14,
      10,    35,    23,     0,    12,     0,    39,     0,    13,    15,
      39,    36,    33,   189,    38,    41,     0,     0,    32,     0,
     188,   187,   190,    16,    19,    20,   143,   148,   153,   165,
     172,   179,     0,   180,     0,   181,   128,   129,   130,   131,
     132,   133,     0,   121,     0,     0,    62,     0,    41,    57,
      58,    95,    96,    59,    60,    61,   124,     0,   135,   134,
       0,   194,    22,   147,   152,   156,   171,   178,   182,    52,
      51,    53,    54,    49,    48,    50,    47,   186,   189,     0,
     189,   189,    74,    37,    40,     0,    24,   138,   120,   192,
     191,     0,    17,   145,   144,   150,   149,     0,   157,   159,
     161,   154,   189,   167,   169,   166,   174,   176,   173,   189,
      97,   100,   126,    99,   189,     0,     0,   115,    66,    63,
      64,    65,     0,     0,    27,     0,   136,   189,    21,   189,
     189,   162,   164,   164,   155,   189,   189,   189,   189,     0,
       0,     0,     0,     0,   113,   119,   189,    78,    82,    84,
       0,    76,    77,     0,    27,    31,   137,     0,    69,   139,
     146,   151,   163,   158,   160,   168,   170,   175,   177,   183,
       0,     0,     0,   106,     0,   117,   116,     0,   189,     0,
       0,    75,   125,    26,    71,     0,    31,    55,    56,   193,
     142,    41,   127,   122,     0,   114,   189,    67,    79,    80,
      81,    87,    86,    83,    90,    89,    85,   189,    25,    30,
     189,   140,     0,    41,     0,     0,   118,     0,     0,     0,
      72,   141,   103,     0,   195,   197,   196,   108,   107,    68,
      93,    94,    92,    88,    91,     0,   101,    98,   123,     0,
      73,     0,     0,    41,   104,   102,     0,     0,    41,   105,
       0,   109,   112,   111,   110
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    13,    14,    20,    15,    24,    29,
      34,    35,    43,    92,    53,   122,    21,    37,   154,   185,
      26,   215,    46,    18,    25,    36,    45,    41,    77,    16,
     107,   216,    78,    79,   112,   149,   150,   176,   247,   187,
     218,   237,   265,   151,   152,   180,   181,   208,   228,   182,
     209,   210,   233,   248,   236,   249,   263,    80,    81,   170,
     140,   267,   271,   275,    82,   224,   245,   269,   282,   284,
      83,   204,   146,   175,   206,   226,    54,    84,   109,   243,
      85,   115,   141,   171,    86,    48,    89,   117,   156,   188,
     220,   241,    55,    93,   124,   159,    56,    94,   126,   160,
      57,    95,   131,   132,   162,   163,   193,    58,    96,   135,
     165,   166,    59,    97,   138,   167,   168,    60,    61,   139,
      62,    63,    64,    65,    91,   120,   157,   257
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -172
static const yytype_int16 yypact[] =
{
    -172,    24,    26,  -172,    29,  -172,    34,    82,  -172,  -172,
    -172,  -172,  -172,    51,    68,    82,    37,  -172,  -172,    82,
    -172,    68,  -172,  -172,    43,    70,    39,  -172,  -172,    83,
    -172,  -172,  -172,    37,  -172,    75,    82,    73,  -172,  -172,
      82,  -172,    82,    36,  -172,    25,    42,    74,  -172,    84,
      85,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,    86,  -172,    18,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,    87,  -172,    88,    89,  -172,    95,    25,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,    98,  -172,  -172,
      81,    93,   103,   109,   112,    71,    16,    72,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    44,    99,
      54,    54,   100,  -172,  -172,   101,  -172,   113,  -172,  -172,
    -172,    37,  -172,  -172,  -172,  -172,  -172,   107,  -172,  -172,
    -172,  -172,    54,  -172,  -172,  -172,  -172,  -172,  -172,    54,
    -172,  -172,  -172,  -172,    54,   104,   105,  -172,  -172,  -172,
    -172,  -172,    63,   106,    82,    82,  -172,    49,  -172,    54,
      54,  -172,   114,   114,  -172,    54,    54,    54,    54,   108,
     110,   115,   111,   119,  -172,   116,    49,  -172,  -172,  -172,
     122,  -172,  -172,   124,    82,     5,  -172,   117,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
     123,   118,   126,  -172,   129,  -172,  -172,   125,    36,   -21,
      27,  -172,  -172,  -172,  -172,   128,     5,  -172,  -172,  -172,
     134,    25,  -172,  -172,   151,  -172,    54,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,    54,  -172,  -172,
      54,  -172,   133,    25,   -32,   135,  -172,   137,   -12,   -12,
    -172,  -172,   161,   138,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,   140,  -172,  -172,  -172,   139,
    -172,    47,   141,    25,  -172,  -172,   142,   144,    25,  -172,
     145,  -172,   151,  -172,  -172
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,  -172,  -172,  -172,   160,   157,   -35,   -29,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    -2,
    -172,   -33,  -172,  -172,  -172,  -172,  -172,   146,   -78,   -17,
    -172,  -172,  -171,  -172,  -172,  -172,  -172,  -172,  -172,     8,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,   -64,   -84,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,   -94,  -172,  -172,  -172,
    -172,  -172,   -37,  -172,  -172,  -172,   -18,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,    90,    38,  -172,  -172,  -172,   -49,
    -172,  -172,  -105,  -172,  -172,  -172,    32,  -172,  -172,  -172,
      62,  -172,  -172,  -172,  -172,  -172,    33,  -104,  -172,  -172,
    -172,  -172,   -47,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -186
static const yytype_int16 yytable[] =
{
     114,    40,    27,   143,    38,    40,   145,   147,    66,    67,
      68,    69,    70,    71,   217,    72,   231,    73,   254,   255,
     256,    74,   232,   214,     3,    47,    75,    99,    66,    67,
      68,    69,    70,    71,   169,    72,   260,    73,   261,   172,
     262,    74,   100,   101,   102,   217,    75,    66,    67,    68,
      69,    70,    71,   189,   190,    76,     4,    72,    49,   133,
     134,   195,   196,    74,   234,    50,   103,   104,     7,   105,
     106,   235,   189,    50,    17,    76,    30,  -185,    50,     5,
      51,    19,   273,    50,    87,  -185,    52,    23,    51,    32,
    -185,   -70,   158,    51,    52,  -185,     8,     9,    51,    52,
     177,    10,    11,   230,    52,    31,   178,   179,   127,   128,
     129,   130,    39,    12,    42,    33,   -18,   136,   137,   184,
     197,   198,   147,   118,    88,    90,  -184,    98,   108,   110,
     111,   113,   250,   116,   119,   121,   189,   123,    47,   125,
     144,   148,   153,   242,   161,   155,   173,   174,   183,   184,
     199,   192,   200,   202,   203,   211,   201,   212,   221,   219,
     222,   223,   225,   205,   238,   253,   240,   227,   244,   252,
     259,   258,   266,   270,   268,    22,   272,   278,    28,   276,
     279,   281,   213,   239,   207,   264,    44,   274,   283,   246,
     229,   251,   191,   186,   164,   277,   194,     0,   142,     0,
     280
};

static const yytype_int16 yycheck[] =
{
      78,    36,    19,   108,    33,    40,   110,   111,     3,     4,
       5,     6,     7,     8,   185,    10,    37,    12,    50,    51,
      52,    16,    43,    18,     0,    42,    21,     9,     3,     4,
       5,     6,     7,     8,   139,    10,    48,    12,    50,   144,
      52,    16,    24,    25,    26,   216,    21,     3,     4,     5,
       6,     7,     8,   157,   159,    50,    30,    10,    22,    43,
      44,   165,   166,    16,    37,    29,    48,    49,    34,    51,
      52,    44,   176,    29,    23,    50,    33,    41,    29,    50,
      44,    13,    35,    29,    42,    41,    50,    50,    44,    50,
      41,    42,   121,    44,    50,    41,    14,    15,    44,    50,
      37,    19,    20,   208,    50,    35,    43,    44,    37,    38,
      39,    40,    37,    31,    41,    32,    33,    45,    46,   154,
     167,   168,   226,    42,    50,    41,    41,    41,    41,    41,
      41,    36,   237,    35,    41,    32,   240,    28,   155,    27,
      41,    41,    41,   221,    37,    32,    42,    42,    42,   184,
      42,    37,    42,    42,    35,    33,    41,    33,    35,    42,
      42,    35,    33,    47,    36,   243,    32,    42,    17,    36,
      33,    36,    11,    33,    36,    15,    37,    35,    21,    38,
      36,    36,   184,   216,   176,   249,    40,   271,   282,   226,
     208,   240,   160,   155,   132,   273,   163,    -1,   108,    -1,
     278
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,    55,     0,    30,    50,    56,    34,    14,    15,
      19,    20,    31,    57,    58,    60,    82,    23,    76,    13,
      59,    69,    58,    50,    61,    77,    73,    82,    59,    62,
      33,    35,    50,    32,    63,    64,    78,    70,    61,    37,
      60,    80,    41,    65,    80,    79,    75,    82,   138,    22,
      29,    44,    50,    67,   129,   145,   149,   153,   160,   165,
     170,   171,   173,   174,   175,   176,     3,     4,     5,     6,
       7,     8,    10,    12,    16,    21,    50,    81,    85,    86,
     110,   111,   117,   123,   130,   133,   137,    42,    50,   139,
      41,   177,    66,   146,   150,   154,   161,   166,    41,     9,
      24,    25,    26,    48,    49,    51,    52,    83,    41,   131,
      41,    41,    87,    36,    81,   134,    35,   140,    42,    41,
     178,    32,    68,    28,   147,    27,   151,    37,    38,    39,
      40,   155,   156,    43,    44,   162,    45,    46,   167,   172,
     113,   135,   137,   145,    41,   160,   125,   160,    41,    88,
      89,    96,    97,    41,    71,    32,   141,   179,    61,   148,
     152,    37,   157,   158,   153,   163,   164,   168,   169,   145,
     112,   136,   145,    42,    42,   126,    90,    37,    43,    44,
      98,    99,   102,    42,    60,    72,   138,    92,   142,   160,
     145,   149,    37,   159,   159,   160,   160,   165,   165,    42,
      42,    41,    42,    35,   124,    47,   127,    92,   100,   103,
     104,    33,    33,    72,    18,    74,    84,    85,    93,    42,
     143,    35,    42,    35,   118,    33,   128,    42,   101,   129,
     145,    37,    43,   105,    37,    44,   107,    94,    36,    74,
      32,   144,    81,   132,    17,   119,   125,    91,   106,   108,
     145,   142,    36,    81,    50,    51,    52,   180,    36,    33,
      48,    50,    52,   109,   109,    95,    11,   114,    36,   120,
      33,   115,    37,    35,   110,   116,    38,    81,    35,    36,
      81,    36,   121,   119,   122
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
#line 842 "parser.y"
    {/*Regla 43*/generar_cuadruplo(21,-1,-1,-1);/*goto del main*/ ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 842 "parser.y"
    {/* Regla 48*/tipo_actual = 'V'; /*Regla 101*/insert_proc_to_table("programa");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 850 "parser.y"
    {/*Regla 103 y 32*/id_a_verificar = yylval.str; insert_var_to_table(yylval.str,proc_actual);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 852 "parser.y"
    {/*Regla 1*/verifica_existe_var(id_a_verificar);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 852 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 852 "parser.y"
    {
		//regla 3
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 863 "parser.y"
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
#line 872 "parser.y"
    {/*Regla 33*/insert_dir_inicial();;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 872 "parser.y"
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

  case 28:

/* Line 1455 of yacc.c  */
#line 906 "parser.y"
    {//Regla 49
		tipo_funcion_actual = tipo_actual;
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 909 "parser.y"
    { 	//Regla 48
		tipo_funcion_actual= 'V';;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
    {/*Regla 101*/insert_proc_to_table(yylval.str);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
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
#line 922 "parser.y"
    {
		//Regla 33
		insert_dir_inicial();
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 931 "parser.y"
    {/*Regla 102*/tipo_actual= 'I';;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 932 "parser.y"
    {/*Regla 102*/tipo_actual= 'F';;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 933 "parser.y"
    {/*Regla 102*/tipo_actual= 'C';;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 934 "parser.y"
    {/*Regla 102*/tipo_actual= 'S';;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 935 "parser.y"
    {/*Regla 102*/tipo_actual= 'L';;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 937 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,1);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 938 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,3);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 939 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,2);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 940 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,4);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 943 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,5);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 944 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,5);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 955 "parser.y"
    {/*Regla 17*/id_a_verificar=yylval.str;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 959 "parser.y"
    {
			/*Regla 105*/
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
#line 969 "parser.y"
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
			//GOSUB
			generar_cuadruplo_funcion(24,func,ft->dir_inicial,-1);
			;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 988 "parser.y"
    {/*Regla 44*/bandera_return = 1;;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 988 "parser.y"
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
#line 1033 "parser.y"
    {/*Regla 104*/verifica_existe_var(id_a_verificar);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1036 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,19);/*operador asigancion(=)*/;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1036 "parser.y"
    {
		//Regla 3
		printf("Genera cuadruplo =\n");
		generar_cuadruplo_asignacion();	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1043 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,1);/*operador +*/;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1044 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,4);/*operador -*/;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1045 "parser.y"
    {/*Regla 4*/generar_cuadruplo_expresion_unaria();;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1046 "parser.y"
    {verifica_existe_var(id_a_verificar); g_queue_push_head(POperadores,3);;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1046 "parser.y"
    {/*Regla 5*/generar_cuadruplo_expresion();;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1047 "parser.y"
    {/*Regla 4*/ generar_cuadruplo_expresion_unaria();;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1048 "parser.y"
    {verifica_existe_var(id_a_verificar); g_queue_push_head(POperadores,6);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1048 "parser.y"
    {/*Regla 5*/generar_cuadruplo_expresion();;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1050 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,1);;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1051 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,2);;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1052 "parser.y"
    {/*Regla 104*/verifica_existe_var(yylval.str);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1056 "parser.y"
    {
		//Regla 20
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

  case 98:

/* Line 1455 of yacc.c  */
#line 1070 "parser.y"
    {
		//Regla 22
		int final = g_queue_pop_head(PSaltos);
		//Rellenar GoTo con el contador de cuádruplos para el final
		cuadruplo *tmp = g_slice_new(cuadruplo);
		tmp = g_queue_pop_nth(cuadruplos,(guint)final-1);
		tmp->destino = contador_cuadruplos;
		g_queue_push_nth(cuadruplos,(gpointer)tmp,final-1);
	;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1081 "parser.y"
    {
		//Regla 21
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

  case 106:

/* Line 1455 of yacc.c  */
#line 1097 "parser.y"
    {
		//Regla 42
		g_queue_push_head(PSwitch,0);		
		;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1100 "parser.y"
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

  case 108:

/* Line 1455 of yacc.c  */
#line 1117 "parser.y"
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

  case 109:

/* Line 1455 of yacc.c  */
#line 1132 "parser.y"
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
		//Regla 51
		int acum = g_queue_pop_head(PSwitch);
		acum++;
		g_queue_push_head(PSwitch,acum);
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1151 "parser.y"
    {
		//Regla 26
		int operando1 = (int)g_queue_pop_head(POperandos);	
		int tipo1 = g_queue_pop_head(PTipos);
		printf("Genera cuadruplo de escribe\n");
		generar_cuadruplo(34,operando1,-1,-1);
		;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1158 "parser.y"
    { 
		//Regla 27
		if(g_queue_peek_head(POperadores) == 9){
		printf("Genera cuadruplo .\n");
		generar_cuadruplo_expresion();		
		};}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1165 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,9);/*operador concatenacion(.)*/;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1168 "parser.y"
    {/*Regla 16*/insert_constante_to_table("Lectura de pantalla",3);;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1170 "parser.y"
    {/* Regla 23*/g_queue_push_head(PSaltos,contador_cuadruplos); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1171 "parser.y"
    { 	//Regla 24
		int aux = g_queue_pop_head(PTipos);
		
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

  case 123:

/* Line 1455 of yacc.c  */
#line 1182 "parser.y"
    {
		//Regla 25
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
#line 1194 "parser.y"
    {
	//Regla 41
	printf("Genera cuadruplo de accion\n");
	generar_cuadruplo(accion,-1,-1,-1);
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1200 "parser.y"
    {
	//Regla 41
	printf("Genera cuadruplo de accion\n");
	generar_cuadruplo(accion,-1,-1,-1);	
	;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1205 "parser.y"
    {/*Regla 52*/accion = 28;;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1206 "parser.y"
    {/*Regla 52*/accion = 29;;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1207 "parser.y"
    {/*Regla 52*/accion = 30;;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1208 "parser.y"
    {/*Regla 52*/accion = 31;;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1209 "parser.y"
    {/*Regla 52*/accion = 32;;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1210 "parser.y"
    {/*Regla 52*/accion = 33;;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1213 "parser.y"
    {/*Regla 19*/insert_param_tipo();/*Regla 103*/insert_var_to_table(yylval.str,proc_actual);;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1216 "parser.y"
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

  case 143:

/* Line 1455 of yacc.c  */
#line 1250 "parser.y"
    {
	//Regla 9
	  if(g_queue_peek_head(POperadores) == 17){
  			printf("Genera cuadruplo or \n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1256 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,17);/*operador or*/;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1259 "parser.y"
    {
	//Regla 8
  if(g_queue_peek_head(POperadores) == 16){
  			printf("Genera cuadruplo and /\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1265 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,16);/*operador and*/;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1268 "parser.y"
    {
	//Regla 7
  if(valida_existencia_logico(g_queue_peek_head(POperadores))){
  			printf("Genera cuadruplo < > <= >= <>\n");
			generar_cuadruplo_expresion();		
	};}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1276 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,13);/*operador mayorque*/ exp_operador_actual = 13;;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1277 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,10);/*operador menorque*/ exp_operador_actual = 10;;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1278 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,11);/*operador diferente*/;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1279 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,15);/*operador igual igual*/;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1280 "parser.y"
    {
		//Regla 6
		int operadoranterior = g_queue_pop_head(POperadores);
		int operadorreal = dame_operador_logico(operadoranterior,exp_operador_actual);
		g_queue_push_head(POperadores,operadorreal);
		;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1289 "parser.y"
    {	//Regla 10
  	if(g_queue_peek_head(POperadores) == 1 || g_queue_peek_head(POperadores) == 4){
		printf("Genera cuadruplo + o -\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1294 "parser.y"
    { /*Regla 2*/g_queue_push_head(POperadores,1);printf("Push +\n");/*operador suma*/;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1295 "parser.y"
    { /*Regla 2*/g_queue_push_head(POperadores,4);printf("Push -\n");/*operador resta*/;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1299 "parser.y"
    {	//Regla 11
  	if(g_queue_peek_head(POperadores) == 7 || g_queue_peek_head(POperadores) == 8){
    	printf("Genera cuadruplo * o /\n");
		generar_cuadruplo_expresion();		
	};}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1305 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,7);/*operador multiplica*/;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1306 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,8);/*operador division*/;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1312 "parser.y"
    {/*Regla 12*/g_queue_push_head(POperadores,'(');;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1312 "parser.y"
    {
		/*Regla 13*/
		if(g_queue_peek_head(POperadores) == '('){
			g_queue_pop_head(POperadores);
		}else{
			printf("Error: Mala construccion de expresión en la línea %d\n",yylineno);
			exit(1);
		}
		//Regla 14
		if(g_queue_peek_head(POperadores) == 18){
			printf("Genera cuadruplo not\n");
			generar_cuadruplo_expresion_unaria();
		}
		;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1326 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1328 "parser.y"
    {
	//Regla 15
  	if(g_queue_peek_head(POperadores) == 18 || g_queue_peek_head(POperadores) == 20){
		printf("Genera cuadruplo not o - \n");
		generar_cuadruplo_expresion_unaria();
	}
	;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1335 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,20);/*operador multiplica*/;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1336 "parser.y"
    {/*Regla 2*/g_queue_push_head(POperadores,18);/*operador NOT*/;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1338 "parser.y"
    {/*Regla 17*/id_a_verificar=yylval.str;;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1339 "parser.y"
    {
		//Regla 105
		verifica_existe_procs(id_a_verificar);
					
		//Regla 36
		g_queue_push_head(PFunciones,id_a_verificar);
		//ERA
		generar_cuadruplo_funcion(25,id_a_verificar,-1,-1);
		g_queue_push_head(PParametros,0);
			
	;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
    {
		//verifica_existe_procs(id_a_verificar);
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

  case 194:

/* Line 1455 of yacc.c  */
#line 1368 "parser.y"
    {	//Regla 1
         	verifica_existe_var(id_a_verificar);
         	
         	;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    {/*Regla 104*/verifica_existe_var(yylval.str);;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1374 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.integer,1);;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1375 "parser.y"
    {/*Regla 16*/insert_constante_to_table(yylval.str,4);;}
    break;



/* Line 1455 of yacc.c  */
#line 3522 "parser.tab.c"
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
#line 1378 "parser.y"
 
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


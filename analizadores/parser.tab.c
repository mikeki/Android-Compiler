
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
static char *proc_actual;
static char *tipo_actual;
static char *id_a_verificar;
/*
Estructuras para las tabalase de procedimientos y tabla de variables
*/
typedef struct{
GHashTable *var_table;
}funcion;

typedef struct{
char *tipo;
char *nombre;
}variable;

/*
CUBO SEMANTICO
*/
char cubo[6][6][19] =
	{
		{//SUMA(+)
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
		{//MAYORQUE(>)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
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
		{//MASMAS(++)
			{'E','E','E','E','E','I'},
			{'E','E','E','E','E','E'},
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
		{//MAYORIGUAL(>=)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','E','E','E','E'},
			{'E','E','E','E','E','E'},
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
		{//MASIGUAL(+=)
			{'I','F','E','E','E','E'},
			{'F','F','E','E','E','E'},
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
		},
		{//IGUALIGUAL(==)
			{'L','L','E','E','E','E'},
			{'L','L','E','E','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','L','L','E','E'},
			{'E','E','E','E','L','E'},
			{'E','E','E','E','E','E'}
		}
	};

/*
Descripcion: Inicializa la tabla de dir_procs (directorio de procedimientos)

Parametros: void
Salida:void
*/
void create_dir_table(){
	dir_procs = g_hash_table_new(g_str_hash, g_str_equal);
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
		g_hash_table_insert(tabla->var_table,(gpointer)name,(gpointer)temp);
		//g_hash_table_foreach(tabla->var_table,(GHFunc)printf,NULL);
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
#line 357 "parser.tab.c"

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
#line 283 "parser.y"
 
int integer; 
float float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 453 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 465 "parser.tab.c"

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
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNRULES -- Number of states.  */
#define YYNSTATES  239

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
     295,   297,   298,   301,   304,   305,   308,   311,   312,   315,
     318,   319,   322,   325,   326,   329,   332,   334,   336,   337,
     340,   343,   346,   347,   350,   353,   356,   357,   359,   361,
     363,   367,   370,   372,   374,   375,   376,   380,   384,   385,
     387,   389
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
     124,    42,    35,    98,    36,    -1,    17,   135,    37,    38,
      35,    71,    36,    99,    -1,    98,    -1,    -1,    21,    41,
     101,    42,    33,    -1,   102,    -1,    73,   103,    -1,   124,
     103,    -1,    47,   102,    -1,    -1,    22,    41,    42,    -1,
      12,    41,   116,    42,    35,    71,    36,    -1,   109,    41,
     107,    42,    33,    -1,   114,    -1,    -1,   109,    41,   107,
      42,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,    72,   111,    -1,    -1,    50,   112,
     113,    -1,    32,   111,    -1,   110,    -1,    -1,   124,   115,
      -1,    32,   114,    -1,    -1,   118,   117,    -1,    28,   116,
      -1,    -1,   120,   119,    -1,    27,   118,    -1,    -1,   124,
     121,    -1,   122,   120,    -1,    -1,    38,   123,    -1,    39,
     123,    -1,    40,    -1,    37,    -1,    -1,   126,   125,    -1,
      43,   124,    -1,    44,   124,    -1,    -1,   128,   127,    -1,
      45,   126,    -1,    46,   126,    -1,    -1,   129,    -1,   130,
      -1,   132,    -1,    41,   116,    42,    -1,   131,    73,    -1,
      44,    -1,    29,    -1,    -1,    -1,    50,   133,   134,    -1,
      41,    81,    42,    -1,    -1,    50,    -1,    52,    -1,    51,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   303,   303,   303,   304,   305,   306,   307,   308,   310,
     311,   311,   312,   313,   314,   315,   316,   317,   318,   320,
     320,   321,   322,   323,   324,   326,   326,   328,   329,   331,
     332,   333,   334,   335,   337,   338,   339,   340,   341,   342,
     343,   344,   346,   347,   349,   350,   351,   352,   353,   354,
     356,   356,   357,   358,   360,   360,   362,   363,   365,   367,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   397,   398,
     399,   400,   401,   402,   404,   406,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   419,   420,   420,   421,
     422,   423,   424,   425,   426,   428,   430,   431,   433,   434,
     435,   437,   438,   439,   440,   441,   442,   443,   444,   446,
     447,   448,   449,   451,   452,   453,   454,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   464,   465,   466,   468,
     469,   470
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
  "mmexpp", "mexp", "mexpp", "expresion", "expresionp", "ep", "epp", "exp",
  "expp", "termino", "terminop", "factor", "factorp", "factorpp", "f",
  "factorppp", "$@9", "fun_var", "varselecciona", 0
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
     113,   113,   114,   115,   115,   116,   117,   117,   118,   119,
     119,   120,   121,   121,   122,   122,   122,   123,   123,   124,
     125,   125,   125,   126,   127,   127,   127,   128,   128,   128,
     129,   130,   131,   131,   131,   133,   132,   134,   134,   135,
     135,   135
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
       1,     0,     2,     2,     0,     2,     2,     0,     2,     2,
       0,     2,     2,     0,     2,     2,     1,     1,     0,     2,
       2,     2,     0,     2,     2,     2,     0,     1,     1,     1,
       3,     2,     1,     1,     0,     0,     3,     3,     0,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,    29,    30,    33,
      32,    31,     0,     8,     6,     0,    25,     3,     0,     4,
       8,     5,    10,     0,     0,    19,     7,    14,     9,    28,
       0,     0,   144,    11,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,    50,    49,     0,    28,    44,    45,
      75,    76,    46,    47,    48,     0,    24,    12,     0,   143,
     144,   142,   145,    18,    15,    16,   117,   120,   123,   132,
     136,   137,   138,     0,   139,   144,   144,   144,     0,     0,
      26,    27,   144,     0,     0,    23,     0,     0,   148,     0,
      13,   144,   115,   144,   118,   128,   128,   126,   121,   144,
     144,   144,   129,   144,   144,   133,    39,    38,    40,    41,
      36,    35,    37,    34,   141,     0,    79,     0,    78,     0,
       0,    93,     0,    89,    93,   144,   144,     0,     0,    51,
      52,    53,    59,    61,    62,    66,    67,     0,    97,   114,
       0,   107,   106,    94,   140,   144,   146,    17,   116,   119,
     127,   124,   125,   122,   130,   131,   134,   135,     0,   144,
       0,     0,     0,    90,     0,    91,    63,    64,    65,     0,
      56,     0,    68,     0,    69,     0,     0,   144,   112,    22,
     111,     0,    28,     0,    28,     0,    92,    88,    54,    73,
      74,    72,    70,    71,    60,    96,   113,   144,     0,    22,
      42,    43,     0,   110,   108,   147,     0,    99,     0,     0,
       0,     0,     0,    20,    21,   109,    81,    95,   149,   151,
     150,     0,    84,    55,    58,     0,    77,     0,    28,    82,
      80,     0,     0,    28,    83,     0,    87,    86,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    12,    13,    19,    45,    23,    27,    33,
      63,    90,    20,    30,   198,    83,    17,    24,    46,    15,
     121,   199,    47,    48,    79,   129,   130,   211,   169,   201,
     131,   175,   132,   133,   166,   134,   135,   136,   192,    49,
      50,   115,   226,   230,    51,   210,   238,    52,   122,   123,
     163,    64,    53,    54,   137,   116,    55,    85,   142,   180,
     204,   138,   178,    65,    92,    66,    94,    67,    98,    99,
     151,    68,   102,    69,   105,    70,    71,    72,    73,    74,
      88,   146,   221
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -169
static const yytype_int16 yypact[] =
{
      -2,   -40,    47,  -169,  -169,    34,   152,  -169,  -169,  -169,
    -169,  -169,    49,    57,   152,    29,  -169,  -169,    45,  -169,
      57,  -169,  -169,    51,    62,  -169,  -169,   -19,  -169,    86,
      63,    29,   112,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
      72,    80,    81,    88,  -169,  -169,    91,    86,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,    92,   152,  -169,    98,  -169,
      14,  -169,  -169,   110,  -169,  -169,   124,   134,    43,    16,
      41,  -169,  -169,   106,  -169,    70,    14,    14,    99,    75,
    -169,  -169,   -20,   121,   118,  -169,   127,   128,   132,    29,
    -169,    14,  -169,    14,  -169,   137,   137,  -169,  -169,    14,
      14,    14,  -169,    14,    14,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,   133,  -169,   138,  -169,   136,
     140,   141,   142,  -169,   141,   112,    12,   -14,   -25,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,   143,  -169,   148,
     154,  -169,  -169,  -169,  -169,    12,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,   155,   -20,
     156,   157,    99,  -169,   160,  -169,  -169,  -169,  -169,   153,
    -169,    17,  -169,    17,  -169,   161,   163,    14,  -169,    30,
     145,   158,    86,   159,    86,   170,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,    14,   162,    30,
    -169,  -169,   118,  -169,  -169,  -169,   166,  -169,   167,    94,
     168,   164,   172,  -169,  -169,  -169,   188,  -169,  -169,  -169,
    -169,   169,  -169,  -169,  -169,     4,  -169,   171,    86,  -169,
    -169,   173,   174,    86,  -169,   175,   170,  -169,  -169
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,  -169,  -169,   193,   192,     1,   -26,  -169,  -169,
    -169,  -169,  -169,  -169,    15,  -169,  -169,  -169,   -47,   -54,
     144,  -169,  -168,  -169,  -169,  -169,  -169,  -169,    68,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    42,    -9,
    -169,  -169,  -169,  -169,  -169,   -18,  -169,  -169,  -169,    58,
      95,    96,  -169,  -169,    64,  -169,   147,    44,    23,  -169,
    -169,  -120,  -169,   -59,  -169,   135,  -169,   130,  -169,  -169,
     131,   -74,  -169,     6,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -99
static const yytype_int16 yytable[] =
{
      81,    87,    84,   120,   124,    57,   170,    14,   139,    59,
       3,   200,   173,    31,    40,    14,   118,   119,    32,   174,
      42,    60,   -98,   171,    61,   170,   154,   155,     1,   172,
      62,   200,   148,    34,    35,    36,    37,    38,    39,   228,
      40,    59,    41,    59,     7,     8,    42,     4,   197,     9,
      10,    43,   139,    60,   -57,    60,    61,   196,    61,   100,
     101,    11,    62,   147,    62,   189,   168,   190,     6,   191,
      18,   139,    16,    34,    35,    36,    37,    38,    39,    22,
      44,    95,    96,    97,    28,   139,   103,   104,   124,    34,
      35,    36,    37,    38,    39,    25,    40,    29,    41,    59,
       7,     8,    42,   139,    56,     9,    10,    43,   106,   156,
     157,    60,   125,    75,    61,   106,   126,    11,   127,   128,
      62,    76,    77,   107,   108,   109,    84,    80,    59,    78,
     107,   108,   109,    82,    58,   206,    44,   208,   212,    86,
      60,    59,    89,    61,   218,   219,   220,   110,   111,    62,
     112,   113,    91,    60,   110,   111,    61,   112,   113,     7,
       8,    93,    62,   140,     9,    10,     7,     8,   141,   143,
     144,     9,    10,   145,   150,   158,    11,   202,   160,   159,
     177,   232,   161,    11,   164,   176,   235,   209,   162,   179,
     182,   184,   185,   187,   194,   188,   195,   223,   213,   225,
     205,   207,   216,   217,   222,   224,   227,    21,   233,   231,
     234,   236,    26,   181,   214,   193,   229,   114,   237,   165,
     186,   167,   117,   183,   203,   215,     0,   152,   149,   153
};

static const yytype_int16 yycheck[] =
{
      47,    60,    56,    77,    78,    31,   126,     6,    82,    29,
      50,   179,    37,    32,    10,    14,    75,    76,    37,    44,
      16,    41,    42,    37,    44,   145,   100,   101,    30,    43,
      50,   199,    91,     3,     4,     5,     6,     7,     8,    35,
      10,    29,    12,    29,    14,    15,    16,     0,    18,    19,
      20,    21,   126,    41,    42,    41,    44,   177,    44,    43,
      44,    31,    50,    89,    50,    48,   125,    50,    34,    52,
      13,   145,    23,     3,     4,     5,     6,     7,     8,    50,
      50,    38,    39,    40,    33,   159,    45,    46,   162,     3,
       4,     5,     6,     7,     8,    50,    10,    35,    12,    29,
      14,    15,    16,   177,    41,    19,    20,    21,     9,   103,
     104,    41,    37,    41,    44,     9,    41,    31,    43,    44,
      50,    41,    41,    24,    25,    26,   180,    36,    29,    41,
      24,    25,    26,    41,    22,   182,    50,   184,   197,    41,
      41,    29,    32,    44,    50,    51,    52,    48,    49,    50,
      51,    52,    28,    41,    48,    49,    44,    51,    52,    14,
      15,    27,    50,    42,    19,    20,    14,    15,    50,    42,
      42,    19,    20,    41,    37,    42,    31,    32,    42,    41,
      32,   228,    42,    31,    42,    42,   233,    17,    47,    35,
      35,    35,    35,    33,    33,    42,    33,    33,    36,    11,
      42,    42,    36,    36,    36,    33,    37,    14,    35,    38,
      36,    36,    20,   145,   199,   173,   225,    73,   236,   124,
     162,   125,    75,   159,   180,   202,    -1,    96,    93,    99
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
      41,    44,    50,    63,   104,   116,   118,   120,   124,   126,
     128,   129,   130,   131,   132,    41,    41,    41,    41,    77,
      36,    71,    41,    68,    72,   110,    41,   116,   133,    32,
      64,    28,   117,    27,   119,    38,    39,    40,   121,   122,
      43,    44,   125,    45,    46,   127,     9,    24,    25,    26,
      48,    49,    51,    52,    73,    94,   108,   109,   116,   116,
     124,    73,   101,   102,   124,    37,    41,    43,    44,    78,
      79,    83,    85,    86,    88,    89,    90,   107,   114,   124,
      42,    50,   111,    42,    42,    41,   134,    60,   116,   118,
      37,   123,   123,   120,   124,   124,   126,   126,    42,    41,
      42,    42,    47,   103,    42,   103,    87,   104,   116,    81,
     114,    37,    43,    37,    44,    84,    42,    32,   115,    35,
     112,    81,    35,   107,    35,    35,   102,    33,    42,    48,
      50,    52,    91,    91,    33,    33,   114,    18,    67,    74,
      75,    82,    32,   110,   113,    42,    71,    42,    71,    17,
      98,    80,   116,    36,    67,   111,    36,    36,    50,    51,
      52,   135,    36,    33,    33,    11,    95,    37,    35,    92,
      96,    38,    71,    35,    36,    71,    36,    98,    99
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
#line 303 "parser.y"
    {insert_proc_to_table("programa");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 320 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {tipo_actual= "entero";;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {tipo_actual= "flotante";;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {tipo_actual= "caracter";;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 334 "parser.y"
    {tipo_actual= "string";;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 335 "parser.y"
    {tipo_actual= "logico";;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 356 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 367 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 381 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    {id_a_verificar=yylval.str;;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 465 "parser.y"
    {verifica_existe_procs(id_a_verificar);;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 466 "parser.y"
    {verifica_existe_var(id_a_verificar);;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 468 "parser.y"
    {verifica_existe_var(yylval.str);;}
    break;



/* Line 1455 of yacc.c  */
#line 2025 "parser.tab.c"
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
#line 473 "parser.y"
 
main() { 
create_dir_table();
  yyparse(); 
imprime(dir_procs); 

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


free(dir_procs);
}

yyerror(char *s){
       printf("%s \n", s);
}


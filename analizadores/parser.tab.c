
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
	g_hash_table_foreach(tabla->var_table,(GHFunc)printf,NULL);
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
#line 162 "parser.tab.c"

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
#line 88 "parser.y"
 
int integer; 
float float_n;
char *str; 



/* Line 214 of yacc.c  */
#line 258 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 270 "parser.tab.c"

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
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNRULES -- Number of states.  */
#define YYNSTATES  236

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
      23,    28,    30,    32,    35,    38,    41,    42,    47,    49,
      51,    52,    53,    63,    66,    67,    69,    70,    71,    77,
      80,    81,    83,    85,    87,    89,    91,    93,    95,    97,
      99,   101,   103,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,   129,   131,   133,   135,   137,
     141,   144,   146,   148,   151,   154,   157,   159,   161,   165,
     169,   174,   179,   181,   183,   185,   187,   189,   198,   201,
     202,   204,   208,   216,   225,   227,   228,   234,   236,   239,
     242,   245,   246,   250,   258,   264,   266,   267,   272,   274,
     276,   278,   280,   282,   284,   286,   289,   292,   295,   297,
     298,   301,   304,   305,   309,   311,   312,   315,   316,   320,
     323,   324,   328,   331,   332,   335,   338,   340,   342,   343,
     346,   349,   352,   353,   356,   359,   362,   363,   365,   367,
     371,   374,   376,   377,   379,   381
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    -1,    30,    50,    55,    34,    56,    71,
      -1,    57,    58,    -1,    59,    57,    -1,    -1,    67,    58,
      -1,    -1,    -1,    74,    50,    60,    61,    -1,    62,    -1,
      64,    -1,    37,    63,    -1,    98,    33,    -1,   109,    33,
      -1,    -1,    32,    50,    65,    66,    -1,    33,    -1,    64,
      -1,    -1,    -1,    13,    50,    68,    41,    70,    42,    35,
      69,    36,    -1,    76,    69,    -1,    -1,   104,    -1,    -1,
      -1,    23,    72,    35,    73,    36,    -1,    77,    73,    -1,
      -1,    14,    -1,    15,    -1,    31,    -1,    20,    -1,    19,
      -1,    50,    -1,    52,    -1,    49,    -1,    48,    -1,    51,
      -1,    24,    -1,     9,    -1,    25,    -1,    26,    -1,   102,
      -1,    79,    -1,    87,    -1,    94,    -1,    99,    -1,   100,
      -1,    59,    -1,    78,    -1,    79,    -1,    87,    -1,    94,
      -1,    99,    -1,   100,    -1,    59,    -1,    18,   109,    33,
      -1,    50,    80,    -1,    81,    -1,    83,    -1,    37,    82,
      -1,    98,    33,    -1,   109,    33,    -1,    84,    -1,    85,
      -1,    43,    43,    33,    -1,    44,    44,    33,    -1,    43,
      37,    86,    33,    -1,    44,    37,    86,    33,    -1,    52,
      -1,    48,    -1,    50,    -1,    88,    -1,    91,    -1,    10,
      41,   109,    42,    35,    73,    36,    89,    -1,    11,    90,
      -1,    -1,    87,    -1,    35,    73,    36,    -1,    16,    41,
     118,    42,    35,    92,    36,    -1,    17,   126,    37,    38,
      35,    73,    36,    93,    -1,    92,    -1,    -1,    21,    41,
      95,    42,    33,    -1,    96,    -1,    75,    97,    -1,   118,
      97,    -1,    47,    96,    -1,    -1,    22,    41,    42,    -1,
      12,    41,   109,    42,    35,    73,    36,    -1,   103,    41,
     101,    42,    33,    -1,   107,    -1,    -1,   103,    41,   101,
      42,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,    50,    -1,    74,   105,    -1,    50,
     106,    -1,    32,   105,    -1,   104,    -1,    -1,   118,   108,
      -1,    32,   107,    -1,    -1,   110,   112,   111,    -1,    29,
      -1,    -1,    28,   112,    -1,    -1,   110,   114,   113,    -1,
      27,   114,    -1,    -1,   110,   118,   115,    -1,   116,   118,
      -1,    -1,    38,   117,    -1,    39,   117,    -1,    40,    -1,
      37,    -1,    -1,   120,   119,    -1,    43,   118,    -1,    44,
     118,    -1,    -1,   122,   121,    -1,    45,   120,    -1,    46,
     120,    -1,    -1,   123,    -1,   124,    -1,    41,   109,    42,
      -1,   125,    75,    -1,    44,    -1,    -1,    50,    -1,    52,
      -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   108,   108,   108,   109,   110,   111,   112,   113,   115,
     115,   116,   117,   118,   119,   120,   121,   121,   122,   123,
     124,   126,   126,   127,   128,   129,   130,   132,   132,   134,
     135,   137,   138,   139,   140,   141,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   154,   155,   156,   157,
     158,   159,   160,   162,   163,   164,   165,   166,   167,   170,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   200,   201,   202,   203,
     204,   205,   207,   209,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   223,   224,   225,   226,   227,
     228,   229,   230,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   253,   254,   255,   256,   258,   259,   260,
     261,   262,   263,   265,   266,   267
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
  "vars", "$@2", "varsp", "lva", "lvap", "varid", "$@3", "varidp",
  "funcion", "$@4", "funcionp", "funcionpp", "main", "$@5", "bloque",
  "tipo", "varcte", "estatutofuncion", "estatuto", "regresa", "asignacion",
  "asignacionp", "asigp", "lea", "asigpp", "ap", "app", "atipo",
  "condicion", "c", "sip", "sipp", "cp", "cuandop", "cuandopp",
  "escritura", "escriturap", "escriturapp", "e", "lectura", "ciclo",
  "accion", "accionp", "accionsi", "acciones", "params", "paramsp",
  "paramspp", "params2", "params2p", "mmexp", "nop", "mmexpp", "mexp",
  "mexpp", "expresion", "expresionp", "ep", "epp", "exp", "expp",
  "termino", "terminop", "factor", "factorp", "factorpp", "f",
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
       0,    53,    55,    54,    56,    57,    57,    58,    58,    60,
      59,    61,    61,    62,    63,    63,    65,    64,    64,    66,
      66,    68,    67,    69,    69,    70,    70,    72,    71,    73,
      73,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    77,    77,    78,
      79,    80,    80,    81,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    86,    87,    87,    88,    89,    89,
      90,    90,    91,    92,    93,    93,    94,    95,    96,    96,
      97,    97,    98,    99,   100,   101,   101,   102,   103,   103,
     103,   103,   103,   103,   103,   104,   105,   106,   106,   106,
     107,   108,   108,   109,   110,   110,   111,   111,   112,   113,
     113,   114,   115,   115,   116,   116,   116,   117,   117,   118,
     119,   119,   119,   120,   121,   121,   121,   122,   122,   123,
     124,   125,   125,   126,   126,   126
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     2,     2,     0,     2,     0,     0,
       4,     1,     1,     2,     2,     2,     0,     4,     1,     1,
       0,     0,     9,     2,     0,     1,     0,     0,     5,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     1,     1,     2,     2,     2,     1,     1,     3,     3,
       4,     4,     1,     1,     1,     1,     1,     8,     2,     0,
       1,     3,     7,     8,     1,     0,     5,     1,     2,     2,
       2,     0,     3,     7,     5,     1,     0,     4,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     0,
       2,     2,     0,     3,     1,     0,     2,     0,     3,     2,
       0,     3,     2,     0,     2,     2,     1,     1,     0,     2,
       2,     2,     0,     2,     2,     2,     0,     1,     1,     3,
       2,     1,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,    31,    32,    35,
      34,    33,     0,     8,     6,     0,    27,     3,     0,     4,
       8,     5,     9,     0,    21,     7,     0,    30,     0,     0,
      18,   115,    10,    11,    12,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,   104,    58,     0,    30,    53,
      54,    75,    76,    55,    56,    57,     0,    26,    16,     0,
     114,    13,     0,     0,   115,   115,   115,   142,     0,   115,
       0,     0,    60,    61,    62,    66,    67,    28,    29,   142,
       0,     0,    25,    20,     0,    14,    15,   115,   117,     0,
       0,   115,   141,     0,   132,   136,   137,   138,     0,    42,
      41,    43,    44,    39,    38,    36,    40,    37,    91,     0,
      87,    45,     0,    91,    63,     0,     0,     0,     0,     0,
       0,     0,    95,   112,     0,   109,   105,    19,    17,    92,
     142,   120,   115,   113,     0,     0,     0,     0,   142,   142,
     129,   142,   142,   133,   140,     0,    88,     0,   142,    89,
      64,    65,    73,    74,    72,     0,    68,     0,    69,     0,
     142,   110,    24,     0,   108,   106,   123,   115,   118,   116,
      30,    30,   139,     0,   130,   131,   134,   135,    90,    86,
       0,    70,    71,    94,   111,   115,    51,     0,    24,    52,
      46,    47,    48,    49,    50,   107,   128,   128,   126,   121,
     142,   119,     0,     0,     0,     0,    97,     0,    22,    23,
     127,   124,   125,   122,    79,    93,   143,   145,   144,     0,
      82,    59,     0,    77,     0,    30,    80,    78,     0,     0,
      30,    81,     0,    85,    84,    83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    12,    13,    19,    46,    26,    32,    33,
      61,    34,    83,   128,    20,    28,   187,    80,    17,    23,
      47,    15,   108,   188,    48,   189,    49,    72,    73,   114,
      74,    75,    76,   155,    50,    51,   223,   227,    52,   205,
     235,    53,   109,   110,   146,    62,    54,    55,   121,   111,
      56,    82,   126,   165,   122,   161,    63,    64,   133,    88,
     168,   131,   199,   200,   211,   123,   140,    94,   143,    95,
      96,    97,    98,   219
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -152
static const yytype_int16 yypact[] =
{
     -13,   -31,    45,  -152,  -152,    24,    41,  -152,  -152,  -152,
    -152,  -152,    88,    99,    41,    64,  -152,  -152,    65,  -152,
      99,  -152,  -152,    82,  -152,  -152,    16,   182,    75,    68,
    -152,    28,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,    78,    79,    80,    84,    54,  -152,    90,   182,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,    86,    41,  -152,    87,
    -152,  -152,   101,   103,   114,   114,   114,    52,    18,    28,
      -9,    55,  -152,  -152,  -152,  -152,  -152,  -152,  -152,    35,
     105,    95,  -152,    -1,   109,  -152,  -152,   114,   128,   116,
     117,   114,  -152,   118,    38,    49,  -152,  -152,    81,  -152,
    -152,  -152,  -152,  -152,  -152,   120,  -152,  -152,   115,   121,
    -152,  -152,   123,   115,  -152,   133,   135,   -32,   136,   -32,
     137,   125,  -152,   139,   138,    32,  -152,  -152,  -152,  -152,
      52,   145,   114,  -152,   140,   141,   132,   143,    52,    52,
    -152,    52,    52,  -152,  -152,    18,  -152,   146,    35,  -152,
    -152,  -152,  -152,  -152,  -152,   147,  -152,   148,  -152,   158,
      52,  -152,   134,    95,  -152,  -152,    62,   114,  -152,  -152,
     182,   182,  -152,   176,  -152,  -152,  -152,  -152,  -152,  -152,
     153,  -152,  -152,  -152,  -152,   114,  -152,   163,   134,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,   167,   167,  -152,  -152,
      52,  -152,   164,   169,    58,   170,  -152,   174,  -152,  -152,
    -152,  -152,  -152,  -152,   197,  -152,  -152,  -152,  -152,   172,
    -152,  -152,    19,  -152,   173,   182,  -152,  -152,   175,   178,
     182,  -152,   179,   176,  -152,  -152
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,   198,   196,    -5,  -152,  -152,  -152,
    -152,   142,  -152,  -152,  -152,  -152,    29,  -152,  -152,  -152,
     -48,   -50,   122,  -152,  -152,  -152,  -150,  -152,  -152,  -152,
    -152,  -152,  -152,   100,  -151,  -152,  -152,  -152,  -152,   -15,
    -152,  -149,  -152,    76,   110,   155,  -148,  -147,    74,  -152,
     -62,   102,    63,  -152,    69,  -152,   -61,   -54,  -152,    96,
    -152,    66,  -152,  -152,    33,   -65,  -152,   -38,  -152,  -152,
    -152,  -152,  -152,  -152
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -105
static const yytype_int16 yytable[] =
{
      78,    14,    93,   113,    89,    90,   112,    81,   116,    14,
      87,   191,   190,   192,   193,   194,   152,     1,   153,     3,
     154,    35,    36,    37,    38,    39,    40,    99,   117,    41,
     136,    29,    30,   130,   118,    43,   112,   191,   190,   192,
     193,   194,   100,   101,   102,     4,     7,     8,    29,    30,
      59,     9,    10,    31,   225,     7,     8,    60,     6,    91,
       9,    10,    92,    11,   163,   166,   103,   104,   105,   106,
     107,   226,    11,   174,   175,    81,    91,   -96,    87,    92,
     113,   138,   139,   112,    35,    36,    37,    38,    39,    40,
      99,    69,   119,    91,   141,   142,    92,    70,    71,   120,
     196,   197,   198,   176,   177,   100,   101,   102,   216,   217,
     218,    16,    18,   130,    22,    24,    57,    27,    58,    65,
      66,    67,   202,   203,   207,    68,    77,    79,    84,   103,
     104,   105,   106,   107,    85,   213,    86,    35,    36,    37,
      38,    39,    40,    60,    41,   125,    42,   124,     7,     8,
      43,   129,   185,     9,    10,    44,   132,   186,   134,   135,
     137,  -104,   145,   147,   148,    11,   150,   159,   151,   156,
     158,   160,   167,   162,   172,   170,   171,   229,   173,   179,
     181,   182,   232,   186,    45,    35,    36,    37,    38,    39,
      40,   183,    41,   204,    42,   206,     7,     8,    43,   208,
     214,     9,    10,    44,   210,   215,   220,   221,   222,   224,
     230,   228,    21,    11,   231,   233,    25,   209,   234,   157,
     144,   178,   180,   149,   115,   127,   195,   164,   169,   184,
     212,     0,    45,   201
};

static const yytype_int16 yycheck[] =
{
      48,     6,    67,    68,    65,    66,    68,    57,    69,    14,
      64,   162,   162,   162,   162,   162,    48,    30,    50,    50,
      52,     3,     4,     5,     6,     7,     8,     9,    37,    10,
      91,    32,    33,    87,    43,    16,    98,   188,   188,   188,
     188,   188,    24,    25,    26,     0,    14,    15,    32,    33,
      22,    19,    20,    37,    35,    14,    15,    29,    34,    41,
      19,    20,    44,    31,    32,   130,    48,    49,    50,    51,
      52,   222,    31,   138,   139,   125,    41,    42,   132,    44,
     145,    43,    44,   145,     3,     4,     5,     6,     7,     8,
       9,    37,    37,    41,    45,    46,    44,    43,    44,    44,
      38,    39,    40,   141,   142,    24,    25,    26,    50,    51,
      52,    23,    13,   167,    50,    50,    41,    35,    50,    41,
      41,    41,   170,   171,   185,    41,    36,    41,    41,    48,
      49,    50,    51,    52,    33,   200,    33,     3,     4,     5,
       6,     7,     8,    29,    10,    50,    12,    42,    14,    15,
      16,    42,    18,    19,    20,    21,    28,   162,    42,    42,
      42,    41,    47,    42,    41,    31,    33,    42,    33,    33,
      33,    32,    27,    35,    42,    35,    35,   225,    35,    33,
      33,    33,   230,   188,    50,     3,     4,     5,     6,     7,
       8,    33,    10,    17,    12,    42,    14,    15,    16,    36,
      36,    19,    20,    21,    37,    36,    36,    33,    11,    37,
      35,    38,    14,    31,    36,    36,    20,   188,   233,   119,
      98,   145,   148,   113,    69,    83,   163,   125,   132,   160,
     197,    -1,    50,   167
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    54,    50,     0,    55,    34,    14,    15,    19,
      20,    31,    56,    57,    59,    74,    23,    71,    13,    58,
      67,    57,    50,    72,    50,    58,    60,    35,    68,    32,
      33,    37,    61,    62,    64,     3,     4,     5,     6,     7,
       8,    10,    12,    16,    21,    50,    59,    73,    77,    79,
      87,    88,    91,    94,    99,   100,   103,    41,    50,    22,
      29,    63,    98,   109,   110,    41,    41,    41,    41,    37,
      43,    44,    80,    81,    83,    84,    85,    36,    73,    41,
      70,    74,   104,    65,    41,    33,    33,   110,   112,   109,
     109,    41,    44,   118,   120,   122,   123,   124,   125,     9,
      24,    25,    26,    48,    49,    50,    51,    52,    75,    95,
      96,   102,   103,   118,    82,    98,   109,    37,    43,    37,
      44,   101,   107,   118,    42,    50,   105,    64,    66,    42,
     110,   114,    28,   111,    42,    42,   109,    42,    43,    44,
     119,    45,    46,   121,    75,    47,    97,    42,    41,    97,
      33,    33,    48,    50,    52,    86,    33,    86,    33,    42,
      32,   108,    35,    32,   104,   106,   118,    27,   113,   112,
      35,    35,    42,    35,   118,   118,   120,   120,    96,    33,
     101,    33,    33,    33,   107,    18,    59,    69,    76,    78,
      79,    87,    94,    99,   100,   105,    38,    39,    40,   115,
     116,   114,    73,    73,    17,    92,    42,   109,    36,    69,
      37,   117,   117,   118,    36,    36,    50,    51,    52,   126,
      36,    33,    11,    89,    37,    35,    87,    90,    38,    73,
      35,    36,    73,    36,    92,    93
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
#line 108 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 121 "parser.y"
    {insert_var_to_table(yylval.str);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 126 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    {insert_proc_to_table(yylval.str);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    {tipo_actual= "entero";;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    {tipo_actual= "flotante";;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    {tipo_actual= "caracter";;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    {tipo_actual= "string";;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    {tipo_actual= "logico";;}
    break;



/* Line 1455 of yacc.c  */
#line 1768 "parser.tab.c"
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
#line 270 "parser.y"
 
main() { 
create_dir_table();
  yyparse(); 
imprime(dir_procs);
free(dir_procs);
}

yyerror(char *s){
       printf("%s \n", s);
}


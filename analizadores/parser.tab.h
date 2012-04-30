
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 864 "parser.y"
 
char *integer; 
char *float_n;
char *str; 



/* Line 1676 of yacc.c  */
#line 113 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



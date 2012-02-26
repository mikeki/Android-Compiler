# Makefile: A simple makefile for ex1.
default:
		bison -d parser.y
		bison parser.y
		flex scanner.l
		gcc -o android parser.tab.c lex.yy.c -lfl

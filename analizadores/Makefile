# Makefile: A simple makefile for ex1.
default:
		bison -d parser.y
		bison parser.y
		flex scanner.l
		gcc -o android -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0 parser.tab.c lex.yy.c -lfl `pkg-config --libs --cflags glib-2.0`

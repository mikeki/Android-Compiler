%union{ 
int integer; 
float float_n;
char *str; 
} 
%token ADELANTE ATRAS ROTADERECHA ROTAIZQUIERDA TOMARTESORO TOPA
%token VERPISTA SI SINO MIENTRAS FUNCION ENTERO FLOTANTE SELECCIONA CUANDO
%token REGRESA LOGICO PALABRA ESCRIBE LEE PRINCIPAL VACIO VERDADERO FALSO
%token Y O NO PROGRAMA CARACTER COMA PUNTOCOMA IGUALP ALLAVE CLLAVE
%token IGUALR MAYORQUE MENORQUE DIFERENTE APARENTESIS CPARENTESIS
%token MAS MENOS POR ENTRE CONCA
%token <float_n> CTF
%token <str> CTESTRING
%token <str> ID
%token <str> CAR
%token <integer> CTE

%start programa

%% 
programa: PROGRAMA ID IGUALP programap main;
programap: programapp programappp;
programapp: 	vars programapp
		| ;
programappp: funcion programappp
		| ;

vars: tipo ID varsp;
varsp: lva
	|varid;
lva: IGUALR lvap;
lvap: lectura PUNTOCOMA
	| varcte PUNTOCOMA
	| accion;
varid: COMA ID varidp
	| PUNTOCOMA;
varidp: varid 
	| ;

funcion: FUNCION ID APARENTESIS funcionpp CPARENTESIS ALLAVE funcionp CLLAVE;
funcionp: estatutofuncion funcionp
	| ;
funcionpp: params 
	| ;

main: PRINCIPAL ALLAVE bloque CLLAVE;

bloque: estatuto bloque
	| ;

tipo:	 ENTERO
	|FLOTANTE
	| CARACTER
	| PALABRA
	| LOGICO ;

varcte: ID
	| CTE
	| CTESTRING
	| CTF
	| CAR
	| VACIO
	| VERPISTA
	| VERDADERO
	| FALSO
	| accionsi;

estatutofuncion: asignacion
		|condicion
		|escritura
		|ciclo
		|accion
		|funcion
		|vars
		|regresa;

estatuto: asignacion
		|condicion
		|escritura
		|ciclo
		|accion
		|funcion
		|vars;


regresa: REGRESA mmexp PUNTOCOMA;

asignacion: 	ID asignacionp;
asignacionp: 	asigp
		| asigpp;
asigp: 		IGUALR lea;
lea: 		lectura PUNTOCOMA
		|exp PUNTOCOMA
		| accion;
asigpp:		ap 
		| app;
ap:		MAS MAS PUNTOCOMA
		|MENOS MENOS PUNTOCOMA;
app:		MAS IGUALR atipo PUNTOCOMA
		| MENOS IGUALR atipo PUNTOCOMA;
atipo:		CTE
		| CTF
		| ID;

condicion: c
	|  cp;
c:	SI APARENTESIS mmexp CPARENTESIS ALLAVE bloque CLLAVE sip;
sip:	SINO sipp
	| ;
sipp: 	condicion
	| ALLAVE bloque CLLAVE;
cp: 	SELECCIONA APARENTESIS exp CPARENTESIS ALLAVE cuandop CLLAVE;
cuandop: CUANDO varselecciona IGUALR MAYORQUE ALLAVE bloque CLLAVE cuandopp;
cuandopp: cuandop 
	| ;

escritura: ESCRIBE APARENTESIS escriturap CPARENTESIS PUNTOCOMA;
escriturap: escriturapp;
escriturapp: varcte e 
	| exp e;
e: 	CONCA escriturapp
	| ;

lectura: LEE APARENTESIS CPARENTESIS;

ciclo: MIENTRAS APARENTESIS mmexp CPARENTESIS ALLAVE bloque CLLAVE;

accion: acciones APARENTESIS accionp CPARENTESIS PUNTOCOMA;
accionp: params2 
	| ;
accionsi: acciones APARENTESIS accionp CPARENTESIS;
acciones: ADELANTE
	| ATRAS
	| ROTADERECHA
	| ROTAIZQUIERDA
	| TOMARTESORO
	| TOPA
	| ID;

params: tipo paramsp;
paramsp: ID paramspp;
paramspp: COMA paramsp
	| params
	| ;
params2: exp params2p;
params2p: COMA params2
	| ;

mmexp: nop mexp mmexpp;
nop: 	NO
	| ;
mmexpp: O mexp 
	| ;
mexp: nop expresion mexpp;
mexpp: Y expresion
	| ;
expresion: nop exp expresionp;
expresionp: ep exp 
		| ;
ep: 	MAYORQUE epp
	|MENORQUE epp
	| DIFERENTE;
epp: IGUALR 
	| ;
exp: termino expp;
expp: MAS exp
	| MENOS exp 
	| ;

termino: factor terminop;
terminop: POR termino
	| ENTRE termino
	| ;

factor: factorp 
	| factorpp;
factorp: APARENTESIS mmexp CPARENTESIS;
factorpp: f varcte;
f: 	MENOS 
	| ;

varselecciona: ID
		|CTE
		|CAR;
 

%% 
main() { 
  yyparse(); 
}

yyerror(char *s){
       printf("%s \n", s);
}

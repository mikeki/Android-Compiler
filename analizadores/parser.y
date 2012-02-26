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
programap: vars programapp
	| programapp
	| ;
programapp: funcion programapp
	| ;

vars:	tipo ID varsp PUNTOCOMA vars
	| ;
varsp:	IGUALR varspp 
	| varsppp;
varspp:	lectura 
	| varcte;
varsppp: COMA ID varspppp;
varspppp: varsppp
	| ;

funcion: ID APARENTESIS params CPARENTESIS ALLAVE funcionp CLLAVE;
funcionp: estatutofuncion funcionp
	| ;

main: PRINCIPAL ALLAVE bloque CLLAVE;

tipo:	 ENTERO
	|FLOTANTE
	| CARACTER
	| PALABRA
	| LOGICO ;

varcte: ID
	| CTE
	| CTS
	| CTF
	| CAR
	| VACIO
	| VERPISTA;

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

bloque: bloquep;
bloquep: estatuto bloquep
	| ;

regresa: REGRESA mmexp;

asignacion: ID asignacionp;
asignacionp: IGUALR asignacionpp 
		| asignacionppp;
asignacionpp: lectura
		|exp;
asignacionppp: a
		|ap;
a: 	MAS MAS 
	| MENOS MENOS;
ap: 	MAS IGUALR app
	| MENOS IGUALR app;
app: 	CTE
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

yyerror(){
}

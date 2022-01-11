%{
	/* === AUTEURS : Gaetan FREJOUX & Mathieu Niord === */

	/* === INCLUDES === */
	#include <stdio.h>
    #include "parser.tab.hh"
	
	/* === METHODS === */
	void extern yyerror(const char* s);
	void invalid_token();
	
	char* error;
	
%}

%option yylineno

INTEGER		[0-9]
ALPHANUM	[a-zA-Z0-9]

COLOR       ("NOIR"|"ROUGE"|"BLEU"|"VERT")
DIRECTION   ("gauche"|"droite"|"haut"|"bas")
NAME        {ALPHANUM}+
OPERATOR    [+\-/\*]

COMMENT		"//"(" "?{ALPHANUM}*)*

ENDL 		";"

%%

Couleur       	{ return SET_COLOR; }
Ecrire        	{ return LOWER; }
Deplace       	{ return MOVE; }
Lever         	{ return LIFT; }
Ligne         	{ return LINE; }
Rectangle     	{ return RECT; }

entier			{ return DEC; }	
pour          	{ return BEGIN_FOR; }
"fin pour"      { return END_FOR; }

"(" 			{ return LPAR; }
")" 			{ return RPAR; }
"," 			{ return VIRG; }
"<-"            { return AFFECT; }

{INTEGER}		{ yylval.intVal = atoi(yytext); return _number; }
{COLOR}         { yylval.colorVal = strdup(yytext); return _color; }
{DIRECTION}     { yylval.directionVal = strdup(yytext); return _direction; }
{OPERATOR}      { yylval.operatorType = strdup(yytext); return _operator; }

\n          	{ return JUMP; }
{ENDL}          { return ENDL; }

{NAME}          { yylval.varVal = strdup(yytext); return _variable; }
{COMMENT}		{ return COMMENT; }

%%

void yyerror(const char *s) {
    fprintf(stderr, "\nERROR ON LINE %d : \n %s\n", yylineno, s);
    exit(0);
}

void invalid_token(){
    printf("ERROR ON LINE %d : \n Invalid Token \"%s\"\n", yylineno, yytext);
    exit(0);
}
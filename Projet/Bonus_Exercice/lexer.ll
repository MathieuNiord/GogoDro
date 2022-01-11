%{
	/* === AUTEURS : FREJOUX Gaetan & Niord Mathieu === */

	#include <stdio.h>
    #include "parser.tab.hh"
	
	// Display error
	void extern yyerror(const char* s);
	
	// Store error
	char* error;
%}

%option yylineno

INTEGER		[0-9]
ALPHANUM	[a-zA-Z0-9]
NAME        {ALPHANUM}+
COMMENT		"//"(" "?{ALPHANUM}*)*
ENDL 		";"

%%

Couleur       	{ return SET_COLOR; }
Deplace       	{ return MOVE; }
Ecrire        	{ return LOWER; }
Lever          	{ return LIFT; }
Ligne			{ return LINE; }
Rectangle     	{ return RECT; }

entier			{ return DEC; }
pour			{ return BEGIN_FOR; }
"fin pour"		{ return END_FOR; }

"(" 			{ return LPAR; }
")" 			{ return RPAR; }
"," 			{ return VIRG; }
"<-"            { return AFFECT; }

{INTEGER}		{ yylval.intVal = atoi(yytext); return number; }

NOIR			{ return CBLACK; }
BLEU			{ return CBLUE; }
VERT			{ return CGREEN; }
ROUGE			{ return CRED; }
ROSE			{ return CPINK; }
JAUNE			{ return CYELLOW; }
VIOLET			{ return CPURPLE; }

HAUT			{ return UP; }
BAS				{ return DOWN; }
GAUCHE 			{ return LEFT; }
DROITE 			{ return RIGHT; }

"+"				{ return OPLUS; }
"-"				{ return OMINUS; }
"*"				{ return OMULT; }
"/"				{ return ODIV; }

\n          	{ return JUMP; }
{ENDL}          { return ENDL; }

{NAME}          { yylval.varVal = strdup(yytext); return variable; }
{COMMENT}		{ return COMMENT; }

.				{ ; }

%%

void yyerror(const char *s) {
    fprintf(stderr, "\nERROR ON LINE %d : \n %s\n", yylineno, s);
    exit(0);
}
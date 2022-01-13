%{
	/* === AUTEURS : FREJOUX Gaetan & Niord Mathieu === */

	#include <stdio.h>
    #include "parser.tab.hh"
	
	// Displaying the error
	void extern yyerror(const char* s);

	// For storing the error message
	char* error;
%}

%option yylineno

FLOAT		"-"?[0-9]+"."?[0-9]*
ALPHANUM	[a-zA-Z0-9]
NAME        {ALPHANUM}+(_?{ALPHANUM})*
PATH 		"/"("../")?{NAME}"/"({NAME}"/")*
COMMENT		"//"(" "?.*)*
ENDL 		";"

COLOR		("NOIR"|"BLEU"|"VERT"|"ROUGE"|"ROSE"|"VIOLET"|"JAUNE")
DIRECTION	("HAUT"|"BAS"|"GAUCHE"|"DROITE")

%%

Couleur       	{ return SET_COLOR; }
Deplacer       	{ return MOVE; }
Ecrire        	{ return LOWER; }
Lever          	{ return LIFT; }
Ligne			{ return LINE; }
Rectangle     	{ return RECT; }
Cercle			{ return CIRCLE; }
Centrer			{ return CENTER; }

nombre			{ return DEC; }
pour			{ return BEGIN_FOR; }
"fin pour"		{ return END_FOR; }

"#NOM"			{ return CONFIG_NAME; }
"#CHEMIN"		{ return CONFIG_PATH; }
"#SAUVER"		{ return CONFIG_SAVE; }
"#NOUVEAU"		{ return CONFIG_NEW; }

"(" 			{ return LPAR; }
")" 			{ return RPAR; }
"," 			{ return VIRG; }
"<-"            { return AFFECT; }

{FLOAT}			{ yylval.doubleVal = atof(yytext); return number; }
{COLOR}			{ yylval.color = strdup(yytext); return color; }
{DIRECTION}		{ yylval.direction = strdup(yytext); return direction; }

"+"				{ return OPLUS; }
"-"				{ return OMINUS; }
"*"				{ return OMULT; }
"/"				{ return ODIV; }

\n          	{ return JUMP; }
{ENDL}          { return ENDL; }

{NAME}          { yylval.varVal = strdup(yytext); return name; }
{PATH}			{ yylval.path = strdup(yytext); return path; }
{COMMENT}		{ return COMMENT; }

.				{ ; }

%%

void yyerror(const char *s) {
    fprintf(stderr, "\n[ERREUR] : %s\n\n", s);
    exit(0);
}
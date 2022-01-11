%{
	/* === AUTEUR : Gaetan FREJOUX & Mathieu Niord === */

	/* === INCLUDES === */
	#include <stdio.h>
	#include <stdbool.h>

    /* === ENUMERATION === */
    //enum color {NOIR, ROUGE, BLEU, VERT};

	/* === VARIABLES === */
	bool isWriting;
	int line;

	/* === FONCTIONS === */
	void printLine(const char* text);

%}

%option yylineno

DIGIT		[0-9]
ALPHANUM	[a-zA-Z0-9]

COLOR       ("NOIR"|"ROUGE"|"BLEU"|"VERT")
DIRECTION   "gauche"|"droite"|"haut"|"bas"
VAR         {ALPHANUM}+
OPE         [+\-/\*]

exp         {VAR}({SPACE}?{OPE}{SPACE}?{VAR})?
affect      {VAR}"<-"{exp}

move        "deplace("{DIRECTION}","{SPACE}?{DIGIT}+")"
down        "ecrire"
up          "stop"
set_color   "couleur("{COLOR}")"
rect        "rectangle("{exp}","{SPACE}?{exp}")"
ligne        "ligne("{DIRECTION}","{SPACE}?{exp}")"

dec         "nombre"{SPACE}{VAR}({SPACE}?{affect}{SPACE}?{exp})
for_beg     "pour"{SPACE}?"("{VAR}","{SPACE}?{exp}","{SPACE}?{exp}")"
for_end     "fin pour"

SPACE		[ ]{1}
END 		";"

%%

{for_beg}		{ printLine("Lancement d'une boucle for"); }
{for_end}		{ printLine("Fin de boucle"); }

{down}      	{ printLine("Crayon abbaisse"); }
{up}        	{ printLine("Crayon leve"); }
{move}			{ printLine("Deplacement"); }
{set_color}		{ printLine("Changement de couleur"); }
{rect}			{ printLine("Dessine un rectangle"); }
{ligne}			{ printLine("Dessine une ligne"); }

{dec}			{ printLine("Declaration d'une variable"); }

{END}       { ; }
\n          { line++; }
.           { ; }
<<EOF>>     { return 0; }

%%

int main(int argc, char* argv[]) {
    line = 1;
	return yylex();
}

void printLine(const char* text) {
	printf("\tligne : %3d, \t[%s]\t%s\n", line, text, yytext);
}
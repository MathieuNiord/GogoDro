%{
    #include <stdio.h>
	#include "drawer.hh"
	
    #ifndef _cplusplus
	
	extern "C" void yyerror(const char* s);
	extern "C" int yylex();
	extern "C" char* yytext;
	extern "C" int yylineno;
	
    #else
	
	extern void yyerror(const char* s);
	extern int yylex();
	extern char* yytext;
	extern int yylineno;
	
    #endif

	// Full Instruction
	Instruction* fullInstruction;
%}

%define parse.lac full
%define parse.error verbose

%code requires {
	#include "drawer.hh"
}

%union {
	int 			intVal;
	char* 			varVal;
	Instruction* 	inst;
	Expession* 		expr;
	Operator		ope;
	Color			color;
	Direction		dir;
}

%token LPAR RPAR VIRG AFFECT ENDL JUMP
%token CBLACK CBLUE CGREEN CRED CPINK CYELLOW CPURPLE
%token UP DOWN LEFT RIGHT
%token OPLUS OMINUS OMULT ODIV
%token COMMENT
%token DEC
%token MOVE LIFT LOWER SET_COLOR
%token RECT LINE
%token BEGIN_FOR END_FOR

%token <intVal> number
%token <varVal> variable

%type<inst> seq instruction affect declaration move lower lift set_color rect for_loop
%type<expr> expr
%type<color> color
%type<dir> direction
%type <ope> operator

%start prog

%%

prog: seq { fullInstruction = $1; } ;

seq: {} 
	| seq comment			{}
	| seq JUMP				{}
	| seq instruction ENDL 	{
		Sequence* seq = new Sequence($2);
		seq->add($1);
		$$ = seq;
	}
;

instruction: declaration	{ $$ = $1; }
	| affect				{ $$ = $1; }
	| move					{ $$ = $1; }
	| lower 				{ $$ = $1; }
	| lift					{ $$ = $1; }
	| set_color				{ $$ = $1; }
	| rect					{ $$ = $1; }
	| for_loop				{ $$ = $1; }
;

comment: COMMENT JUMP {} ;

color: CBLACK	{ $$ = $1; }
	| CBLUE		{ $$ = $1; }
	| CGREEN	{ $$ = $1; }
	| CRED 		{ $$ = $1; }
	| CPINK		{ $$ = $1; }
	| CYELLOW	{ $$ = $1; }
	| CPURPLE	{ $$ = $1; }
;

direction: UP	{ $$ = $1; }
	| DOWN 		{ $$ = $1; }
	| LEFT  	{ $$ = $1; }
	| RIGHT 	{ $$ = $1; }
;

operator: OPLUS { $$ = PLUS; }
	| OMINUS { $$ = MINUS; }
	| OMULT { $$ = MULT; }
	| ODIV { $$ = DIV; }
;

expr: variable					{ $$ = new Variable(yylval.varVal); }
	| number					{ $$ = new Integer(yylval.intVal); }
	| expr operator expr 		{ $$ = new Operation($1, $2, $3); }
	| LPAR expr RPAR			{ $$ = new Expression($2); }
;

affect: variable AFFECT expr { $$ = new Affect($1, $3); } ;

declaration: DEC variable	{ $$ = new Declaration($2); } ;

move: MOVE LPAR direction VIRG expr RPAR { $$ = new MovePen($3, $5); }
	| LINE LPAR direction VIRG expr RPAR { $$ = new MovePen($3, $5); }
;

lower: LOWER { $$ = new Pen(true); } ;

lift: LIFT { $$ = new Pen(false); } ;

set_color: SET_COLOR LPAR color RPAR { $$ = new SetColor($3); } ;

rect: RECT LPAR expr VIRG expr RPAR { $$ = new Rectangle($3, $5); } ;

for_loop:
  BEGIN_FOR LPAR variable VIRG expr VIRG expr RPAR ENDL seq END_FOR {
	$$ = new ForLoop($3, $5, $7, new Sequence($10));
  }
;

%%

int main(int argc, char* argv[]) {

	yyparse();

	Drawer drawer;

	if(fullInstruction)
		fullInstruction->visit(drawer);
}


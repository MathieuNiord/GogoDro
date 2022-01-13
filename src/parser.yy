%{
    #include <stdio.h>
	#include "drawer.hh"
	
/*    #ifndef _cplusplus
	
	extern "C" void yyerror(const char* s);
	extern "C" int yylex();
	extern "C" char* yytext;
	extern "C" int yylineno;
	
    #else*/
	
	extern void yyerror(const char* s);
	extern int yylex();
	extern char* yytext;
	extern int yylineno;
	
    //#endif

	Instruction* fullInstruction = nullptr;	// Full instruction
%}

%define parse.lac full
%define parse.error verbose

%code requires {
	#include "drawer.hh"
}

%union {
	double 			doubleVal;
	char*		 	varVal;
	char*			color;
	char*			direction;
	char* 			path;
	Instruction* 	inst;
	Expression* 	expression;
}

%token LPAR RPAR VIRG AFFECT ENDL JUMP
%token OPLUS OMINUS OMULT ODIV
%token CONFIG_NAME CONFIG_PATH CONFIG_SAVE CONFIG_NEW
%token COMMENT
%token DEC
%token MOVE LIFT LOWER SET_COLOR CIRCLE CENTER
%token RECT LINE
%token BEGIN_FOR END_FOR

%token <doubleVal> number
%token <varVal> name
%token <color> color
%token <direction> direction
%token <path> path

%type <inst> prog seq instruction config
%type <inst> affect declaration move lower lift set_color rect circle for_loop center
%type <expression> expr

%left OPLUS OMINUS OMULT ODIV

%start prog

%%

prog: seq { fullInstruction = new Prog($1); } ;

seq: {  $$ = nullptr; }
	| seq comment
	| seq JUMP
	| seq instruction ENDL 	{
		Sequence* seq = new Sequence($1);
		seq->add($2);
		$$ = seq;
	}
	| seq config JUMP {
		Sequence* seq = new Sequence($1);
		seq->add($2);
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
	| circle				{ $$ = $1; }
	| for_loop				{ $$ = $1; }
	| center				{ $$ = $1; }
;

comment: COMMENT JUMP {} ;

expr: name					{ $$ = new Variable($1); }
	| number				{ $$ = new Double($1); }
	| expr OPLUS expr 		{ $$ = new Operation($1, PLUS, $3); }
	| expr OMINUS expr 		{ $$ = new Operation($1, MINUS, $3); }
	| expr OMULT expr 		{ $$ = new Operation($1, MULT, $3); }
	| expr ODIV expr 		{ $$ = new Operation($1, DIV, $3); }
	| LPAR expr RPAR		{ $$ = $2; }
;

config: CONFIG_NAME name 	{ $$ = new ImgConfig(NAME, $2); }
	| CONFIG_NEW name 		{ $$ = new ImgConfig(NEW, $2); }
	| CONFIG_PATH path 		{ $$ = new ImgConfig(PATH, $2, $2); }
	| CONFIG_SAVE name		{ $$ = new ImgConfig(SAVE, $2, $2); }
	| CONFIG_NEW			{ $$ = new ImgConfig(NEW); }
	| CONFIG_SAVE			{ $$ = new ImgConfig(SAVE); }
;

center: CENTER { $$ = new Center(); } ;

affect: name AFFECT expr { $$ = new Affect($1, $3); } ;

declaration: DEC name		{ $$ = new Declaration($2); }
	| DEC name AFFECT expr 	{
		Declaration* d = new Declaration($2);
		Affect* a = new Affect($2, $4);
		Sequence* seq = new Sequence(d);
		seq->add(a);
		$$ = seq;
	}
;

move: MOVE LPAR direction VIRG expr RPAR	{ $$ = new MovePen($3, $5); }
	| LINE LPAR direction VIRG expr RPAR 	{ $$ = new MovePen($3, $5, true); }
;

lower: LOWER { $$ = new Pen(true); } ;

lift: LIFT { $$ = new Pen(false); } ;

set_color: SET_COLOR LPAR color RPAR { $$ = new SetColor($3); } ;

rect: RECT LPAR expr VIRG expr RPAR { $$ = new Rectangle($3, $5); } ;

circle: CIRCLE LPAR expr RPAR { $$ = new Circle($3); }

for_loop:
  BEGIN_FOR LPAR name VIRG expr VIRG expr RPAR ENDL seq END_FOR {
	$$ = new ForLoop($3, $5, $7, $10);
  }
;

%%
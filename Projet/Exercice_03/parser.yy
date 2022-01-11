%{
    #include <stdio.h>
	#include <stdbool.h>
	#include <string.h>
	
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
	
	int loop_count;
	char* iter[3];
	
	bool isAffectable(const char* var);
	bool sameString(const char* str1, const char* str2);
	
%}

%define parse.lac full
%define parse.error verbose

%union {
	int 	intVal;
	char* 	operatorType;
	char* 	colorVal;
	char* 	directionVal;
	char* 	varVal;
}

%token LPAR RPAR VIRG AFFECT ENDL JUMP
%token COMMENT
%token DEC
%token MOVE LIFT LOWER SET_COLOR
%token RECT LINE
%token BEGIN_FOR END_FOR

%token <intVal> 		_number
%token <colorVal> 		_color
%token <directionVal> 	_direction
%token <operatorType> 	_operator
%token <varVal> 		_variable

%start prog

%%

prog: seq {} ;

seq: {}
	| seq instruction ENDL 	{}
	| seq comment			{}
	| seq JUMP				{}
;

instruction: declaration	{}
	| affect				{}
	| move					{}
	| lower 				{}
	| lift					{}
	| set_color				{}
	| rect					{}
	| line					{}
	| for_loop				{}
;

comment: COMMENT JUMP {} ;

iterator: _variable { iter[loop_count] = strdup($1); loop_count++; } ;

expr: _variable						{ free($1); }
	  | _number						{}
      | _variable _operator expr	{}
	  | _number _operator expr 		{}
;

affect: _variable AFFECT expr { if (!isAffectable($1)) { return EXIT_FAILURE; } } ;

declaration: DEC _variable	{}
             | DEC affect 	{}
;

move: MOVE LPAR _direction VIRG expr RPAR {} ;

lower: LOWER {} ;

lift: LIFT {} ;

set_color: SET_COLOR LPAR _color RPAR {} ;

rect: RECT LPAR expr VIRG expr RPAR {} ;

line: LINE LPAR _direction VIRG expr RPAR {} ;

for_begin: BEGIN_FOR LPAR iterator VIRG expr VIRG expr RPAR ENDL {} ;

for_content: seq {} ;

for_end: END_FOR { free(iter[loop_count]); loop_count--; } ;

for_loop: for_begin for_content for_end {} ;

%%

bool sameString(const char* str1, const char* str2) {
			
	while (*str1 != '\0') {
		if (*str1 != *str2)
			return false;
		str1++;
		str2++;
	}
	
	return true;
}

bool isAffectable(const char* var) {
		
	for (int loop = 0; loop < 3; loop++)
		if (iter[loop] == NULL) break;
		else if (sameString(var, iter[loop])) {
			printf("\nErreur : Vous ne pouvez pas réaffecter une variable d'itération.\n\n");
			return false;
		}
	
	return true;
}

int main(int argc, char* argv[]) {

	loop_count = 0;

    int res = yyparse();
    printf("RES = %d\n\n", res);
    return 0;
}


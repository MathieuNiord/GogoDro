/* Auteurs : Frejoux Gaetan & Niord Mathieu */

#include "parser.tab.hh"
#include "drawer.hh"
#include "exceptions/parsing_exception.hh"

extern Instruction* fullInstruction;
extern void yyerror(const char*);

int main(int argc, char** argv) {

    yyparse();

    Drawer drawer;

    try {
        if (fullInstruction != NULL)
            fullInstruction->visit(drawer);
    }

    catch (parsing_exception pe) {
        yyerror(pe.what());
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
SRC=affect.cc  decl.cc drawer.cc  for_loop.cc  integer.cc  move.cc  ope.cc  pen.cc rect.cc set_color.cc var.cc lex.yy.c parser.tab.cc
SRCH=affect.hh decl.hh  expr.hh  for_loop.hh  inst.hh  integer.hh  move.hh  ope.hh  pen.hh  rect.hh set_color.hh term.hh var.hh
CXX=g++
FLAGS =-lX11 -lpthread -ll
OBJ=$(SRC:.cc=.o)

prog: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(FLAGS)


lex.yy.c: lexer.ll parser.tab.cc
	flex $<

parser.tab.cc: parser.yy
	bison -d $<

quadrilatere: prog
	./prog < quadrilatere

quad: prog
	@echo "\n=== QUADRILLAGE ===\n"
	@./prog < ../tests_files/quadrillage.ggd

rect: prog
	@echo "\n=== RECTANGLE ===\n"
	@./parser < ../tests_files/rectangle_croix.ggd

clean:
	rm -fr $(OBJ) *~ lex.yy.c parser.tab.cc parser.tab.hh
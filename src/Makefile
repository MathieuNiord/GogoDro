SRC = lex.yy.c parser.tab.cc prog.cc affect.cc seq.cc img_config.cc decl.cc for_loop.cc double.cc ope.cc pen.cc center.cc rect.cc circle.cc set_color.cc var.cc move_pen.cc drawer.cc main.cc
SRCH = exceptions/*.hh term.hh inst.hh expr.hh prog.hh img_config.hh double.hh var.hh affect.hh decl.hh for_loop.hh move_pen.hh center.hh ope.hh pen.hh rect.hh circle.hh set_color.hh
CXX = g++
FLAGS = -lX11 -lpthread -ll -lstdc++fs
OBJ = $(SRC:.cc=.o)

prog: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(FLAGS)

vgd: prog
	valgrind ./prog < tests_files/rectangle_croix.ggd

lex.yy.c: lexer.ll parser.tab.cc
	flex $<

parser.tab.cc: parser.yy
	bison -d $<

grid: prog
	@mkdir -p ../Results
	@echo "\n=== QUADRILLAGE ===\n"
	@./prog < ../tests_files/grid.ggd

rect: prog
	@mkdir -p ../Results
	@echo "\n=== RECTANGLE ===\n"
	@./prog < ../tests_files/rectangle_cross.ggd

android: prog
	@mkdir -p ../Results
	@echo "\n=== ANDROID ===\n"
	@./prog < ../tests_files/egg.ggd

graph.png: graph.dot
	@dot -Tpng $< > $@

graph.dot: parser.yy
	@bison -ggraph.dot parser.yy

clean:
	rm -fr $(OBJ) *~ lex.yy.c parser.tab.cc parser.tab.hh prog

help:
	@echo -e '\n\t= HELP COMMANDS ======================================================================================\n'
	@echo -e '\t- make | make prog\t:\tbuild project.\n'
	@echo -e '\t- make graph.png\t:\tCreate a .png file of the abstract syntaxic tree.\n'
	@echo -e '\t- make grid\t\t:\tLaunch the parser on "../tests_files/grid.ggd".\n\t\t\t\t\tStore the result inside the "../Results/grid_result/" folder.\n'
	@echo -e '\t- make rect\t\t:\tLaunch the parser on "../tests_files/rectangle_cross.ggd."\n\t\t\t\t\tStore the result inside the "../Results/rect_result/" folder.\n'
	@echo -e '\t- make android\t\t:\tLaunch the parser on "../tests_files/egg.ggd."\n\t\t\t\t\tStore the result inside the "../Results/others_results/" folder.\n'
	@echo -e '\t- make clean\t\t:\tClean project.\n'
	@echo -e '\n\t======================================================================================================\n\n'
default: all

parser: parser.tab.o lex.yy.o
	@gcc -o $@ $^ -lfl

parser.tab.o: parser.tab.cc
	@gcc -c $<
	
lex.yy.o: lex.yy.c
	@gcc -c $<
	
parser.tab.cc: parser.tab.hh

parser.tab.hh: parser.yy
	@bison -d $<

lex.yy.c: lexer.ll parser.tab.hh
	@flex $<
	
graph.png: graph.dot
	@dot -Tpng $< > $@

graph.dot: parser.yy
	@bison -ggraph.dot parser.yy

all: parser graph.png clean
	
clean:
	@rm lex.yy.c parser *.o *.cc *.hh
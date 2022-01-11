default: quadrillage

build:
	@flex gogodro.ll
	@gcc -o ggd lex.yy.c -lfl
	
quad: build
	@./ggd < ../tests_files/quadrillage.ggd
	
rect: build
	@./ggd < ../tests_files/rectangle_croix.ggd
	
clean: @rm lex.yy.c ggd
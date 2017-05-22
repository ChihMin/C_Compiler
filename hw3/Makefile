all:
	@byacc -d hw2.y
	@flex hw2.l
	@gcc -DDEBUG -g lex.yy.c y.tab.c code.c -o parser -lfl

debug:
	@byacc -d hw2.y
	@flex hw2.l
	@gcc -DDEBUG lex.yy.c y.tab.c code.c -o parser -lfl

clean:
	rm -f lex.yy.c debug scanner

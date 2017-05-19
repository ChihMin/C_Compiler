all:
	@byacc -d hw2.y
	@flex hw2.l
	@gcc -DDEBUG lex.yy.c y.tab.c -o parser -lfl

debug: clean
	@flex debug.l
	@gcc lex.yy.c -o debug -lfl

clean:
	rm -f lex.yy.c debug scanner

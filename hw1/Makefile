all:
	@flex scanner.l
	@gcc lex.yy.c -o scanner -lfl

debug: clean
	@flex debug.l
	@gcc lex.yy.c -o debug -lfl

clean:
	rm -f lex.yy.c debug scanner

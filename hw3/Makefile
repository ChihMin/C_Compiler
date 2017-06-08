all:
	@byacc -d hw2.y
	@flex hw2.l
	@gcc lex.yy.c y.tab.c code.c -o codegen -lfl

debug:
	@byacc -d hw2.y
	@flex hw2.l
	@gcc -DDEBUG -g lex.yy.c y.tab.c code.c -o codegen -lfl

install:
	./create.sh
	 cp Blink.s ~/DemoBlink/Demo_Blink

clean:
	rm -f lex.yy.c debug scanner

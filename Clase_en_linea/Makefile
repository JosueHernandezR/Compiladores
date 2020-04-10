c-grammar.tab.c: c-grammar.y
	bison -d c-grammar.y
lex.yy.c: c-grammar.l
	flex c-grammar.l
c-grammar.tab.o: c-grammar.tab.c
	gcc c-grammar.tab.c -c -o c-grammar.tab.o
lex.yy.o: lex.yy.c
	gcc lex.yy.c -c -o lex.yy.o
a.out: c-grammar.tab.o lex.yy.o
	gcc c-grammar.tab.o lex.yy.o -ll
run: a.out
	./a.out
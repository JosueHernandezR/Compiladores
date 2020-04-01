Practica.tab.c: Practica.y
	bison -d Practica.y
lex.yy.c: Practica.l
	flex Practica.l
Practica.tab.o: Practica.tab.c
	gcc Practica.tab.c -c
lex.yy.o: lex.yy.c
	gcc lex.yy.c -c
a.out: Practica.tab.o lex.yy.o
	gcc Practica.tab.o lex.yy.0 -ll
run: a.out
	./a.out
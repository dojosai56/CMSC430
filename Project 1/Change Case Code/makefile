case: case.o
	g++ -o case case.o

case.o: case.c
	g++ -c case.c

case.c: case.l
	flex case.l
	mv lex.yy.c case.c

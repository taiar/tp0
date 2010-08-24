run:
	./Release/tp0 -a ./bentrada/lista -b hehe -c hehehe
min:
	./Release/tp0 -a ./textos/lista -b hehe -c hehehe
read:
	./Release/tp0 -a ./bentrada/lista -b hehe -c hehehe > in
val:
	valgrind ./Release/tp0 -a ./bentrada/lista -b hehe -c hehehe
HAHA:
	gcc -o tp0 ./src/main.c ./src/io.c ./src/io.h ./src/vocabulario.c ./src/vocabulario.h ./src/util.c ./src/util.h -g -Wall
haha: HAHA
	./tp0 -a ./bentrada/lista -b hehe -c hehehe


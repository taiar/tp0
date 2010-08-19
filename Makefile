run:
	./Release/tp0 -a ./bentrada/lista -b hehe -c hehehe
read:
	./Release/tp0 -a ./bentrada/lista -b hehe -c hehehe > in
val:
	valgrind ./Release/tp0 -a ./bentrada/lista -b hehe -c hehehe

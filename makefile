test	:	algorithm.o test.o
	g++ -o test algorithm.o test.o

algorithm.o	:	algorithm.cpp algorithm.h
	g++ -c algorithm.cpp -o algorithm.o

test.o	:	test.cpp algorithm.h
	g++ -c test.cpp -o test.o
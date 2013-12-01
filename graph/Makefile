test : test.o graph.o
	cc -g -Wall -o test test.o graph.o

test.o : graph.h

graph.o : graph.h

.PHONY : clean
clean :
	-rm test.o graph.o test

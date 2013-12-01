test : sorter.o test.o
	cc -g -o test sorter.o test.o -lm

test.o : sorter.h
	cc -g -c test.c

sorter.o : sorter.h
	cc -g -c sorter.c

clean :
	rm test test.o sorter.o

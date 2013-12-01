VPATH = include

list_test : list.o list_test.o
	cc -L./lib -o list_test list.o list_test.o -lhashmap

list.o : list.h hashmap.h
	cc -L./lib -Wall -c list.c -lhashmap

list_test.o : list.h

clean :
	rm list_test list.o list_test.o

bst_test : bst.o bst_test.o
	cc -g -o bst_test bst.o bst_test.o

bst.o : bst.h
	cc -g -c bst.c

bst_test.o : bst.h
	cc -g -c bst_test.c

clean:
	rm bst_test bst.o bst_test.o

libhashmap.so : hashmap.o
	cc -shared -o libhashmap.so hashmap.o

hashmap.o : hashmap.h
	cc -c -Wall -Werror -fpic hashmap.c

.PHONY : clean
clean :
	-rm hashmap.o libhashmap.so


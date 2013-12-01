objects = queue_test.o priority_queue.o

queue_test : $(objects)
	cc -g -o queue_test $(objects)

$(objects) : priority_queue.h

.PHONY : clean
clean :
	-rm priority_queue.o queue_test

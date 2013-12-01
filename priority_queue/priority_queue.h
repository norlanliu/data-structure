#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

typedef int item_type;

typedef struct priority_queue
{
	item_type *item;
	int length;
	int capability;
}priority_queue;

extern priority_queue *initialize_queue(int length);

extern void enqueue(priority_queue * queue,const item_type item);

extern item_type dequeue();

extern int size();

extern void free_queue(priority_queue *queue);
#endif

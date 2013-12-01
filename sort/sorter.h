#ifndef DATASTRUCT_SORT_H_
#define DATASTRUCT_SORT_H_
#define BUCKET_SIZE 128

extern void counterSorting(unsigned *org, unsigned * des, int length, int order);

extern void bucketSorting(unsigned *org, unsigned *des, int length);

extern void radixSorting(unsigned *org, int length);

extern void bitSorting(unsigned *org, int length);

extern void HeapSorting(int *org, int length);

typedef struct _list
{
	int item;
	struct _list * next;
}list_t;
#endif

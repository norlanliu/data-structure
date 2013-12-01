#ifndef DATASTRUCT_LIST_H__
#define DATASTRUCT_LIST_H__
typedef int item_type;
typedef struct _list{
	item_type item;
	struct _list * next;
}list;

void insert(list *l, item_type item);
list *findItem(list *l, item_type item);
list *findPredecessor(list *l, item_type x);
void deleteItem(list *l, item_type x);
void freeList(list *l);
void printList(list *l);
/*
 * reverse the list through three list pointer
 */
extern void reverseList(list *l);
/*
 * remove the duplicate item of the list
 */
extern void remove_duplication(list *l);

#endif

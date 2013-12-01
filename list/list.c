#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "include/hashmap.h"

void insert(list *l, item_type item)
{
	if(l == NULL)
		return;
	list * newItem = (list *)malloc(sizeof(list));
	newItem->item = item;
	newItem->next = l->next;
	l->next = newItem;
}
list *findItem(list *l, item_type item)
{
	if(l == NULL)
		return NULL;
	list *p = l;
	while(p != NULL)
	{
		if(p->item == item)
			return p;
		else
			p = p->next;
	}
	return NULL;
}
list *findPredecessor(list *l, item_type x)
{
	if(l == NULL)
		return NULL;
	list * p = l;
	while(p->next != NULL)
	{
		if(p->next->item == x)
			return p;
		else 
			p = p->next;
	}
	return NULL;
}
void deleteItem(list *l, item_type x)
{
	if(l == NULL)
		return;
	list *p = findPredecessor(l,x);
	if(p != NULL)
	{
		list *old = p->next;
		p->next = old->next;
		free(old);
		old = NULL;
	}
}
void freeList(list *l)
{
	if(l != NULL)
	{
		list *temp = NULL;
		while(l->next != NULL)
		{
			temp = l->next;
			l->next = temp->next;
			free(temp);
			temp = NULL;
		}
	}
}
void printList(list *l)
{
	if(l ==  NULL || l->next == NULL)
		return;
	
	printf("%d\n", l->next->item);
	printList(l->next);
}
void reverseList(list *l)
{
	if(l == NULL)
		return;
	list *p1 = l->next;
	list *p2 = p1->next;
	p1->next = NULL;
	list *pTemp = p2;
	while(pTemp != NULL)
	{
		pTemp = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = pTemp;
	}
	l->next = p1;
}
static int hashCode(item_type item)
{
	return 31 + item;
}
void remove_duplication(list *l)
{
	clock_t start = clock();
	hashmap_t *map = hashmap_initialize(13, &hashCode);
	while(l->next != NULL)
	{
		if(hashmap_put(map, l->next->item, 0) < 0 )
			deleteItem(l, l->next->item);
		else
			l = l->next;
	}
	clock_t end = clock();
	printf("Total time taken by CPU is %f\n", (double)(end-start)/CLOCKS_PER_SEC);
}

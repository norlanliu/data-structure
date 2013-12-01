#ifndef TEMPLATE_LIST_
#define TEMPLATE_LIST_

#define LIST_DEF(LIST, TYPE)				\
	typedef struct _LIST					\
{											\
	TYPE item;								\
	struct _LIST * next;					\
}LIST;										\
											\
void LIST##_insert(LIST *l, TYPE item);		\
											\
LIST *LIST##_find(LIST *l, TYPE item);		\
											\
LIST *LIST##_findPredecessor(LIST *l, TYPE item);\
											\
void LIST##_delete(LIST *l, TYPE item);	\
											\
void LIST##_free(LIST *l);					\
											\
void LIST##_print(LIST *l);					\
											\
void LIST##_reverse(LIST *l);				\

#define LIST_IMPL_(LIST, TYPE, ALLOC, FREE, PRINTF)	\
	void LIST##_insert(LIST *l, TYPE item)			\
{													\
	if(l == NULL)									\
		return;										\
	LIST * newItem = (LIST *)ALLOC(sizeof(LIST));	\
	newItem->item = item;							\
	newItem->next = l->next;						\
	l->next = newItem;								\
}													\
													\
LIST *LIST##_find(LIST *l, TYPE item)				\
{													\
	if(l == NULL)									\
		return NULL;								\
	LIST *p = l;									\
	while(p != NULL)								\
	{												\
		if(p->item == item)							\
			return p;								\
		else										\
			p = p->next;							\
	}												\
	return NULL;									\
}													\
													\
LIST *LIST##_findPredecessor(LIST *l, TYPE x)		\
{													\
	if(l == NULL)									\
		return NULL;								\
	LIST * p = l;									\
	while(p->next != NULL)							\
	{												\
		if(p->next->item == x)						\
			return p;								\
		else										\
			p = p->next;							\
	}												\
	return NULL;									\
}													\
void LIST##_delete(LIST *l, TYPE x)						\
{													\
	if(l == NULL)									\
		return;								\
	LIST *p = LIST##_findPredecessor(l,x);					\
	if(p != NULL)									\
	{												\
		LIST *old = p->next;						\
		p->next = old->next;						\
		FREE(old);									\
	}												\
}													\
void LIST##_free(LIST *l)							\
{													\
	if(l != NULL)									\
	{												\
		LIST *temp = NULL;							\
		while(l->next != NULL)						\
		{											\
			temp = l->next;							\
			l->next = temp->next;					\
			FREE(temp);								\
		}											\
	}												\
}													\
void LIST##_print(LIST *l)							\
{													\
	if(l ==  NULL || l->next == NULL)				\
		return;										\
													\
	PRINTF("%d\n", l->next->item);					\
	LIST##_print(l->next);							\
}													\
void LIST##_reverse(LIST *l)						\
{													\
	if(l == NULL)									\
		return;										\
	LIST *p1 = l->next;								\
	LIST *p2 = p1->next;							\
	p1->next = NULL;								\
	LIST *pTemp = p2;								\
	while(pTemp != NULL)							\
	{												\
		pTemp = p2->next;							\
		p2->next = p1;								\
		p1 = p2;									\
		p2 = pTemp;									\
	}												\
	l->next = p1;									\
}													\

#define LIST_IMPL(LIST, TYPE)						\
	LIST_IMPL_(LIST, TYPE, malloc, free, printf)	\


#endif

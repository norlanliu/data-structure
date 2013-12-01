#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
	list *nullList = NULL;
	insert(nullList, 0);

	list *header = (list *)malloc(sizeof(list));
	header->next = NULL;
	int i;
	for(i = 0; i < 10; i++)
	{
		insert(header, i);
		insert(header, i);
	}
	printf("insert 0 - 9 into the list\n");
	printList(header);
	reverseList(header);
	printf("after reverse the list\n");
	printList(header);
	remove_duplication(header);
	printf("after remove the duplicate item\n");
	printList(header);
	freeList(header);
	free(header);
	return 0;
}

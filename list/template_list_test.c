#include <stdio.h>
#include <stdlib.h>

#include "template_list.h"

LIST_DEF(int_list, int);

LIST_IMPL(int_list, int);

int main()
{
	int_list *header = (int_list *)malloc(sizeof(int_list));
	header->next = NULL;
	int i;
	for(i = 0; i < 10; i++)
		int_list_insert(header, i);
	int_list * answer = int_list_find(header, 2);
	printf("%d\n", answer->item);
	int_list_delete(header, 2);
	int_list_print(header);

	int_list_reverse(header);
	int_list_print(header);
	int_list_free(header);
	free(header);
	return 0;
}

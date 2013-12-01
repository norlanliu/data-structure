#include <stdio.h>
#include <stdlib.h>
#include "sorter.h"

int main()
{
	int *temp = (int *)malloc(200 * sizeof(int));
	int *des = (int *)malloc(200 * sizeof(int));
	int i;
	for(i = 0; i < 200; i++)
		temp[i] = i%100;
	//counterSorting(temp, des, 200, 1);
	//bucketSorting(temp, des, 200);
	//radixSorting(temp, 200);
	//bitSorting(temp,200);
	HeapSorting(temp, 200);
	for(i = 0; i < 200; i++)
		printf("%d\t", temp[i]);
	printf("\n");
	return 0;
}

#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * counter sorting
 * org : the array to sort.
 * count : the size of the array(org).
 * order : the order after sorting, 0 for INC, the other for DES
 *
 **/
void counterSorting(unsigned *org, unsigned *des, int count, int order)
{
	if(org == NULL || count == 0)
		return;
	int max = 0;
	int i;
	for(i = 0; i < count; i++)
		if(org[i] > max)
			max = org[i];
	max += 1;
	int *bucket = (int *)malloc(max * sizeof(int));
	memset(bucket, 0, sizeof(int)*max);
	for(i = 0; i < count; i++)
		bucket[org[i]]++;

	if(order == 0)
		for(i = 1; i < max; i++)
			bucket[i] += bucket[i-1];
	else
		for(i = max-2; i >= 0; i--)
			bucket[i] += bucket[i+1];

	for(i = count-1; i >= 0; i--)
	{
		des[bucket[org[i]]-1] = org[i];
		bucket[org[i]] -= 1;
	}
}
inline void insertSorting(int *array, int start, int length)
{
	int i,j,temp,end=start+length;
	for(i = start+1; i < end; i++)
	{
		temp = array[i];
		j = i-1;
		while(j >= start && array[j] > temp)
		{
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = temp;
	}
}
void bucketSorting(unsigned *org, unsigned *des, int length)
{
	int max = 0;
	int i,j, k = 0;

	for(i = 0; i<length; i++)
		if(org[i] > max)
			max = org[i];
	if(max <= 0)
		return;
	unsigned m = max / BUCKET_SIZE + 1;
	list_t **buckets = (list_t **)malloc(BUCKET_SIZE * sizeof(list_t *));
	memset(buckets, 0, BUCKET_SIZE*sizeof(list_t*));
	list_t *temp, *temp2;
	for(i = 0; i < length; i++)
	{
		k = org[i] / m;
		temp = (list_t *)malloc(sizeof(list_t));
		temp->item = org[i];
		temp->next = buckets[k];
		buckets[k] = temp;
	}
	for(i=j=0; i<BUCKET_SIZE; i++)
	{
		temp = buckets[i];
		while(temp != NULL)
		{
			des[j++] = temp->item;
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
	}
	free(buckets);
	insertSorting(des, 0, length);

}
void radixSorting(unsigned *org, int length)
{
	int max = 0;
	int i,j, k = 0, bucket_size = 10,exp = 1;

	for(i = 0; i<length; i++)
		if(org[i] > max)
			max = org[i];
	if(max <= 0)
		return;
	list_t **buckets = (list_t **)malloc(bucket_size * sizeof(list_t *));
	memset(buckets, 0, bucket_size* sizeof(list_t*));
	list_t *temp, *temp2;
	while(max / exp != 0)
	{
		for(i = 0; i < length; i++)
		{
			k = (org[i] / exp) % bucket_size;
			temp = (list_t *)malloc(sizeof(list_t));
			temp->item = org[i];
			temp->next = buckets[k];
			buckets[k] = temp;
		}
		for(i=j=0; i<bucket_size; i++)
		{
			
			temp = buckets[i];
			while(temp != NULL)
			{
				temp = temp->next;
				j++;
			}
			k = 0;
			temp = buckets[i];
			while(temp != NULL)
			{
				org[j-k-1] = temp->item;
				temp2 = temp;
				temp = temp->next;
				free(temp2);
				k++;
			}
			buckets[i] = NULL;
		}
		exp *= 10;
	}
	free(buckets);
}
void bitSorting(unsigned *org, int length)
{
	int i,j;
	for(i = 31; i >= 1; i--)
	{
		int preCB = org[0] >> i;
		int theS = 0;
		int theI = theS - 1;
		int theBase = 1 << (i-1);
		int theAxBit = 0;

		for(j = 0; j < length; j++)
		{
			int temPreCB = org[j]>>i;
			if(temPreCB != preCB)
			{
				theS = j;
				theI = theS - 1;
				theAxBit = 0;
				preCB = temPreCB;
				j--;
				continue;
			}
			int theAJ = (org[j] & theBase) > 0 ? 1:0;
			if(theI < theS)
			{
				if(theAJ == 0)
					continue;
				theI = j;
				continue;
			}
			if(theAJ <= theAxBit)
			{
				int temp = org[j];
				org[j] = org[theI];
				org[theI]=temp;
				theI++;
			}
		}
	}
}
//percolate down the heap
//length is the max index of the array.
static void PerDown(int *array, int size, int hole)
{
	int temp = array[hole];
	int child;
	for(; (2 * hole + 1) < size; hole = child)
	{
		child = 2 * hole + 1;
		if(child != size-1 && array[child] < array[child+1])
			++child;
		if(array[child] < temp)
			break;
		else
			array[hole] = array[child];
	}
	array[hole] = temp;
}
//build the heap
//size is the length of the array
static void BuildHeap(int *array, int size)
{
	int i = (size-2) / 2;
	for(; i >= 0; --i)
		PerDown(array, size, i);
}
inline void Swap(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}
//heap sorting
void HeapSorting(int *org, int length)
{
	BuildHeap(org, length);
	int i;
	for(i = length-1; i > 0; --i)
	{
		Swap(&org[0], &org[i]);
		PerDown(org, i, 0);
	}
}

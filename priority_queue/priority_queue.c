/*
 * =====================================================================================
 *
 *       Filename:  priority_queue.c
 *
 *    Description:  priority queue
 *
 *        Version:  1.0
 *        Created:  09/15/2013 08:13:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (Qi Liu), liuqi.edward@gmail.com
 *   Organization:  antq.com
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "priority_queue.h"

static float threshold = 0.75;

priority_queue *initialize_queue(int length)
{
	priority_queue *answer = (priority_queue *)malloc(sizeof(priority_queue));
	answer->item = (item_type *)malloc(sizeof(item_type) * (length + 1));
	answer->capability = length;
	answer->length = 0;
	return answer;
}

void enqueue(priority_queue *queue, item_type item)
{
	if(queue->length < (queue->capability * threshold) )
	{
		queue->capability *= 2;
		item_type *new_item = (item_type *)malloc(queue->capability * sizeof(item_type));
		int i;
		for(i = 1; i <= queue->length; i++)
			new_item[i] = queue->item[i];
		item_type *temp = queue->item;
		queue->item = new_item;
		free(temp);
		temp = NULL;
		new_item = NULL;
	}
	queue->length += 1;
	int i = queue->length;
	for(; i > 1 && queue->item[i/2] > item; i = i/2)
		queue->item[i] = queue->item[i/2];
	queue->item[i] = item;

}
static void percolate_down(priority_queue *queue, int hole)
{
	item_type temp = queue->item[hole];
	int child;
	int length = queue->length / 2;
	for(; hole <= length; hole = child)
	{
		child = 2 * hole;
		if(queue->item[child] > queue->item[child+1])
			child++;
		if(queue->item[child] < temp)
			queue->item[hole] = queue->item[child];
		else
			break;
	}
	queue->item[hole] = temp;
}
/* *
 * dequeue the min item!
 * */
item_type dequeue(priority_queue *queue)
{
	if(queue->length == 0)
		return -1;
	int answer = queue->item[1];
	queue->item[1] = queue->item[queue->length--];
	percolate_down(queue, 1);
	return answer;
}

void free_queue(priority_queue *queue)
{
	free(queue->item);
	free(queue);
	queue = NULL;
}

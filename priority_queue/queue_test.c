/*
 * =====================================================================================
 *
 *       Filename:  queue_test.c
 *
 *    Description:  test priority queue
 *
 *        Version:  1.0
 *        Created:  09/16/2013 05:03:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (Qi Liu), liuqi.edward@gmail.com
 *   Organization:  antq.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "priority_queue.h"
#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	priority_queue *queue = initialize_queue(100);
	int i;
	for(i = 20; i >= 0; i--)
		enqueue(queue, i);
	for(i = 0; i < 21; i++)
		printf("%d\n", dequeue(queue));
	free_queue(queue);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

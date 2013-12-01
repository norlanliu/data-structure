/*
 * =====================================================================================
 *
 *       Filename:  hashmap_test.c
 *
 *    Description:  hashmap test
 *
 *        Version:  1.0
 *        Created:  08/27/2013 07:44:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Antq (Qi Liu), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "hashmap.h"
int hashCode(int num )
{
	return 31 + num;
}
int main()
{
	hashmap_t *table= hashmap_initialize(20, &hashCode);
	int i;
	for(i = 0; i < 200; i++)
		hashmap_put(table, i, i);
	printf("contains : %d\n", hashmap_contains(table,10, 10));

	for(i = 0 ; i < 200; i++)
		printf("key : %d, value : %d\n",i, hashmap_get(table, i));
	hashmap_free(table);
	return 0;
}

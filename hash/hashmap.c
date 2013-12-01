/*
 * =====================================================================================
 *
 *       Filename:  hashmap.c
 *
 *    Description:  the hashmap datastructure
 *
 *        Version:  1.0
 *        Created:  08/27/2013 03:57:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Antq (lq), 
 *   Organization:  ant
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "hashmap.h"


//default capability of hashmap
static const int DEFAULT_TABLE_CAPABILITY = 16;
//max capability
static const int MAX_CAPABILITY = 1<<30;
//the load factor
static const float DEFAULT_LOAD_FACTOR = 0.75;
/* 
 * get the base of hash
 * */
static int getHashBase()
{
	int distance = sizeof(int)*8-15;
	int hash_base = 0;
	int data[2] = {time(NULL), rand() >> 16};
	int i;
	for(i = 0; i < 2; i++)
	{
		data[i] *= 0xcc9e2d51;
		data[i] = (data[i]>>15) | (data[i]<<distance);
		data[i] *= 0x1b873593;
		hash_base ^= data[i];
		hash_base = (hash_base >> 15) | (hash_base << distance);
		hash_base = hash_base * 5 + 0xe6546b64;
	}

	hash_base ^= hash_base >> 16;
	hash_base *= 0x85ebca6b;
	hash_base ^= hash_base >> 13;
	hash_base *= 0xc2b2ae35;
	hash_base ^= hash_base >> 16;
	return hash_base;
}
/* *
 * get the hash number
 * */
static int hash(int hash_code, int hash_base)
{
	int answer = hash_base;
	answer ^= hash_code;
	answer ^= (answer >> 20) ^ (answer >> 12);
	answer ^= (answer >> 7) ^ (answer >> 4);
	return answer;
}
/* *
 * the index of the table
 * */
static int indexForTable(int hash, int capability)
{
	return hash & (capability-1);
}
static void resize(hashmap_t *map, int new_capability)
{
	if(map->table_capability >= MAX_CAPABILITY)
	{
		map->threshold = map->table_capability;
	}
	hashmap_list_t **new_table = (hashmap_list_t **)malloc(sizeof(hashmap_list_t *) * new_capability);
	memset(new_table, 0, sizeof(hashmap_list_t *)*new_capability);
	int i, index;
	hashmap_list_t *temp, *temp_while;
	for(i = 0; i < map->table_capability; i++)
	{
		temp = map->table[i];
		temp_while = map->table[i];
		while(temp_while != NULL)
		{
			index = indexForTable(temp->hash, new_capability);
			temp_while = temp->next;
			temp->next = new_table[index];
			new_table[index] = temp;
			temp = temp_while;
		}
	}
	temp = temp_while = NULL;
	free(map->table);
	map->table = new_table;
	map->table_capability = new_capability;
	map->threshold = new_capability * DEFAULT_LOAD_FACTOR;
}
/* *
 * initialize a hashmap with the specified capability.
 * */
hashmap_t *hashmap_initialize(int org_capability, int (*hashCode)(int))
{
	int capability = 1;
	if(org_capability < 0)
		return NULL;
	else if( org_capability > MAX_CAPABILITY)
		capability = MAX_CAPABILITY;
	else
		while(capability < org_capability )
			capability <<= 1;
	hashmap_t *answer = (hashmap_t *)malloc(sizeof(hashmap_t));
	answer->hash_base = getHashBase();
	answer->table = (hashmap_list_t **)malloc(sizeof(hashmap_list_t *) * capability);
	memset(answer->table, 0, sizeof(hashmap_list_t *) * capability);
	answer->hash_code = hashCode;
	answer->table_capability = capability;
	answer->threshold = (int)(capability * DEFAULT_LOAD_FACTOR);
	answer->size = 0;
	return answer;
}
/* *
 * initialize a hashmap with the default capability
 * */
hashmap_t *hashmap_initialize_default(int (*hashCode)(int))
{
	hashmap_t *answer = (hashmap_t *)malloc(sizeof(hashmap_t));
	answer->hash_base = getHashBase();
	answer->hash_code = hashCode;
	answer->table_capability = DEFAULT_TABLE_CAPABILITY;
	answer->threshold = (int)(DEFAULT_LOAD_FACTOR * DEFAULT_TABLE_CAPABILITY);
	answer->table = (hashmap_list_t **)malloc(sizeof(hashmap_list_t *) * DEFAULT_TABLE_CAPABILITY);
	memset(answer->table, 0, sizeof(hashmap_list_t *) * DEFAULT_TABLE_CAPABILITY);
	answer->size = 0;
	return answer;
}

int hashmap_put(hashmap_t *map, int key, int value)
{
	if(map == NULL || map->table == NULL)
		return -2;
	if(map->size >= (map->threshold-1))
		resize(map, 2*map->table_capability);
		
	int hash_num = hash((*(map->hash_code))(key), map->hash_base);
	int index = indexForTable(hash_num, map->table_capability);
	
	printf("key : %d, index : %d\n", key, index);
	if(map->table[index] != NULL)
	{
		hashmap_list_t *temp;
		for(temp = map->table[index]; temp != NULL; temp = temp->next)
		{
			if(temp->hash == hash_num && temp->key == key)
			{
				temp->value = value;
				return -1;
			}
		}
	}
	hashmap_list_t * newNode = (hashmap_list_t *)malloc(sizeof(hashmap_list_t));
	newNode->hash = hash_num;
	newNode->key = key;
	newNode->value = value;
	newNode->next = map->table[index];
	map->table[index] = newNode;
	map->size++;
	return index;
}

/*
 * judge whether the key and value in the hashmap
 * @return 0 for containing it, !0 for not containing it.
 */
int hashmap_contains(hashmap_t *map, int key, int value)
{
	if(map == NULL || map->table == NULL)
		return -1;
	int hash_num = hash((*(map->hash_code))(key), map->hash_base);
	int index = indexForTable(hash_num, map->table_capability);
	hashmap_list_t *temp;
	for(temp = map->table[index]; temp != NULL; temp = temp->next)
		if(temp->hash == hash_num && temp->key == key && temp->value == value)
			return 0;
	return 1;
}

void hashmap_remove(hashmap_t *map, int key)
{
	if(map == NULL || map->table == NULL)
		return;
	int hash_num = hash((*(map->hash_code))(key), map->hash_base);
	int index = indexForTable(hash_num, map->table_capability);
	hashmap_list_t *temp = map->table[index], *prev = map->table[index];
	if(temp != NULL && temp->hash == hash_num && temp->key == key)
	{
		map->table[index] = temp->next;
		free(temp);
	}
	else
	{
		for(temp = map->table[index]->next; temp != NULL; temp = temp->next)
		{
			if(temp->hash == hash_num && temp->key == key)
			{
				prev->next = temp->next;
				free(temp);
				break;
			}
			prev = prev->next;
		}
	}
}
int hashmap_get(hashmap_t *map, int key)
{
	if(map == NULL || map->table == NULL)
		return -1;
	int hash_num = hash((*(map->hash_code))(key), map->hash_base);
	int index = indexForTable(hash_num, map->table_capability);
	if(map->table[index] != NULL)
	{
		hashmap_list_t *temp;
		for(temp = map->table[index]; temp != NULL; temp = temp->next)
			if(temp->hash == hash_num && temp->key == key)
				return temp->value;
	}
	return -1;
}
/* *
 * free the hashmap
 * */
void hashmap_free(hashmap_t *map)
{
	if(map == NULL || map->table == NULL)
		return;
	int i;
	hashmap_list_t *temp1, *temp2;
	for(i = 0; i < map->table_capability; i++)
	{
		temp1 = map->table[i];
		temp2 = temp1;
		while(temp2 != NULL)
		{
			temp2 = temp2->next;
			free(temp1);
			temp1 = temp2;
		}
		map->table[i] = NULL;
	}
	free(map);
	map = NULL;
}

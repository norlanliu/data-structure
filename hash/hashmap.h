#ifndef DATASTRACTURE_HASHMAP_H_
#define DATASTRACTURE_HASHMAP_H_
//hehe
typedef struct _linked_list
{
	int hash;
	int key;
	int value;
	struct _linked_list *next;
}hashmap_list_t;

/* *
 * ths hashmap structure
 * */
typedef struct _hashmap
{
	//the number of k-v pairs
	int size;
	//the thresh to resize
	int threshold;
	//the base number of hash
	int hash_base;
	//the real capability of hashmap
	int table_capability;
	//hash code function pointer
	int (*hash_code)(int);
	//the table which contains data
	hashmap_list_t ** table;
}hashmap_t;

extern hashmap_t *hashmap_initialize(int capability, int (*hashcode)(int));

extern hashmap_t *hashmap_initialize_default(int (*hashcode)(int));

extern int hashmap_put(hashmap_t *map, int key, int value);
/* *
 * get the value whose key is @key
 * */
extern int hashmap_get(hashmap_t *map, int key);
/* *
 * judge whether the key and value in the hashmap
 * */
extern int hashmap_contains(hashmap_t *map, int key, int value);

extern void hashmap_remove(hashmap_t *map, int key);

extern void hashmap_free(hashmap_t *map);
#endif

/******************************************************************************
 * Filename: htable.c
 * Description:
 *
 * Version: 1.0
 * Created: Nov 13 2009 10:48:45
 * Last modified: Nov 13 2009 10:48:45
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "htable.h"
#include "macro.h"
#include "strhash.h"


/* Convenient function for string hashes */
htable_t *htable_init( int initial_size ) {
	return htable_init_f( initial_size, 
					(int (*)(void *, void *)) &strcmp, 
					(unsigned int (*)(void *)) &strhash );
}

/* This function requires initial size or zero for default */
htable_t *htable_init_f(int initial_size, 
					    int (*cmpfunc)(void* d1, void *d2), 
					    unsigned int (*hashfunc)(void *data) 				) 
{
	/* Create empty table */
	htable_t *table = malloc(sizeof(htable_t));
	CHECK_PTR(table, return NULL)
	table->size = 0;

	/* Resize table to requested size */
	int ret = htable_resize(table, (initial_size > 0) ? initial_size : HTABLE_DEFAULT_SIZE);
	if (!ret) { /* Reinit failed! */
		free(table);
		return NULL;
	}

	return table;
}

int htable_resize(htable_t *table, int new_size ) {
	int *oldkeys = table->keys;
	struct htable_item *olddata = table->data;
	int oldsize = table->size;

	/* Allocate new table */
	table->size = (new_size > 0) ? new_size : HTABLE_DEFAULT_SIZE;
	
	table->keys = malloc(sizeof(int) * table->size);
	CHECK_PTR(table->keys, return 0)

	table->data = malloc(sizeof(struct htable_item) * table->size);
	CHECK_PTR(table->data, return 0)
	
	/* Init free space */
	table->first_free = 0;
	for (int i = 1; i < table->size; i++) {
		table->data[i-1].next = i;
	}
	table->data[table->size-1].next = -1;

	/* Init table */
	for (int i = 0; i < table->size; i++) {
		table->keys[i] = -1;
	}

	/* Rehash old items */
	for (int i = 0; i < oldsize; i++) {
		int item = oldkeys[i];
		while (item != -1)
			htable_insert( table, olddata[item].key, olddata[item].data );
	}

	/* Free old arrays */
	free(oldkeys);
	free(olddata);

	return 1;
}

inline int htable_hash( htable_t *table, void *key ) {
	return table->hashfunc(key) % table->size;
}

void *htable_search(htable_t *table, void *key) {
	int hash = htable_hash( table, key );	
	int curr = table->keys[hash];
	while (curr != -1) {
		if (table->cmpfunc(table->data[curr].key, key) == 0)
			return table->data[curr].data;	/* That's it, return value */
	}
	
	/* Not found */
	return NULL;
}

int htable_insert(htable_t *table, void *key, void *data) {
	int hash = htable_hash( table, key );
	int prev = table->keys[hash];
	table->keys[hash] = hash;
	table->data[hash].next = prev;
	return 1;
}

int htable_remove(htable_t *table, void *key) {
	int hash = htable_hash( table, key );	
	int prev = -1;
	int curr = table->keys[hash];
	while (curr != -1) {
		if (table->cmpfunc(table->data[curr].key, key) == 0) {
			if (prev == -1) {
				/* First item in list */
				table->keys[hash] = table->data[curr].next;
			} else {
				/* Middle or end of list */
				table->data[prev].next = table->data[curr].next;
			}
			
			/* Reclaim item back to free-items list */
			htable_reclaim(table, curr);

			/* Done! */
			return 1;
		}

		prev = curr;
		curr = table->data[curr].next;
	}

	return 0;
	
}

/* Get index of next free space and mark it used */
inline int htable_alloc(htable_t *table) {
	int item = table->first_free;
	if (item == -1) {
		/* Ugh, must bloat the table */
	}
	table->first_free = table->data[item].next;
	table->data[item].next = -1;
	return item;
}

inline int htable_reclaim(htable_t *table, int item) {
	int next = table->first_free;
	table->first_free = item;
	table->data[item].next = next;
	return 1;
}

/* Frees htable structure */
int htable_destroy(htable_t *table) {
	free(table->keys);
	free(table->data);
	free(table);
	return 0;
}

// vim:sw=4:ts=4

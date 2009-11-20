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
#include <config.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "htable.h"
#include "macro.h"
#include "strhash.h"
#include "debug.h"


/* Convenient function for string hashes */
htable_t *htable_init( int initial_size ) {
	return htable_init_f( initial_size, 
					(int (*)(void *, void *)) &strcmp, 
					(unsigned long (*)(void *)) &strhash,
					NULL );
}

/* This function requires initial size or zero for default */
htable_t *htable_init_f(int initial_size, 
					    int (*cmpfunc)(void* d1, void *d2), 
					    unsigned long (*hashfunc)(void *data),
						void (*func_destruct)(void *key, void *data)	) 
{
	/* Create empty table */
	htable_t *table = malloc(sizeof(htable_t));
	CHECK_PTR(table, return NULL)
	table->size = 0;
	table->hashfunc = hashfunc;
	table->cmpfunc = cmpfunc;
	table->func_destruct = func_destruct;
	table->used = 0;

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
	if (table->size < table->used) 
		table->size = table->used; /* Force minimal size */
	
	debugf("Resizing table: %i -> %i.", oldsize, table->size);
	
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
	table->used = 0;
	for (int i = 0; i < oldsize; i++) {
		int item = oldkeys[i];
		while (item != -1) {
			htable_insert( table, olddata[item].key, olddata[item].data );
			item = olddata[item].next;
		}
	}

	/* Free old arrays */
	if (oldsize > 0) {
		free(oldkeys);
		free(olddata);
	}

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
		curr = table->data[curr].next;
	}
	
	/* Not found */
	return NULL;
}

int htable_insert(htable_t *table, void *key, void *data) {
	assert(table);

	/* Get place for item */
	int new = htable_alloc( table );
	/* Compute hash */
	int hash = htable_hash( table, key );
	
	/* Fill item and place it into correct box. */
	int prev = table->keys[hash];
	table->keys[hash] = new;
	table->data[new].next = prev;
	table->data[new].key = key;
	table->data[new].data = data;
	return 1;
}

int htable_remove(htable_t *table, void *key) {
	assert(table);
	
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

			/* Free data if destruct function is set */
			if (table->func_destruct != NULL)
				table->func_destruct( table->data[curr].key, table->data[curr].data );
			
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

/* Get index of next free space and mark it used. Be warned that poiters
 * to elements in table and indexes MAY change during this function call.*/
inline int htable_alloc(htable_t *table) {
	assert(table);

	if (table->used > table->size*0.75) {
		/* No free space, bloat table */
		htable_resize( table, table->size*2 );
	}
	int item = table->first_free;
	table->first_free = table->data[item].next;
	table->data[item].next = -1;

	table->used++;

	return item;
}

inline int htable_reclaim(htable_t *table, int item) {
	int next = table->first_free;
	table->first_free = item;
	table->data[item].next = next;
	table->used--;
	return 1;
}

/* Frees htable structure */
void htable_destroy(htable_t *table) {
	if (table->func_destruct != NULL) 
		htable_forall( table, table->func_destruct );

	free(table->keys);
	free(table->data);
	free(table);
	return;
}

void htable_forall( htable_t *table, void (*func)(void *key, void *data)) {
	for (int i = 0; i < table->size; i++) {
		int key = table->keys[i];
		while (key != -1) {
			func(table->data[key].key, table->data[key].data);		
			key = table->data[key].next;
		}
	}

	return;
}

#ifdef DEBUG
/* Print key assuming it's string. DON'T CALL IT IF IT'S NOT! */
int htable_debug_print_key_and_count( htable_t *table, int key ) {
	int count = 0;
	if (key != -1)
		fprintf(stderr, "Printing hashtable key %i:\n", key);
	while (key != -1) {
		fprintf(stderr, " ** '%s'\n", (char*) table->data[key].data);
		key = table->data[key].next;
		count++;
	}

	return count;
}

/* Print table */
void htable_debug_print( htable_t *table ) {
	int boxes_filled = 0;
	int boxes_max = 0;

	for (int i = 0; i < table->size; i++) {
		int count = htable_debug_print_key_and_count( table, table->keys[i] );
		if (count) boxes_filled++;
		if (count > boxes_max) boxes_max = count;
	}

	fprintf(stderr, "Hashtable stats\n");
	fprintf(stderr, "===============\n");
	fprintf(stderr, "Table size:       %5i\n", table->size);
	fprintf(stderr, "In use:           %5i (%3.0i%%)\n", table->used, 100 * table->used / table->size);
	fprintf(stderr, "Empty boxes:      %5i\n", table->size - boxes_filled);
	fprintf(stderr, "Items in box avr: %5.2f\n", (double) table->used / (double) boxes_filled);
}
#endif

// vim:sw=4:ts=4

/******************************************************************************
 * Filename: htable.h
 * Description:
 *
 * Version: 1.0
 * Created: Nov 13 2009 10:42:17
 * Last modified: Nov 13 2009 10:42:17
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#ifndef _HTABLE_H_
#define _HTABLE_H_

#include <config.h>

#ifndef HTABLE_DEFAULT_SIZE
#define HTABLE_DEFAULT_SIZE 64
#endif

struct htable_item {
	int next;
	void *key;
	void *data;
};

typedef struct htable {
	int    size;
	int    used;
	int   *keys;
	int    first_free;
	struct htable_item *data;
	int 			(*cmpfunc)(void *d1, void *d2);
	unsigned long 	(*hashfunc)(void *data);
	void 			(*func_destruct)(void *key, void *data);
} htable_t;
htable_t *htable_init( int initial_size );
htable_t *htable_init_f(int initial_size, 
					    int (*cmpfunc)(void* d1, void *d2), 
					    unsigned long (*hashfunc)(void *data),
						void (*func_destruct)(void *key, void *data) 	);
int  htable_alloc(htable_t *table);
int  htable_reclaim(htable_t *table, int item);
int  htable_resize( htable_t *table, int new_size);
void htable_destroy(htable_t *table);

int   htable_hash( htable_t *table, void *key );
void *htable_search( htable_t *table, void *key);
int   htable_insert( htable_t *table, void *key, void *data);
int   htable_remove( htable_t *table, void *key);

/* Auxilary functions */
void htable_forall( htable_t *table, void (*func)(void *key, void *data));

/* Debugging functions */
#ifdef DEBUG
int htable_debug_print_key_and_count( htable_t *table, int key );
void htable_debug_print( htable_t *table );
#endif

#endif
// vim:sw=4:ts=4

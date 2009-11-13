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

#ifndef HTABLE_DEFAULT_SIZE
#define HTABLE_DEFAULT_SIZE 64
#endif

struct htable_item {
	int next;
	void *key;
	void *data;
};

typedef struct htable {
	int   size;
	int  *keys;
	struct htable_item *data;
	int   first_free;
	int (*cmpfunc)(void *d1, void *d2);
	unsigned int (*hashfunc)(void *data);
} htable_t;
htable_t *htable_init( int initial_size );
htable_t *htable_init_f(int initial_size, 
					    int (*cmpfunc)(void* d1, void *d2), 
					    unsigned int (*hashfunc)(void *data) 				);
int htable_alloc(htable_t *table);
int htable_reclaim(htable_t *table, int item);
int htable_resize( htable_t *table, int new_size);
int htable_destroy(htable_t *table);

int   htable_hash( htable_t *table, void *key );
void *htable_search( htable_t *table, void *key);
int   htable_insert( htable_t *table, void *key, void *data);
int   htable_remove( htable_t *table, void *key);

#endif
// vim:sw=4:ts=4

/******************************************************************************
 * Filename: fenwick.h
 * Description: Fenwick Tree algorithm implementation,
 *
 * see http://en.wikipedia.org/wiki/Fenwick_tree for more information
 *
 * Version: 1.0
 * Created: May 24 2010 18:37:44
 * Last modified: May 24 2010 18:37:44
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#ifndef _FENWICK_H_
#define _FENWICK_H_

typedef struct fenwick_tree_s {
	int *data;
	int size;
} fenwick_tree_t;

fenwick_tree_t *fenwick_init( int size );
int fenwick_resize( fenwick_tree_t *t, int size );
int fenwick_query( fenwick_tree_t *t, int a, int b);
void fenwick_update( fenwick_tree_t *t, int idx, int val);
void fenwick_destroy( fenwick_tree_t *t);

#endif

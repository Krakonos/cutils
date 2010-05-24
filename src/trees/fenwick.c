/******************************************************************************
 * Filename: fenwick.c
 * Description: Fenwick Tree algorithm implementation,
 *
 * see http://en.wikipedia.org/wiki/Fenwick_tree for more information
 *
 * Version: 1.0
 * Created: May 24 2010 18:37:36
 * Last modified: May 24 2010 18:37:36
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include <stdlib.h>

#include "fenwick.h"

fenwick_tree_t *fenwick_init( int size ) {
	fenwick_tree_t *t = malloc(sizeof(fenwick_tree_t));
	if (t != NULL) {
		t->data = malloc(sizeof(int)*size);
		t->size = size;
	}
	return t;
}

int fenwick_resize( fenwick_tree_t *t, int size ) {
	int *ndata = realloc(t->data, sizeof(int)*size);
	if (ndata == NULL) return t->size;
	t->data = ndata;
	return size;
}

int fenwick_query( fenwick_tree_t *t, int a, int b) {
	int sum = 0;
	if (a == 0) {
		for (; b >= 0; b = (b & (b + 1)) -1 )
			sum += t->data[b];
	} else {
		sum = fenwick_query(t, 0, b) - fenwick_query(t, 0, a-1);
	}
	return sum;
}

void fenwick_update( fenwick_tree_t *t, int idx, int val) {
	for (; idx < t->size; idx |= idx + 1)
		t->data[idx] += val;
}

void fenwick_destroy( fenwick_tree_t *t) {
	free(t->data);
	free(t);
}

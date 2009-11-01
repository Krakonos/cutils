/******************************************************************************
 * Filename: queue.h
 * Description:
 *
 * Version: 1.0
 * Created: Nov 01 2009 11:36:57
 * Last modified: Nov 01 2009 11:36:57
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>

struct queue_item {
	void *data;
	struct queue_item *next;
};

typedef struct queue {
	size_t item_size;
	struct queue_item *first;
	struct queue_item *last;
	int (*func_destruct)(void *item);
} queue_t;

enum {
	QUEUE_EMPTY = -1
};

queue_t* queue_init(size_t item_size);
int queue_enqueue(queue_t *q, void *data);
int queue_dequeue(queue_t *q, void *data);
int queue_head(queue_t *q, void *data);
int queue_destroy(queue_t *q);

#endif
// vim:sw=4:ts=4

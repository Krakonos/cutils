/******************************************************************************
 * Filename: queue.c
 * Description: standard queue in linked list implementation
 *
 * Version: 1.0
 * Created: Nov 01 2009 11:36:06
 * Last modified: Nov 01 2009 11:36:06
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "queue.h"

void queue_free_item(struct queue_item *item) {
	free(item->data);
	free(item);
}

queue_t* queue_init(size_t item_size) {
	queue_t *q = malloc(sizeof(queue_t));
	q->item_size = item_size;
	q->first = NULL;
	q->last = NULL;
	q->func_destruct = NULL;
	return q;
}

int queue_enqueue(queue_t *q, void *data) {
	struct queue_item *item = malloc(sizeof(struct queue_item));
	item->data = malloc(q->item_size);
	memcpy(item->data, data, q->item_size);
	item->next = NULL;
	if (q->last == NULL) {
		/* The list is empty */
		q->first = item;
		q->last = item;
	} else {
		/* There is item in there, append to the end */
		q->last->next = item;
		q->last = item;
	}

	return 0;
}

int queue_dequeue(queue_t *q, void *data) {
	/* Check for item */
	if (q->first == NULL) 
		return QUEUE_EMPTY;
	struct queue_item *item = q->first;
	memcpy(data, item->data, q->item_size);
	q->first = item->next;
	queue_free_item(item);

	/* Was it last item? If so, clear q->last */
	if (q->first == NULL)
		q->last = NULL;

	return 0;
}

int queue_head(queue_t *q, void *data) {
	/* Just copy the data out */
	if (q->first == NULL)
		return QUEUE_EMPTY;
	memcpy(data, q->first->data, q->item_size);

	return 0;
}

int queue_destroy(queue_t *q) {
	struct queue_item *item = q->first;
	while (item != NULL) {
		struct queue_item *ptr = item;
		item = item->next;
		if (q->func_destruct != NULL)
			q->func_destruct(ptr->data);
		queue_free_item(ptr);
	}
	free(q);
	return 0;
}

// vim:sw=4:ts=4

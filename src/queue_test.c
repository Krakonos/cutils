/******************************************************************************
 * Filename: queue_test.c
 * Description: queue unit test
 *
 * Version: 1.0
 * Created: Nov 01 2009 12:48:18
 * Last modified: Nov 01 2009 12:48:18
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include "queue.h"
#include "test.h"

#define TEST_LENGTH 1000

int freed;

int destroy( void *item ) {
	free(*(int**)item);
	freed++;
}

int main() {
	int failed = 0;
	int ok = 1;

	queue_t *q;

	TBEGIN("normal queue operations");
	q = queue_init(sizeof(int));
	for (int i = 0; i < TEST_LENGTH; i++)
		queue_enqueue(q, &i);
	
	for (int i = 0; i < TEST_LENGTH; i++) {
		int a;
		queue_dequeue(q, &a);
		if (a != i) ok = 0;
	}
	queue_destroy(q);
	TEST(ok, failed++);

	TBEGIN("queue autoremove");
	freed = 0;
	q = queue_init(sizeof(int*));
	q->func_destruct = &destroy;
	for (int i = 0; i < TEST_LENGTH; i++) {
		int *a = malloc(sizeof(int));
		*a = i;
		queue_enqueue(q, &a);
	}
	queue_destroy(q);
	TEST(freed == TEST_LENGTH, failed++);

	return failed;
}

// vim:sw=4:ts=4

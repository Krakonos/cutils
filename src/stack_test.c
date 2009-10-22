/******************************************************************************
 * Filename: stack_test.c
 * Description: stack_t test case
 *
 * Version: 1.0
 * Created: Oct 17 2009 20:32:30
 * Last modified: Oct 17 2009 20:32:30
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>


#include "stack.h"

#define TEST_LENGTH 1000

#define TEST(var,...) if (var) printf("ok\n"); else { printf("FAILED\n"); __VA_ARGS__; }

int freed;

int destroy(void *item) {
	free(*(int**)item);
	freed++;
	return 0;
}

int main(int argc, char **argv) {
	int ok;
	int globok = 0;

	stack_t *stack = stack_init(0, sizeof(int));
	printf("Testing stack pusp/pop... ");
	for (int i = 0; i < TEST_LENGTH; i++) {
		stack_push( stack, &i );
	}

	ok = 1;
	for (int i = TEST_LENGTH-1; i >= 0; i--) {
		int r;
		stack_pop(stack, &r);
		if (i != r) ok = 0;
	}
	
	stack_destroy( stack );
	
	TEST(ok, globok++)

	stack = stack_init(0, sizeof(int*));
	printf("Testing stack autoremove... ");
	freed = 0;
	stack->func_destruct = &destroy;
	for (int i = 0; i < TEST_LENGTH; i++) {
		int *ptr = malloc(sizeof(int));
		*ptr = i;
		stack_push( stack, &ptr );
	}
	stack_destroy( stack );

	TEST(freed == TEST_LENGTH, globok++) 
	
	if (globok) 
		printf(">> %i test FAILED.\n", globok);
	else printf(">> All test passed.\n");

	return globok;
}


// vim:sw=4:ts=4

/******************************************************************************
 * Filename: stack.c
 * Description:
 *
 * Version: 1.0
 * Created: Oct 17 2009 19:15:10
 * Last modified: Oct 17 2009 19:15:10
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/

#include <stdlib.h>
#include <errno.h>

#include "stack.h"
#include "debug.h"

stack_t* stack_init(int initial_size) {
	stack_t *stack = malloc(sizeof(stack_t));
	stack->size = (initial_size > 0) ? initial_size : STACK_DEFAULT_SIZE;
	stack->sp = 0;
	stack->data = malloc(sizeof(void*)*stack->size);
	CHECK_PTR(stack->data, return NULL;)
	stack->func_destruct = NULL;
	return stack;
}

int stack_destroy(stack_t *stack) {
	stack->size = 0;
	if (stack->func_destruct != NULL) {
		/* func_destruct is set, call it on every remaining item */
		while (stack->sp > 0) {
			stack->func_destruct( STACK_LAST(stack) );
			stack->sp--;
		}
	}
	free(stack->data);
	free(stack);
	return 0;
}

void* stack_peek( stack_t *stack ) {
	return STACK_LAST(stack);
}

void* stack_pop( stack_t *stack) {
	void *ptr = STACK_LAST(stack);
	stack->sp--;
	return ptr;
}

int stack_push( stack_t *stack, void *item) {
	/* Check for available memory and alloc more if needed. */
	if (stack->sp == stack->size) {
		int ret;
		if ((ret = stack_resize( stack, stack->size*2)) != 0)
			return ret;
	}
	stack->data[stack->sp++] = item;
	return 0;
}

int stack_resize( stack_t *stack, int size ) {
	/* 
	 * Alloc ``size'' memory, unless it's less than sp. This way I will
	 * not leak memory and cna use stack_resize( ptr, 0 ) to trim stack
	 * if no more space is needed .
	 */
	int newsize = (size > stack->sp) ? size : stack->sp;
	stack->data = realloc( stack->data, newsize*sizeof(void*) );
	int err = errno;
	/* Check for failure */
	if (err == ENOMEM)
		return ENOMEM;

	stack->size = newsize;

	return 0;
}

// vim:sw=4:ts=4

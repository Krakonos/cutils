/******************************************************************************
 * Filename: stack.c
 * Description: dynamic array stack implementation
 *
 * Version: 1.0
 * Created: Oct 17 2009 19:15:10
 * Last modified: Oct 17 2009 19:15:10
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "stack.h"
#include "macro.h"

stack_t* stack_init( int initial_size, size_t item_size ) {
	stack_t *stack = malloc(sizeof(stack_t));
	if (stack == NULL) return NULL;
	stack->size = (initial_size > 0) ? initial_size : STACK_DEFAULT_SIZE;
	stack->item_size = item_size;
	stack->sp = 0;
	stack->data = malloc(item_size * stack->size);
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

int stack_peek( stack_t *stack, void *item ) {
	memcpy(item, STACK_LAST(stack), stack->item_size);
	return 0;
}

int stack_pop( stack_t *stack, void *item) {
	memcpy(item, STACK_LAST(stack), stack->item_size);
	stack->sp--;
	return 0;
}

int stack_push( stack_t *stack, void *item) {
	/* Check for available memory and alloc more if needed. */
	if (stack->sp == stack->size) {
		int ret;
		if ((ret = stack_resize( stack, stack->size*2)) != 0)
			return ret;
	}
	
	memcpy( PTR_TO(stack, stack->sp) , item, stack->item_size );

	stack->sp++;

	return 0;
}

int stack_resize( stack_t *stack, int size ) {
	/* 
	 * Alloc ``size'' memory, unless it's less than sp. This way I will
	 * not leak memory and can use stack_resize( ptr, 0 ) to trim stack
	 * if no more space will be needed.
	 */
	int newsize = (size > stack->sp) ? size : stack->sp;
	stack->data = realloc( stack->data, newsize*stack->item_size );
	int err = errno;
	/* Check for failure */
	if (err == ENOMEM)
		return ENOMEM;

	stack->size = newsize;

	return 0;
}

// vim:sw=4:ts=4

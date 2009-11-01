/******************************************************************************
 * Filename: stack.h
 * Description: simple growing-stack impl.
 *
 * Version: 1.0
 * Created: Oct 17 2009 19:26:05
 * Last modified: Oct 17 2009 19:26:05
 *
 * Author: Ladislav Láska
 * e-mail: ladislav.laska@gmail.com
 *
 ******************************************************************************/
#ifndef _STACK_H_
#define _STACK_H_

#include <errno.h>

#ifndef STACK_DEFAULT_SIZE
#define STACK_DEFAULT_SIZE 64
#endif

//((void*)((int)stack->data+((stack->sp-1)*stack->item_size)))
#define PTR_TO(stack, idx) ((void*) (((int) (stack)->data)+((stack)->item_size * (idx))) )
#define STACK_LAST(stack) PTR_TO((stack), ((stack)->sp-1))
#define CHECK_PTR(ptr, cmd) if ((ptr) == NULL) { cmd }

typedef struct stack {
	int size;
	size_t item_size;
	int sp; /* Stack pointer actually points to next free space, since it more
				convenient for handling empty stack */
	void *data;
	int (*func_destruct)(void *item);
} stack_t;

int stack_resize( stack_t *stack, int size );
int stack_push( stack_t *stack, void *item );
int stack_pop( stack_t *stack, void *item );
int stack_peek( stack_t *stack, void *item );
int stack_destroy(stack_t *stack);
stack_t* stack_init( int initial_size, size_t item_size );

#endif
// vim:sw=4:ts=4

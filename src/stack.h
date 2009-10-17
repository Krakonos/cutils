/******************************************************************************
 * Filename: stack.h
 * Description:
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

#define STACK_LAST(stack) stack->data[stack->sp-1]
#define CHECK_PTR(ptr, cmd) if ((ptr) == NULL) { cmd }

typedef struct stack {
	int size;
	int sp; /* Stack pointer actually points to next free space, since it more
				convenient for handling empty stack */
	void **data;
	int (*func_destruct)(void *item);
} stack_t;

int stack_resize( stack_t *stack, int size );
int stack_push( stack_t *stack, void *item);
void* stack_pop( stack_t *stack);
void* stack_peek( stack_t *stack );
int stack_destroy(stack_t *stack);
stack_t* stack_init(int initial_size);

#endif
// vim:sw=4:ts=4

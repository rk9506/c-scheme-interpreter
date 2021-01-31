#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define STACK_SIZE 8096

typedef struct { void **items; int top; } Stack;

Stack *make_stack();
bool is_empty(Stack *stack);
void push(void *item, Stack *stack);
void *pop(Stack *stack);

#endif // __STACK_H_

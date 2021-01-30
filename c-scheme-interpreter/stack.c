#include "stack.h"

Stack *make_stack()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = 0;
    s->items = malloc(sizeof(void*) * STACK_SIZE);

    return s;
}

bool is_empty(Stack *stack)
{
    return stack->top == 00;
}

void push(void *item, Stack *stack)
{
    stack->top++;
    stack->items[stack->top] = item;
}

void *pop(Stack *stack)
{
    void *item = stack->items[stack->top];
    stack->top--;

    return item;
}

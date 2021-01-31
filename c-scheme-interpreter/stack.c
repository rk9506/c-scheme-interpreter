#include "stack.h"

Stack *make_stack()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = -1;
    s->items = malloc(sizeof(void*) * STACK_SIZE);

    return s;
}

bool is_empty(Stack *stack)
{
    return stack->top == -1;
}

void push(void *item, Stack *stack)
{
    stack->top++;
    stack->items[stack->top] = item;
}

void *pop(Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Trying to pop from an empty stack!\n");
        return NULL;
    }

    void *item = stack->items[stack->top];
    stack->top--;

    return item;
}

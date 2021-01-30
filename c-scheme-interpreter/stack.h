#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define STACK_SIZE 8096

typedef struct { void **items; unsigned int top; } Stack;

#endif // __STACK_H_

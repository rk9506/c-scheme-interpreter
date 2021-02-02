#ifndef __HEAP_H_
#define __HEAP_H_

#include "types.h"
#include "debug.h"
#include "printer.h"

#include <stdlib.h>

#define HEAP_SIZE 1024 * 1024

void initialise_heap();

SchemeAtom *car(SchemeAtom *pair);
SchemeAtom *cdr(SchemeAtom *pair);

void set_car(SchemeAtom *pair, SchemeAtom *atom);
void set_cdr(SchemeAtom *pair, SchemeAtom *atom);
SchemeAtom *cons(SchemeAtom *a, SchemeAtom *b);

#endif // __HEAP_H_

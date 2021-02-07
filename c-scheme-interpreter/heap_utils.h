#ifndef __HEAP_UTILS_H_
#define __HEAP_UTILS_H_

#include "gc.h"
#include "debug.h"

void perform_gc();
void debug_dump_heap(SchemeAtom **the_cars, SchemeAtom **the_cdrs);
SchemeAtom *get_populated_root();

#endif // __HEAP_UTILS_H_

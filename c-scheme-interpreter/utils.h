#ifndef __UTILS_H_
#define __UTILS_H_

#include "types.h"
#include "heap.h"

unsigned int list_length(SchemeAtom *l);
SchemeAtom *list_drop(SchemeAtom *l, int n);

#endif // __UTILS_H_

#ifndef __UTILS_H_
#define __UTILS_H_

#include "types.h"
#include "heap.h"

SchemeAtom *singleton_list(SchemeAtom *contents);
unsigned int list_length(SchemeAtom *l);
SchemeAtom *list_drop(SchemeAtom *l, int n);
void throw_exception(char *message);

#endif // __UTILS_H_

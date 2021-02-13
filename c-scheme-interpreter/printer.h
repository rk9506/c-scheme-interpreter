#ifndef __PRINTER_H_
#define __PRINTER_H_

#include "types.h"
#include "heap.h"
#include "procedure_utils.h"

#include <stdio.h>
#include <float.h>

void print_elem(SchemeAtom *elem);
void print_elem_line(SchemeAtom *elem);
void print_list(SchemeAtom *list);
void print_atom(SchemeAtom *atom);

#endif // __PRINTER_H_

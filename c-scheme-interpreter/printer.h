#ifndef __PRINTER_H_
#define __PRINTER_H_

#include "types.h"

#include <stdio.h>
#include <float.h>

void print_list(struct SchemeList *list);
void print_elem(SchemeListElem *elem);

#endif // __PRINTER_H_

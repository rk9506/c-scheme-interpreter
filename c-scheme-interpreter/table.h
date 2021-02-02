#ifndef __TABLE_H_
#define __TABLE_H_

#include "types.h"
#include "printer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SchemeAtom *entry_value(SchemeAtom *entry);

SchemeAtom *insert(char *key, SchemeAtom *value, SchemeAtom *table);
SchemeAtom *lookup(char *key, SchemeAtom *table);
void print_table(SchemeAtom *table);


SchemeAtom *make_table();
void free_table(SchemeAtom *list);

#endif // __TABLE_H_

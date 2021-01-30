#ifndef __TABLE_H_
#define __TABLE_H_

#include "types.h"
#include "printer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct SchemeList *insert(char *key, SchemeListElem *value, struct SchemeList *table);
struct SchemeList *lookup(char *key, struct SchemeList *table);
void print_table(struct SchemeList *table);


struct SchemeList *make_table();
void free_table(struct SchemeList *list);

#endif // __TABLE_H_

#include "table.h"

struct SchemeList *make_table()
{
    return make_list();
}

void free_table(struct SchemeList *list)
{
    free_list(list);
}

struct SchemeList *insert(char *key, SchemeListElem *value, struct SchemeList *table)
{
    struct SchemeList *result = make_list();
    result->car = make_symbol(key);
    result->cdr = make_list();
    free(result->cdr->car);
    result->cdr->car = value;

    struct SchemeList *new_table = make_list();
    new_table->car->list = result;
    new_table->cdr = table;

    return new_table;
}

struct SchemeList *lookup(char *key, struct SchemeList *table)
{
    if (table == NULL) return NULL;

    struct SchemeList *first_entry = table->car->list;
    if (first_entry != NULL && strcmp(first_entry->car->atom->val->sym, key) == 0)
    {
        return first_entry;
    } else
    {
        return lookup(key, table->cdr);
    }
}

void print_table(struct SchemeList *table)
{
    print_list(table);
}

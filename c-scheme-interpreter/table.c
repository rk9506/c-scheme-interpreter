#include "table.h"

SchemeAtom *make_table()
{
    return the_empty_list();
}

SchemeAtom *make_entry(char *key, SchemeAtom *value)
{
    SchemeAtom *key_atom = make_symbol(key);

    return cons(key_atom, cons(value, the_empty_list()));
}

SchemeAtom *entry_value(SchemeAtom *entry)
{
    return car(cdr(entry));
}

SchemeAtom *insert(char *key, SchemeAtom *value, SchemeAtom *table)
{
    SchemeAtom *entry = make_entry(key, value);

    SchemeAtom *new_table = cons(entry, table);

    return new_table;
}

SchemeAtom *lookup(char *key, SchemeAtom *table)
{
    if (table == NULL) return NULL;

    SchemeAtom *first_entry = car(table);
    if (first_entry != NULL && strcmp(car(first_entry)->val->sym, key) == 0)
    {
        return first_entry;
    } else
    {
        return lookup(key, cdr(table));
    }
}

void print_table(SchemeAtom *table)
{
    print_list(table);
}

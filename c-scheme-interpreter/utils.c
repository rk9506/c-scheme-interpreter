#include "utils.h"

SchemeAtom *singleton_list(SchemeAtom *contents)
{
    return cons(contents, the_empty_list());
}

unsigned int list_length(SchemeAtom *l)
{
    if (is_null_list(l)) return 0;

    return 1 + list_length(cdr(l));
}

SchemeAtom *list_drop(SchemeAtom *l, int n)
{
    if (n == 0)
    {
        return l;
    }

    return list_drop(cdr(l), n - 1);
}

void throw_exception(char *message)
{
    printf("%s\n", message);
    exit(1);
}


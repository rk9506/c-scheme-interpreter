#include "types.h"

SchemeListElem *make_elem();

struct SchemeList *make_list()
{
    struct SchemeList *result = malloc(sizeof(struct SchemeList));
    result->cdr = NULL;
    result->car = make_elem();

    return result;
}

SchemeListElem *make_elem()
{
    SchemeListElem *result = malloc(sizeof(SchemeListElem));
    result->atom = NULL;
    result->list = NULL;

    return result;
}

SchemeAtom *make_atom()
{
    return malloc(sizeof(SchemeAtom));
}

SchemePrimitive *make_primitive()
{
    return malloc(sizeof(SchemePrimitive));
}

SchemeListElem *make_symbol(char *sym)
{
    SchemeListElem *elem = make_elem();
    elem->atom = make_atom();

    elem->atom->type_tag = SCHEME_SYMBOL;
    elem->atom->val = make_primitive();
    elem->atom->val->sym = sym;

    return elem;
}

unsigned int list_length(struct SchemeList *l)
{
    if (l == NULL) return 0;

    return 1 + list_length(l->cdr);
}

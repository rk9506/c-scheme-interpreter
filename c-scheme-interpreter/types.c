#include "types.h"

struct SchemeList *make_list()
{
    struct SchemeList *result = malloc(sizeof(struct SchemeList));
    result->cdr = NULL;
    SchemeListElem *result_car = malloc(sizeof(SchemeListElem));
    result_car->atom = NULL;
    result_car->list = NULL;

    result->car = result_car;

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

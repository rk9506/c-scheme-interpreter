#include "types.h"

SchemeListElem *make_elem();

struct SchemeList *make_list()
{
    struct SchemeList *result = malloc(sizeof(struct SchemeList));
    result->cdr = NULL;
    result->car = make_elem();

    return result;
}

void free_list(struct SchemeList *list)
{
    if (list == NULL) return;

    free_elem(list->car);
    free_list(list->cdr);
}

SchemeListElem *make_elem()
{
    SchemeListElem *result = malloc(sizeof(SchemeListElem));
    result->atom = NULL;
    result->list = NULL;

    return result;
}

void free_elem(SchemeListElem *elem)
{
    if (elem == NULL) return;
    free_list(elem->list);
    free_atom(elem->atom);
    free(elem);
}

SchemeAtom *make_atom()
{
    return malloc(sizeof(SchemeAtom));
}

void free_atom(SchemeAtom *atom)
{
    if (atom == NULL) return;
    free(atom);
}

SchemePrimitive *make_primitive()
{
    return malloc(sizeof(SchemePrimitive));
}

SchemeListElem *make_number(float num)
{
    SchemeListElem *elem = make_elem();
    elem->atom = make_atom();

    elem->atom->type_tag = SCHEME_NUMBER;
    elem->atom->val = make_primitive();
    elem->atom->val->num = num;

    return elem;
}

SchemeListElem *make_boolean(bool boolean)
{
    SchemeListElem *elem = make_elem();
    elem->atom = make_atom();

    elem->atom->type_tag = SCHEME_BOOLEAN;
    elem->atom->val = make_primitive();
    elem->atom->val->boolean = boolean;

    return elem;
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

SchemeListElem *make_procedure(struct SchemeList *parameters,
                               struct SchemeList *body,
                               struct Environment *env)
{
    SchemeProcedure *proc = malloc(sizeof(SchemeProcedure));

    proc->parameters = parameters;
    proc->body = body;
    proc->env = env;

    SchemeListElem *elem = make_elem();
    elem->atom = make_atom();

    elem->atom->type_tag = SCHEME_PROCEDURE;
    elem->atom->val = make_primitive();
    elem->atom->val->proc = proc;

    return elem;
}

SchemeListElem *make_primitive_procedure(PrimitiveProcedure proc)
{
    SchemeListElem *elem = make_elem();
    elem->atom = make_atom();

    elem->atom->type_tag = PRIMITIVE_PROCEDURE;
    elem->atom->val = make_primitive();
    elem->atom->val->primitive_proc = proc;

    return elem;
}

unsigned int list_length(struct SchemeList *l)
{
    if (l == NULL) return 0;

    return 1 + list_length(l->cdr);
}

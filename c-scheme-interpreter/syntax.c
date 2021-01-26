#include "syntax.h"

bool is_self_evaluating(SchemeListElem *elem)
{
    SchemeAtom *atom = elem->atom;

    if (atom != NULL)
    {
        TypeTag type_tag = atom->type_tag;

        return type_tag == SCHEME_STRING
            || type_tag == SCHEME_NUMBER
            || type_tag == SCHEME_BOOLEAN;
    }

    return false;
}

bool is_variable(SchemeListElem *elem)
{
    SchemeAtom *atom = elem->atom;

    if (atom != NULL)
    {
        return atom->type_tag == SCHEME_SYMBOL;
    }

    return false;
}

bool is_tagged_list(SchemeListElem *elem, char *tag)
{
    struct SchemeList *list = elem->list;

    if (list != NULL)
    {
        SchemeAtom *atom = list->car->atom;

        if (atom != NULL)
        {
            return strcmp(atom->val->sym, tag) == 0;
        }
    }

    return false;
}

bool is_quoted(SchemeListElem *exp)
{
    return is_tagged_list(exp, "quote");
}

SchemeListElem *text_of_quotation(SchemeListElem *exp)
{
    return exp->list->cdr->car;
}

bool is_definition(SchemeListElem *exp)
{
    return is_tagged_list(exp, "define");
}

SchemeListElem *definition_variable(SchemeListElem *exp)
{
    SchemeListElem *var = exp->list->cdr->car;
    if (is_variable(var))
    {
        return var;
    }

    printf("Invalid definition variable\n");

    return NULL;
}

SchemeListElem *definition_value(SchemeListElem *exp)
{
    SchemeListElem *var = exp->list->cdr->car;
    if (is_variable(var))
    {
        return exp->list->cdr->cdr->car;
    }

    // TODO: Return make-lambda when second elem is a pair,
    // for syntactic sugar (define (f x) ...)

    return NULL;
}

bool is_assignment(SchemeListElem *exp)
{
    return is_tagged_list(exp, "set!");
}

SchemeListElem *assignment_variable(SchemeListElem *exp)
{
    return exp->list->cdr->car;
}

SchemeListElem *assignment_value(SchemeListElem *exp)
{
    return exp->list->cdr->cdr->car;
}

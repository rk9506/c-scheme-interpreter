#include "primitive_procedures.h"

SchemeListElem *apply_primitive_procedure(SchemeListElem *proc_elem, struct SchemeList *args)
{
    PrimitiveProcedure primitive_proc = proc_elem->atom->val->primitive_proc;

    return (*primitive_proc)(args);
}

float get_number_car(struct SchemeList *args)
{
    SchemeAtom *atom = args->car->atom;

    if (atom->type_tag != SCHEME_NUMBER)
    {
        printf("Argument must be a number\n");
        return 0;
    }

    return atom->val->num;
}

float get_number_cadr(struct SchemeList *args)
{
    SchemeAtom *atom = args->cdr->car->atom;

    if (atom->type_tag != SCHEME_NUMBER)
    {
        printf("Argument must be a number\n");
        return 0;
    }

    return atom->val->num;
}


SchemeListElem *primitive_add(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 + arg2);
}

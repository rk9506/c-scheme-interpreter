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

bool get_boolean_car(struct SchemeList *args)
{
    SchemeAtom *atom = args->car->atom;

    if (atom->type_tag != SCHEME_BOOLEAN)
    {
        printf("Argument must be a boolean\n");
        return 0;
    }

    return atom->val->boolean;
}

bool get_boolean_cadr(struct SchemeList *args)
{
    SchemeAtom *atom = args->cdr->car->atom;

    if (atom->type_tag != SCHEME_BOOLEAN)
    {
        printf("Argument must be a boolean\n");
        return false;
    }

    return atom->val->boolean;
}

SchemeListElem *primitive_add(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 + arg2);
}

SchemeListElem *primitive_subtract(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 - arg2);
}

SchemeListElem *primitive_multiply(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 * arg2);
}

SchemeListElem *primitive_divide(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 / arg2);
}

SchemeListElem *primitive_remainder(struct SchemeList *args)
{
    int arg1 = (int) get_number_car(args);
    int arg2 = (int) get_number_cadr(args);

    return make_number(arg1 % arg2);
}

SchemeListElem *primitive_number_equality(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 == arg2);
}

SchemeListElem *primitive_lt(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 < arg2);
}

SchemeListElem *primitive_lte(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 <= arg2);
}

SchemeListElem *primitive_gt(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 > arg2);
}

SchemeListElem *primitive_gte(struct SchemeList *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 >= arg2);
}

SchemeListElem *primitive_and(struct SchemeList *args)
{
    bool arg1 = get_boolean_car(args);
    bool arg2 = get_boolean_cadr(args);

    return make_boolean(arg1 && arg2);
}

SchemeListElem *primitive_or(struct SchemeList *args)
{
    bool arg1 = get_boolean_car(args);
    bool arg2 = get_boolean_cadr(args);

    return make_boolean(arg1 || arg2);
}

SchemeListElem *primitive_not(struct SchemeList *args)
{
    bool arg1 = get_boolean_car(args);

    return make_boolean(!arg1);
}

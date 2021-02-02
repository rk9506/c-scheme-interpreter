#include "primitive_procedures.h"

#define INPUT_BUFFER_SIZE 1024 * 1024

SchemeAtom *apply_primitive_procedure(SchemeAtom *proc_elem, SchemeAtom *args)
{
    PrimitiveProcedure primitive_proc = proc_elem->val->primitive_proc;

    return (*primitive_proc)(args);
}

float get_number_car(SchemeAtom *args)
{
    SchemeAtom *atom = car(args);

    if (!is_number(atom))
    {
        printf("Argument must be a number\n");
        return 0;
    }

    return atom->val->num;
}

float get_number_cadr(SchemeAtom *args)
{
    SchemeAtom *atom = car(cdr(args));

    if (!is_number(atom))
    {
        printf("Argument must be a number\n");
        return 0;
    }

    return atom->val->num;
}

bool get_boolean_car(SchemeAtom *args)
{
    SchemeAtom *atom = car(atom);

    if (!is_boolean(atom))
    {
        printf("Argument must be a boolean\n");
        return 0;
    }

    return atom->val->boolean;
}

bool get_boolean_cadr(SchemeAtom *args)
{
    SchemeAtom *atom = car(cdr(args));

    if (!is_boolean(atom))
    {
        printf("Argument must be a boolean\n");
        return false;
    }

    return atom->val->boolean;
}

char *get_string_car(SchemeAtom *args)
{
    SchemeAtom *atom = car(atom);

    if (!is_string(atom))
    {
        printf("Argument must be a string\n");
        return 0;
    }

    return atom->val->str;
}


SchemeAtom *primitive_add(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 + arg2);
}

SchemeAtom *primitive_subtract(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 - arg2);
}

SchemeAtom *primitive_multiply(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 * arg2);
}

SchemeAtom *primitive_divide(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_number(arg1 / arg2);
}

SchemeAtom *primitive_remainder(SchemeAtom *args)
{
    int arg1 = (int) get_number_car(args);
    int arg2 = (int) get_number_cadr(args);

    return make_number(arg1 % arg2);
}

SchemeAtom *primitive_number_equality(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 == arg2);
}

SchemeAtom *primitive_lt(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 < arg2);
}

SchemeAtom *primitive_lte(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 <= arg2);
}

SchemeAtom *primitive_gt(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 > arg2);
}

SchemeAtom *primitive_gte(SchemeAtom *args)
{
    float arg1 = get_number_car(args);
    float arg2 = get_number_cadr(args);

    return make_boolean(arg1 >= arg2);
}

SchemeAtom *primitive_and(SchemeAtom *args)
{
    bool arg1 = get_boolean_car(args);
    bool arg2 = get_boolean_cadr(args);

    return make_boolean(arg1 && arg2);
}

SchemeAtom *primitive_or(SchemeAtom *args)
{
    bool arg1 = get_boolean_car(args);
    bool arg2 = get_boolean_cadr(args);

    return make_boolean(arg1 || arg2);
}

SchemeAtom *primitive_not(SchemeAtom *args)
{
    bool arg1 = get_boolean_car(args);

    return make_boolean(!arg1);
}

SchemeAtom *primitive_display(SchemeAtom *args)
{
    char *arg1 = get_string_car(args);

    printf("%s", arg1);

    return make_symbol("ok");
}

SchemeAtom *primitive_newline(SchemeAtom *args)
{
    printf("\n");

    return make_symbol("ok");
}

SchemeAtom *primitive_read(SchemeAtom *args)
{
    char exp[INPUT_BUFFER_SIZE];
    fgets(exp, INPUT_BUFFER_SIZE, stdin);

    return generate_ast(exp);
}

SchemeAtom *primitive_cons(SchemeAtom *args)
{
    return cons(car(args), car(cdr(args)));
}

SchemeAtom *primitive_car(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return car(pair);
}

SchemeAtom *primitive_cdr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return cdr(pair);
}

SchemeAtom *primitive_list(SchemeAtom *args)
{
    if (is_null_list(args))
    {
        return the_empty_list();
    }

    return cons(car(args), primitive_list(cdr(args)));
}

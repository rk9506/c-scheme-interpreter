#include "primitive_procedures.h"

#define INPUT_BUFFER_SIZE 1024 * 1024

SchemeAtom *apply_primitive_procedure(SchemeAtom *proc_elem, SchemeAtom *args)
{
    PrimitiveProcedure primitive_proc = proc_elem->val->primitive_proc;

    return (*primitive_proc)(args);
}

SchemeAtom *primitive_apply_in_underlying_scheme(SchemeAtom *args)
{
    return apply_primitive_procedure(car(args), car(cdr(args)));
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
    SchemeAtom *atom = car(args);

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
    SchemeAtom *atom = car(args);

    if (!is_string(atom))
    {
        printf("Argument must be a string\n");
        return 0;
    }

    return atom->val->str;
}

char *get_symbol_car(SchemeAtom *args)
{
    SchemeAtom *atom = car(args);

    if (!is_symbol(atom))
    {
        printf("Argument must be a symbol\n");
        return 0;
    }

    return atom->val->sym;
}

char *get_symbol_cadr(SchemeAtom *args)
{
    SchemeAtom *atom = car(cdr(args));

    if (!is_symbol(atom))
    {
        printf("Argument must be a symbol\n");
        return 0;
    }

    return atom->val->sym;
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
    SchemeAtom *arg = car(args);
    if (is_string(arg))
    {
        printf("%s", arg->val->str);
    } else
    {
        print_elem(arg);
    }

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
    primitive_temp = cons(car(args), car(cdr(args)));

    return primitive_temp;
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

SchemeAtom *primitive_cadr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return car(cdr(pair));
}

SchemeAtom *primitive_cddr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return cdr(cdr(pair));
}

SchemeAtom *primitive_caar(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return car(car(pair));
}

SchemeAtom *primitive_cdar(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return cdr(car(pair));
}

SchemeAtom *primitive_caadr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return car(car(cdr(pair)));
}

SchemeAtom *primitive_caddr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return car(cdr(cdr(pair)));
}

SchemeAtom *primitive_cdadr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return cdr(car(cdr(pair)));
}

SchemeAtom *primitive_cdddr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return cdr(cdr(cdr(pair)));
}

SchemeAtom *primitive_cadddr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return car(cdr(cdr(cdr(pair))));
}

SchemeAtom *primitive_cddddr(SchemeAtom *args)
{
    SchemeAtom *pair = car(args);

    return cdr(cdr(cdr(cdr(pair))));
}


SchemeAtom *primitive_list(SchemeAtom *args)
{
    if (is_null_list(args))
    {
        return the_empty_list();
    } else
    {
        return cons(car(args), primitive_list(cdr(args)));
    }
}

SchemeAtom *primitive_is_null(SchemeAtom *args)
{
    return make_boolean(is_null_list(car(args)));
}

SchemeAtom *primitive_length(SchemeAtom *args)
{
    SchemeAtom *l = car(args);

    return make_number(list_length(l));
}

SchemeAtom *primitive_set_car(SchemeAtom *args)
{
    set_car(car(args), car(cdr(args)));
    return make_symbol("ok");
}

SchemeAtom *primitive_set_cdr(SchemeAtom *args)
{
    set_cdr(car(args), car(cdr(args)));
    return make_symbol("ok");
}

SchemeAtom *primitive_error(SchemeAtom *args)
{
    print_elem(args);
    throw_exception("Scheme error!");
    return NULL;
}

SchemeAtom *primitive_symbol_equality(SchemeAtom *args)
{
    char *first = get_symbol_car(args);
    char *second = get_symbol_cadr(args);

    return make_boolean(strcmp(first, second) == 0);
}

SchemeAtom *primitive_boolean_equality(SchemeAtom *args)
{
    bool first = get_boolean_car(args);
    bool second = get_boolean_cadr(args);

    return make_boolean(first == second);
}

SchemeAtom *primitive_eq(SchemeAtom *args)
{
    SchemeAtom *first = car(args);
    SchemeAtom *second = car(cdr(args));

    if (is_symbol(first) && is_symbol(second))
    {
        return primitive_symbol_equality(args);
    } else if (is_boolean(first) && is_boolean(second))
    {
        return primitive_boolean_equality(args);
    } else if (is_null_list(first) && is_null_list(second))
    {
        return make_boolean(true);
    }

    return make_boolean(false);
}

SchemeAtom *primitive_is_symbol(SchemeAtom *args)
{
    return make_boolean(is_symbol(car(args)));
}

SchemeAtom *primitive_is_number(SchemeAtom *args)
{
    return make_boolean(is_number(car(args)));
}

SchemeAtom *primitive_is_pair(SchemeAtom *args)
{
    return make_boolean(is_pair(car(args)));
}

SchemeAtom *primitive_is_string(SchemeAtom *args)
{
    return make_boolean(is_string(car(args)));
}

#include "env.h"

Environment *the_global_environment;

Environment *get_global_environment()
{
    return the_global_environment;
}

SchemeAtom *env_bindings(Environment *env)
{
    return car(env);
}

SchemeAtom *enclosing_env(Environment *env)
{
    return cdr(env);
}

void set_bindings(Environment *env, SchemeAtom *bindings)
{
    set_car(env, bindings);
}

void set_enclosing_env(Environment *env, Environment *parent)
{
    set_cdr(env, parent);
}

SchemeAtom *lookup_variable_value(char *name, Environment *env)
{
    if (env == NULL)
    {
        printf("Unbound variable %s\n", name);
        return NULL;
    }

    SchemeAtom *e = lookup(name, env_bindings(env));

    if (e == NULL)
    {
        return lookup_variable_value(name, enclosing_env(env));
    }

    return entry_value(e);
}

SchemeAtom *lookup_variable_value_sym(SchemeAtom *symbol, Environment *env)
{
    return lookup_variable_value(symbol->val->sym, env);
}

void set_variable_value(char *var, SchemeAtom *val, Environment *env)
{
    if (is_null_list(env))
    {
        printf("Unbound variable -- SET! %s", var);
        return;
    }

    SchemeAtom *e = lookup(var, env_bindings(env));

    if (e == NULL)
    {
        set_variable_value(var, val, enclosing_env(env));
    }

    set_car(cdr(e), val);
}

void set_variable_value_sym(SchemeAtom *var, SchemeAtom *val, Environment *env)
{
    set_variable_value(var->val->sym, val, env);
}

void define_variable(char *var, SchemeAtom *val, Environment *env)
{
    if (lookup(var, env_bindings(env)))
    {
        set_variable_value(var, val, env);
    } else
    {
        set_bindings(env, insert(var, val, env_bindings(env)));
    }
}

void define_variable_sym(SchemeAtom *var, SchemeAtom *val, Environment *env)
{
    define_variable(var->val->sym, val, env);
}

Environment *make_environment()
{
    return cons(the_empty_list(), the_empty_list());
}

void insert_bindings(SchemeAtom *vars, SchemeAtom *vals, Environment *env)
{
    if (is_null_list(vars)) return;

    define_variable(car(vars)->val->sym, car(vals), env);

    insert_bindings(cdr(vars), cdr(vals), env);
}

Environment *extend_environment(SchemeAtom *vars, SchemeAtom *vals, Environment *env)
{
    unsigned int vars_length = list_length(vars);
    unsigned int vals_length = list_length(vals);

    if (vars_length == vals_length)
    {
        Environment *new_env = make_environment();
        set_enclosing_env(new_env, env);

        insert_bindings(vars, vals, new_env);

        return new_env;
    } else if (vars_length < vals_length)
    {
        printf("Too many arguments supplied\n");
    } else
    {
        printf("Too few arguments supplied\n");
    }

    return NULL;
}

void define_primitive(char *symbol, PrimitiveProcedure proc)
{
    define_variable(symbol, make_primitive_procedure(proc), the_global_environment);
}

void add_primitive_procedures()
{
    // Arithmetic operators
    define_primitive("+", &primitive_add);
    define_primitive("-", &primitive_subtract);
    define_primitive("*", &primitive_multiply);
    define_primitive("/", &primitive_divide);
    define_primitive("remainder", &primitive_remainder);

    // Comparison operators
    define_primitive("=", &primitive_number_equality);
    define_primitive("<", &primitive_lt);
    define_primitive("<=", &primitive_lte);
    define_primitive(">", &primitive_gt);
    define_primitive(">=", &primitive_gte);

    // Boolean operators
    define_primitive("and", &primitive_and);
    define_primitive("or", &primitive_or);
    define_primitive("not", &primitive_not);

    // IO
    define_primitive("display", &primitive_display);
    define_primitive("newline", &primitive_newline);
    define_primitive("read", &primitive_read);

    // Lists
    define_primitive("cons", &primitive_cons);
    define_primitive("car", &primitive_car);
    define_primitive("cdr", &primitive_cdr);
    define_primitive("list", &primitive_list);
    define_primitive("null?", &primitive_is_null);
    define_primitive("length", &primitive_length);

    // Symbols
    define_primitive("eq?", &primitive_symbol_equality);
}

void print_env(Environment *env)
{
    if (env == NULL) return;

    print_table(env_bindings(env));

    print_env(enclosing_env(env));
}

void add_constants()
{
    define_variable("nil", the_empty_list(), the_global_environment);
    define_variable("true", make_boolean(true), the_global_environment);
    define_variable("false", make_boolean(false), the_global_environment);
}

void setup_global_environment()
{
    the_global_environment = make_environment();

    add_constants();

    add_primitive_procedures();
}

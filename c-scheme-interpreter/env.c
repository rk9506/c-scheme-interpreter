#include "env.h"

struct Environment *the_global_environment;

struct Environment *get_global_environment()
{
    return the_global_environment;
}

SchemeListElem *lookup_variable_value(char *name, struct Environment *env)
{
    if (env == NULL)
    {
        printf("Unbound variable %s\n", name);
        return NULL;
    }

    struct SchemeList *e = lookup(name, env->bindings);
    if (e == NULL)
    {
        return lookup_variable_value(name, env->enclosing_env);
    }

    return e->cdr->car;
}

void set_variable_value(char *var, SchemeListElem *val, struct Environment *env)
{
    if (env == NULL)
    {
        printf("Unbound variable -- SET! %s", var);
        return;
    }

    struct SchemeList *e = lookup(var, env->bindings);

    if (e == NULL)
    {
        set_variable_value(var, val, env->enclosing_env);
    }

    free_elem(e->cdr->car);
    e->cdr->car = val;
}

void define_variable(char *var, SchemeListElem *val, struct Environment *env)
{
    if (lookup(var, env->bindings))
    {
        set_variable_value(var, val, env);
    } else
    {
        env->bindings = insert(var, val, env->bindings);
    }
}

struct Environment *make_environment()
{
    struct Environment *env = malloc(sizeof(struct Environment));
    env->bindings = make_table();
    env->enclosing_env = NULL;

    return env;
}

void free_environment(struct Environment *env)
{
    if (env == NULL) return;

    free_table(env->bindings);
    free(env);
}

void insert_bindings(struct SchemeList *vars, struct SchemeList *vals, struct Environment *env)
{
    if (vars == NULL) return;

    define_variable(vars->car->atom->val->sym, vals->car, env);

    insert_bindings(vars->cdr, vals->cdr, env);
}

struct Environment *extend_environment(struct SchemeList *vars, struct SchemeList *vals, struct Environment *env)
{
    unsigned int vars_length = list_length(vars);
    unsigned int vals_length = list_length(vals);

    if (vars_length == vals_length)
    {
        struct Environment *new_env = make_environment();
        new_env->enclosing_env = env;

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
    define_primitive("%", &primitive_remainder);

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
}

struct Environment *get_empty_environment()
{
    return NULL;
}

void print_env(struct Environment *env)
{
    if (env == NULL) return;

    print_table(env->bindings);

    print_env(env->enclosing_env);
}

void setup_global_environment()
{
    the_global_environment = make_environment();
    add_primitive_procedures();
}

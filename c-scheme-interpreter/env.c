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

    struct TableEntry *e = lookup(name, env->bindings);

    if (e == NULL)
    {
        return lookup_variable_value(name, env->enclosing_env);
    }

    return (SchemeListElem*) e->value;
}

void set_variable_value(char *var, SchemeListElem *val, struct Environment *env)
{
    if (env == NULL)
    {
        printf("Unbound variable -- SET! %s", var);
        return;
    }

    struct TableEntry *e = lookup(var, env->bindings);

    if (e == NULL)
    {
        set_variable_value(var, val, env->enclosing_env);
    }

    e->value = val;
}

void define_variable(char *var, SchemeListElem *val, struct Environment *env)
{
    insert(var, val, env->bindings);
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

struct Environment *extend_environment(struct SchemeList *vars, struct SchemeList *vals, struct Environment *env)
{
    unsigned int vars_length = list_length(vars);
    unsigned int vals_length = list_length(vals);

    if (vars_length == vals_length)
    {
        struct Environment *new_env = make_environment();
        new_env->enclosing_env = env;
        return env;
    } else if (vars_length < vals_length)
    {
        printf("Too many arguments supplied\n");
    } else
    {
        printf("Too few arguments supplied\n");
    }

    return NULL;
}

struct Environment *get_empty_environment()
{
    return NULL;
}

void setup_global_environment()
{
    the_global_environment = make_environment();
}

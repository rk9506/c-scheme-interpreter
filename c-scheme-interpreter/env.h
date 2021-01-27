#ifndef __ENV_H_
#define __ENV_H_

#include "types.h"
#include "hash_table.h"
#include "primitive_procedures.h"

#include <stdio.h>

struct Environment
{
    struct Environment *enclosing_env;
    HashTable *bindings;
};

struct Environment *get_global_environment();
void setup_global_environment();

SchemeListElem *lookup_variable_value(char *name, struct Environment *env);
void set_variable_value(char *var, SchemeListElem *val, struct Environment *env);
void define_variable(char *var, SchemeListElem *val, struct Environment *env);

struct Environment *make_environment();
void free_environment(struct Environment *env);

struct Environment *extend_environment(struct SchemeList *vars, struct SchemeList *vals, struct Environment *env);
struct Environment *get_empty_environment();
struct Environment *setup_environment();

#endif // __ENV_H_

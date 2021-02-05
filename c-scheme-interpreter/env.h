#ifndef __ENV_H_
#define __ENV_H_

#include "types.h"
#include "table.h"
#include "primitive_procedures.h"
#include "printer.h"
#include "debug.h"
#include "heap.h"
#include "utils.h"

#include <stdio.h>

typedef SchemeAtom Environment;

SchemeAtom *env_bindings(Environment *env);

Environment *get_global_environment();
void setup_global_environment();

SchemeAtom *lookup_variable_value(char *name, Environment *env);
void set_variable_value(char *var, SchemeAtom *val, Environment *env);
void define_variable(char *var, SchemeAtom *val, Environment *env);

Environment *make_environment();
void free_environment(Environment *env);

Environment *extend_environment(SchemeAtom *vars, SchemeAtom *vals, Environment *env);
Environment *get_empty_environment();
Environment *setup_environment();

void print_env(Environment *env);

#endif // __ENV_H_

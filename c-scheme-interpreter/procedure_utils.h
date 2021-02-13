#ifndef __PROCEDURE_UTILS_H_
#define __PROCEDURE_UTILS_H_

#include "types.h"
#include "heap.h"

SchemeAtom *make_procedure(SchemeAtom *parameters,
                               SchemeAtom *body,
                               SchemeAtom *env);
SchemeAtom *procedure_parameters(SchemeProcedure *proc);
SchemeAtom *procedure_body(SchemeProcedure *proc);
SchemeAtom *procedure_env(SchemeProcedure *proc);

bool is_primitive_procedure(SchemeAtom *atom);
bool is_compiled_procedure(SchemeAtom *atom);
SchemeAtom *make_compiled_procedure(void *entry, SchemeAtom *env);
void *compiled_procedure_entry(SchemeAtom *proc);
SchemeAtom *compiled_procedure_env(SchemeAtom *proc);

#endif // __PROCEDURE_UTILS_H_

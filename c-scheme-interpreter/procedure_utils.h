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

#endif // __PROCEDURE_UTILS_H_

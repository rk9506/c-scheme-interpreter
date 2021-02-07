#ifndef __EVAL_H_
#define __EVAL_H_

#include "syntax.h"
#include "env.h"
#include "heap.h"
#include "procedure_utils.h"
#include "registers.h"

void initialise_env();
void initialise_eval();

void free_regs();

SchemeAtom *get_root();
void set_root(SchemeAtom *new_root);

SchemeAtom *eval_exp(SchemeAtom *exp);

void save(SchemeAtom *val);
SchemeAtom *restore();

#endif // __EVAL_H_

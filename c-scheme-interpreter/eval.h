#ifndef __EVAL_H_
#define __EVAL_H_

#include "syntax.h"
#include "env.h"
#include "heap.h"

void initialise_regs();
void initialise_env();
void initialise_eval();

void free_regs();

SchemeAtom *eval_exp(SchemeAtom *exp);

#endif // __EVAL_H_

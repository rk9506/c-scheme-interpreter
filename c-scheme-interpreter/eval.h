#ifndef __EVAL_H_
#define __EVAL_H_

#include "syntax.h"
#include "env.h"
#include "stack.h"

void initialise_regs();
void initialise_env();
void initialise_eval();

void free_regs();

SchemeListElem *eval_exp(SchemeListElem *exp);

#endif // __EVAL_H_

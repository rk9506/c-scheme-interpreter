#ifndef __EVAL_H_
#define __EVAL_H_

#include "syntax.h"
#include "env.h"

void initialise_regs();
void initialise_env();

SchemeListElem *eval_exp(SchemeListElem *exp);

#endif // __EVAL_H_

#ifndef __EVAL_H_
#define __EVAL_H_

#include "syntax.h"

void initialise_regs();

SchemeListElem *eval_exp(SchemeListElem *exp);

#endif // __EVAL_H_

#include "eval.h"

typedef struct
{
    SchemeListElem *exp;
    // Environment *env;
    SchemeListElem *val;
    // SchemeProcedure *proc;
    // SchemeList *argl;
    // void (*continue)();
    // SchemeList *unev;
} Registers;

static Registers *regs;

void eval_dispatch();
void ev_self_eval();

void initialise_regs()
{
    regs = malloc(sizeof(Registers));
}

SchemeListElem *eval_exp(SchemeListElem *exp)
{
    initialise_regs();
    regs->exp = exp;
    eval_dispatch();
    return regs->val;
}

void eval_dispatch()
{
    if (is_self_evaluating(regs->exp))
    {
        ev_self_eval();
    }
}

void ev_self_eval()
{
    regs->val = regs->exp;
}

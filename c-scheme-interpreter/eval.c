#include "eval.h"

typedef struct
{
    SchemeListElem *exp;
    struct Environment *env;
    SchemeListElem *val;
    // SchemeProcedure *proc;
    // SchemeList *argl;
    // void (*continue)();
    struct SchemeList *unev;
} Registers;

static Registers *regs;

void eval_dispatch();
void ev_self_eval();
void ev_variable();
void ev_quoted();
void ev_definition();
void ev_assignment();
void ev_begin();
void ev_sequence();

// Used in repl.c
void initialise_regs()
{
    regs = malloc(sizeof(Registers));
    regs->exp = NULL;
    regs->env = NULL;
    regs->val = NULL;
    regs->unev = NULL;
}

void initialise_env()
{
    regs->env = get_global_environment();
}

void initialise_eval()
{
    setup_global_environment();
    initialise_regs();
    initialise_env();
}

void free_regs()
{
    if (regs->exp != NULL) free_elem(regs->exp);
    if (regs->val != NULL) free_elem(regs->val);
    if (regs->unev != NULL) free_list(regs->unev);
}

SchemeListElem *eval_exp(SchemeListElem *exp)
{
    initialise_eval();
    regs->exp = exp;
    eval_dispatch();
    return regs->val;
}

void eval_dispatch()
{
    if (is_self_evaluating(regs->exp))
    {
        ev_self_eval();
    } else if (is_variable(regs->exp))
    {
        ev_variable();
    } else if (is_quoted(regs->exp))
    {
        ev_quoted();
    } else if (is_definition(regs->exp))
    {
        ev_definition();
    } else if (is_assignment(regs->exp))
    {
        ev_assignment();
    } else if (is_begin(regs->exp))
    {
        ev_begin();
    }
}

void ev_self_eval()
{
    regs->val = regs->exp;
}

void ev_variable()
{
    regs->val = lookup_variable_value(regs->exp->atom->val->sym, regs->env);
}

void ev_quoted()
{
    regs->val = text_of_quotation(regs->exp);
}

void ev_definition()
{
    SchemeListElem *var = definition_variable(regs->exp);

    regs->exp = definition_value(regs->exp);
    struct Environment *env = regs->env;
    eval_dispatch();
    regs->env = env;
    define_variable(var->atom->val->sym, regs->val, regs->env);
    regs->val = make_symbol("ok");
}

void ev_assignment()
{
    SchemeListElem *var = assignment_variable(regs->exp);

    regs->exp = assignment_value(regs->exp);
    struct Environment *env = regs->env;
    eval_dispatch();
    regs->env = env;
    set_variable_value(var->atom->val->sym, regs->val, regs->env);
    regs->val = make_symbol("ok");
}

void ev_begin()
{
    regs->unev = begin_actions(regs->exp);

    ev_sequence();
}

void ev_sequence()
{
    regs->exp = first_exp(regs->unev);

    if (is_last_exp(regs->unev))
    {
        eval_dispatch();
        return;
    }

    struct SchemeList *unev = regs->unev;
    struct Environment *env = regs->env;

    eval_dispatch();

    regs->env = env;
    regs->unev = rest_exps(unev);

    ev_sequence();
}

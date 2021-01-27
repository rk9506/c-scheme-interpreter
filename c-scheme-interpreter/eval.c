#include "eval.h"

typedef struct
{
    SchemeListElem *exp;
    struct Environment *env;
    SchemeListElem *val;
    SchemeListElem *proc;
    struct SchemeList *argl;
    // void (*continue)();
    struct SchemeList *unev;
} Registers;

static Registers *regs;

void eval_dispatch();
void ev_self_eval();
void ev_variable();
void ev_quoted();
void ev_lambda();
void ev_definition();
void ev_assignment();
void ev_begin();
void ev_sequence();

void ev_application();
void ev_appl_operand_loop();
void apply_dispatch();
void primitive_apply();

// Used in repl.c
void initialise_regs()
{
    regs = malloc(sizeof(Registers));
    regs->exp = NULL;
    regs->env = NULL;
    regs->val = NULL;
    regs->unev = NULL;
    regs->argl = NULL;
    regs->proc = NULL;
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
    } else if (is_assignment(regs->exp))
    {
        ev_assignment();
    } else if (is_definition(regs->exp))
    {
        ev_definition();
    } else if (is_lambda(regs->exp))
    {
        ev_lambda();
    } else if (is_begin(regs->exp))
    {
        ev_begin();
    } else if (is_application(regs->exp))
    {
        ev_application();
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

void ev_lambda()
{
    regs->unev = lambda_parameters(regs->exp);
    regs->val = make_procedure(regs->unev, lambda_body(regs->exp), regs->env);
}

struct SchemeList *empty_arglist()
{
    return NULL;
}

struct SchemeList *adjoin_arg(SchemeListElem *arg, struct SchemeList *arglist)
{
    struct SchemeList *result = make_list();

    result->car = arg;
    result->cdr = NULL;

    if (arglist == NULL) return result;

    result->cdr = arglist->cdr;
    arglist->cdr = result;

    return arglist;
}

void ev_application()
{
    struct Environment *env = regs->env;
    regs->unev = operands(regs->exp);
    struct SchemeList *unev = regs->unev;
    regs->exp = operator(regs->exp);

    eval_dispatch();

    regs->unev = unev;
    regs->env = env;
    regs->argl = empty_arglist();
    regs->proc = regs->val;

    if (has_no_operands(regs->unev))
    {
        apply_dispatch();
    } else
    {
        ev_appl_operand_loop();
    }
}

void ev_appl_operand_loop()
{
    SchemeListElem *proc = regs->proc;
    struct SchemeList *argl = regs->argl;

    regs->exp = first_operand(regs->unev);

    if (is_last_operand(regs->unev))
    {
        eval_dispatch();
        regs->argl = adjoin_arg(regs->val, argl);
        regs->proc = proc;
        apply_dispatch();
        return;
    }

    struct Environment *env = regs->env;
    struct SchemeList *unev = regs->unev;

    eval_dispatch();

    regs->unev = unev;
    regs->env = env;
    regs->argl = argl;

    regs->argl = adjoin_arg(regs->val, regs->argl);
    regs->unev = rest_operands(regs->unev);

    ev_appl_operand_loop();
}

void apply_dispatch()
{
    if (regs->proc->atom->type_tag == PRIMITIVE_PROCEDURE)
    {
        primitive_apply();
    }
}

void primitive_apply()
{
    regs->val = apply_primitive_procedure(regs->proc, regs->argl);
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

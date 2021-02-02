#include "eval.h"

typedef struct
{
    SchemeAtom *exp;
    Environment *env;
    SchemeAtom *val;
    SchemeAtom *proc;
    SchemeAtom *argl;
    // void (*continue)();
    SchemeAtom *unev;
} Registers;

static Registers *regs;

static Stack *the_stack;

void eval_dispatch();
void ev_self_eval();
void ev_variable();
void ev_quoted();
void ev_lambda();
void ev_definition();
void ev_assignment();
void ev_begin();
void ev_sequence();
void ev_if();

void ev_cond();
void cond_loop();
void cond_eval_body();

void ev_application();
void ev_appl_operand_loop();
void apply_dispatch();
void primitive_apply();
void compound_apply();

void save(void *val)
{
    push(val, the_stack);
}

void *restore()
{
    return pop(the_stack);
}

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

void initialise_stack()
{
    the_stack = make_stack();
}

void initialise_eval()
{
    initialise_heap();
    setup_global_environment();
    initialise_regs();
    initialise_env();
    initialise_stack();
}

void free_regs()
{
    if (regs->exp != NULL) free_atom(regs->exp);
    if (regs->val != NULL) free_atom(regs->val);
    if (regs->unev != NULL) free_atom(regs->unev);
}

SchemeAtom *eval_exp(SchemeAtom *exp)
{
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
    } else if (is_if(regs->exp))
    {
        ev_if();
    } else if (is_lambda(regs->exp))
    {
        ev_lambda();
    } else if (is_begin(regs->exp))
    {
        ev_begin();
    } else if (is_cond(regs->exp))
    {
        ev_cond();
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
    regs->val = lookup_variable_value(regs->exp->val->sym, regs->env);
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

SchemeAtom *empty_arglist()
{
    return NULL;
}

SchemeAtom *append_list(SchemeAtom *a, SchemeAtom *b)
{
    if (is_null_list(a)) return b;

    return cons(car(a), append_list(cdr(a), b));
}

SchemeAtom *adjoin_arg(SchemeAtom *arg, SchemeAtom *arglist)
{
    SchemeAtom *singleton = cons(arg, the_empty_list());

    return append_list(arglist, singleton);
}

void ev_application()
{
    save(regs->env);
    regs->unev = operands(regs->exp);
    save(regs->unev);
    regs->exp = operator(regs->exp);

    eval_dispatch();

    // ev-appl-did-operator
    regs->unev = restore();
    regs->env = restore();
    regs->argl = empty_arglist();
    regs->proc = regs->val;

    if (has_no_operands(regs->unev))
    {
        apply_dispatch();
    } else
    {
        save(regs->proc);
        ev_appl_operand_loop();
    }
}

void ev_appl_operand_loop()
{
    save(regs->argl);

    regs->exp = first_operand(regs->unev);

    if (is_last_operand(regs->unev))
    {
        // ev-appl-last-arg
        eval_dispatch();
        // ev-appl-accum-last-arg
        regs->argl = restore();
        regs->argl = adjoin_arg(regs->val, regs->argl);
        regs->proc = restore();
        apply_dispatch();
        return;
    }

    save(regs->env);
    save(regs->unev);

    eval_dispatch();

    // ev-appl-accumulate-arg
    regs->unev = restore();
    regs->env = restore();
    regs->argl = restore();

    regs->argl = adjoin_arg(regs->val, regs->argl);
    regs->unev = rest_operands(regs->unev);

    ev_appl_operand_loop();
}

void apply_dispatch()
{
    TypeTag type_tag = regs->proc->type_tag;

    if (type_tag == PRIMITIVE_PROCEDURE)
    {
        primitive_apply();
    } else if (type_tag == SCHEME_PROCEDURE)
    {
        compound_apply();
    } else
    {
        printf("Invalid procedure\n");
        regs->val = NULL;
    }
}

void primitive_apply()
{
    regs->val = apply_primitive_procedure(regs->proc, regs->argl);
}

void compound_apply()
{
    regs->unev = regs->proc->val->proc->parameters;
    regs->env = extend_environment(regs->unev, regs->argl, regs->proc->val->proc->env);
    regs->unev = regs->proc->val->proc->body;
    ev_sequence();
}

void ev_definition()
{
    SchemeAtom *var = definition_variable(regs->exp);

    regs->exp = definition_value(regs->exp);
    Environment *env = regs->env;
    eval_dispatch();
    regs->env = env;
    define_variable(var->val->sym, regs->val, regs->env);
    regs->val = make_symbol("ok");
}

void ev_assignment()
{
    SchemeAtom *var = assignment_variable(regs->exp);

    regs->exp = assignment_value(regs->exp);
    Environment *env = regs->env;
    eval_dispatch();
    regs->env = env;
    set_variable_value(var->val->sym, regs->val, regs->env);
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

    SchemeAtom *unev = regs->unev;
    Environment *env = regs->env;

    eval_dispatch();

    regs->env = env;
    regs->unev = rest_exps(unev);

    ev_sequence();
}

bool is_true(SchemeAtom *val)
{
    if (is_boolean(val))
    {
        return val->val->boolean;
    } else
    {
        return true;
    }
}

void ev_if()
{
    save(regs->exp);
    save(regs->env);

    regs->exp = if_predicate(regs->exp);

    eval_dispatch();

    // ev-if-decide
    regs->env = restore();
    regs->exp = restore();

    if (is_true(regs->val))
    {
        // ev-if-consequent
        regs->exp = if_consequent(regs->exp);
    } else
    {
        regs->exp = if_alternative(regs->exp);
    }

    eval_dispatch();
}

void ev_cond()
{
    regs->unev = cond_clauses(regs->exp);
    cond_loop();
}

void cond_loop()
{
    if (is_cond_empty_clauses(regs->unev))
    {
        return;
    }

    regs->exp = cond_first_clause(regs->unev);

    if (is_cond_else_clause(regs->exp))
    {
        cond_eval_body();
        return;
    }

    regs->exp = cond_predicate(regs->exp);
    save(regs->unev);
    save(regs->exp);
    save(regs->env);

    eval_dispatch();

    // cond-decide
    regs->env = restore();
    regs->exp = restore();
    regs->unev = restore();

    if (is_true(regs->val))
    {
        cond_eval_body();
        return;
    }

    regs->unev = cond_rest_clauses(regs->unev);
    cond_loop();
}

void cond_eval_body()
{
    save(regs->unev);
    save(regs->exp);
    save(regs->env);

    regs->unev = cond_first_clause(regs->unev);
    regs->unev = cond_actions(regs->unev);

    ev_sequence();

    // cond-after-body
    regs->env = restore();
    regs->exp = restore();
    regs->unev = restore();
}

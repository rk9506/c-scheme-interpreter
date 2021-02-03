#include "syntax.h"

bool is_self_evaluating(SchemeAtom *atom)
{
    if (atom != NULL)
    {
        TypeTag type_tag = atom->type_tag;

        return type_tag == SCHEME_STRING
            || type_tag == SCHEME_NUMBER
            || type_tag == SCHEME_BOOLEAN;
    }

    return false;
}

bool is_variable(SchemeAtom *atom)
{
    if (atom != NULL)
    {
        return atom->type_tag == SCHEME_SYMBOL;
    }

    return false;
}

bool is_tagged_list(SchemeAtom *atom, char *tag)
{
    SchemeAtom *car_atom = car(atom);

    if (atom != NULL && is_symbol(car_atom))
    {
        return strcmp(car_atom->val->sym, tag) == 0;
    }

    return false;
}

bool is_quoted(SchemeAtom *exp)
{
    return is_tagged_list(exp, "quote");
}

SchemeAtom *text_of_quotation(SchemeAtom *exp)
{
    return car(cdr(exp));
}

bool is_lambda(SchemeAtom *exp)
{
    return is_tagged_list(exp, "lambda");
}

SchemeAtom *lambda_parameters(SchemeAtom *exp)
{
    return car(cdr(exp));
}

SchemeAtom *lambda_body(SchemeAtom *exp)
{
    return cdr(cdr(exp));
}

SchemeAtom *make_lambda(SchemeAtom *parameters, SchemeAtom *body)
{
    return cons(make_symbol("lambda"), cons(parameters, body));
}

bool is_definition(SchemeAtom *exp)
{
    return is_tagged_list(exp, "define");
}

SchemeAtom *definition_variable(SchemeAtom *exp)
{
    SchemeAtom *var = car(cdr(exp));

    if (is_variable(var))
    {
        return var;
    } else
    {
        // exp is using the syntactic sugar (define (f x) ...)
        return car(var);
    }
}

SchemeAtom *definition_value(SchemeAtom *exp)
{
    SchemeAtom *var = car(cdr(exp));

    if (is_variable(var))
    {
        return car(cdr(cdr(exp)));
    }
    {
        return make_lambda(cdr(var), cdr(cdr(exp)));
    }
}

bool is_assignment(SchemeAtom *exp)
{
    return is_tagged_list(exp, "set!");
}

SchemeAtom *assignment_variable(SchemeAtom *exp)
{
    return car(cdr(exp));
}

SchemeAtom *assignment_value(SchemeAtom *exp)
{
    return car(cdr(cdr(exp)));
}

bool is_begin(SchemeAtom *exp)
{
    return is_tagged_list(exp, "begin");
}

SchemeAtom *begin_actions(SchemeAtom *exp)
{
    return cdr(exp);
}

SchemeAtom *first_exp(SchemeAtom *exps)
{
    return car(exps);
}

SchemeAtom *rest_exps(SchemeAtom *exps)
{
    return cdr(exps);
}

bool is_last_exp(SchemeAtom *exps)
{
    return is_null_list(cdr(exps));
}

bool is_application(SchemeAtom *exp)
{
    return is_pair(exp);
}

SchemeAtom *operator(SchemeAtom *exp)
{
    return car(exp);
}

SchemeAtom *operands(SchemeAtom *exp)
{
    return cdr(exp);
}

bool has_no_operands(SchemeAtom *operands)
{
    return is_null_list(operands);
}

bool is_last_operand(SchemeAtom *operands)
{
    return is_null_list(cdr(operands));
}

SchemeAtom *first_operand(SchemeAtom *operands)
{
    return car(operands);
}

SchemeAtom *rest_operands(SchemeAtom *operands)
{
    return cdr(operands);
}

bool is_if(SchemeAtom *exp)
{
    return is_tagged_list(exp, "if");
}

SchemeAtom *if_predicate(SchemeAtom *exp)
{
    return car(cdr(exp));
}

SchemeAtom *if_consequent(SchemeAtom *exp)
{
    return car(cdr(cdr(exp)));
}

SchemeAtom *if_alternative(SchemeAtom *exp)
{
    SchemeAtom *cdddr = cdr(cdr(cdr(exp)));

    if (!is_null_list(cdddr))
    {
        return car(cdddr);
    } else
    {
        return make_symbol("false");
    }
}

bool is_cond(SchemeAtom *exp)
{
    return is_tagged_list(exp, "cond");
}

SchemeAtom *cond_clauses(SchemeAtom *exp)
{
    return cdr(exp);
}

bool is_cond_else_clause(SchemeAtom *clause)
{
    SchemeAtom *pred = car(clause);

    return is_symbol(pred) && strcmp(pred->val->sym, "else") == 0;
}

SchemeAtom *cond_predicate(SchemeAtom *clause)
{
    return car(clause);
}

SchemeAtom *cond_actions(SchemeAtom *clause)
{
    return cdr(clause);
}

SchemeAtom *cond_first_clause(SchemeAtom *clauses)
{
    return car(clauses);
}

SchemeAtom *cond_rest_clauses(SchemeAtom *clauses)
{
    return cdr(clauses);
}

bool is_cond_empty_clauses(SchemeAtom *clauses)
{
    return is_null_list(clauses);
}

bool is_let(SchemeAtom *exp)
{
    return is_tagged_list(exp, "let");
}

SchemeAtom *let_binding_var(SchemeAtom *binding)
{
    return car(binding);
}

SchemeAtom *let_binding_exp(SchemeAtom *binding)
{
    return car(cdr(binding));
}

SchemeAtom *let_vars(SchemeAtom *bindings)
{
    if (is_null_list(bindings))
    {
        return the_empty_list();
    } else
    {
        return cons(let_binding_var(car(bindings)), let_vars(cdr(bindings)));
    }
}

SchemeAtom *let_exps(SchemeAtom *bindings)
{
    if (is_null_list(bindings))
    {
        return the_empty_list();
    } else
    {
        return cons(let_binding_exp(car(bindings)), let_exps(cdr(bindings)));
    }
}

SchemeAtom *let_bindings(SchemeAtom *exp)
{
    return car(cdr(exp));
}

SchemeAtom *let_body(SchemeAtom *exp)
{
    return cdr(cdr(exp));
}

SchemeAtom *make_combination(SchemeAtom *operator, SchemeAtom *operands)
{
    return cons(operator, operands);
}

SchemeAtom *let_to_combination(SchemeAtom *exp)
{
    SchemeAtom *bindings = let_bindings(exp);
    SchemeAtom *op = make_lambda(let_vars(bindings), let_body(exp));

    return make_combination(op, let_exps(bindings));
}

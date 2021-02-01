#include "syntax.h"

bool is_self_evaluating(SchemeListElem *elem)
{
    SchemeAtom *atom = elem->atom;

    if (atom != NULL)
    {
        TypeTag type_tag = atom->type_tag;

        return type_tag == SCHEME_STRING
            || type_tag == SCHEME_NUMBER
            || type_tag == SCHEME_BOOLEAN;
    }

    return false;
}

bool is_variable(SchemeListElem *elem)
{
    SchemeAtom *atom = elem->atom;

    if (atom != NULL)
    {
        return atom->type_tag == SCHEME_SYMBOL;
    }

    return false;
}

bool is_tagged_list(SchemeListElem *elem, char *tag)
{
    struct SchemeList *list = elem->list;

    if (list != NULL)
    {
        SchemeAtom *atom = list->car->atom;

        if (atom != NULL)
        {
            return strcmp(atom->val->sym, tag) == 0;
        }
    }

    return false;
}

bool is_quoted(SchemeListElem *exp)
{
    return is_tagged_list(exp, "quote");
}

SchemeListElem *text_of_quotation(SchemeListElem *exp)
{
    return exp->list->cdr->car;
}

bool is_lambda(SchemeListElem *exp)
{
    return is_tagged_list(exp, "lambda");
}

struct SchemeList *lambda_parameters(SchemeListElem *exp)
{
    return exp->list->cdr->car->list;
}

struct SchemeList *lambda_body(SchemeListElem *exp)
{
    return exp->list->cdr->cdr;
}

SchemeListElem *make_lambda(struct SchemeList *parameters, struct SchemeList *body)
{
    SchemeListElem *result = make_elem();
    result->list = make_list();
    result->list->car = make_symbol("lambda");

    struct SchemeList *contents = make_list();
    contents->car->list = parameters;
    contents->cdr = body;

    result->list->cdr = contents;

    return result;
}

bool is_definition(SchemeListElem *exp)
{
    return is_tagged_list(exp, "define");
}

SchemeListElem *definition_variable(SchemeListElem *exp)
{
    SchemeListElem *var = exp->list->cdr->car;
    if (is_variable(var))
    {
        return var;
    } else
    {
        // exp is using the syntactic sugar (define (f x) ...)
        return var->list->car;
    }
}

SchemeListElem *definition_value(SchemeListElem *exp)
{
    SchemeListElem *var = exp->list->cdr->car;

    if (is_variable(var))
    {
        return exp->list->cdr->cdr->car;
    }
    {
        return make_lambda(var->list->cdr, exp->list->cdr->cdr);
    }
}

bool is_assignment(SchemeListElem *exp)
{
    return is_tagged_list(exp, "set!");
}

SchemeListElem *assignment_variable(SchemeListElem *exp)
{
    return exp->list->cdr->car;
}

SchemeListElem *assignment_value(SchemeListElem *exp)
{
    return exp->list->cdr->cdr->car;
}

bool is_begin(SchemeListElem *exp)
{
    return is_tagged_list(exp, "begin");
}

struct SchemeList *begin_actions(SchemeListElem *exp)
{
    return exp->list->cdr;
}

SchemeListElem *first_exp(struct SchemeList *exps)
{
    return exps->car;
}

struct SchemeList *rest_exps(struct SchemeList *exps)
{
    return exps->cdr;
}

bool is_last_exp(struct SchemeList *exps)
{
    return exps->cdr == NULL;
}

bool is_application(SchemeListElem *exp)
{
    return exp->list != NULL;
}

SchemeListElem *operator(SchemeListElem *exp)
{
    return exp->list->car;
}

struct SchemeList *operands(SchemeListElem *exp)
{
    return exp->list->cdr;
}

bool has_no_operands(struct SchemeList *operands)
{
    return operands == NULL;
}

bool is_last_operand(struct SchemeList *operands)
{
    return operands->cdr == NULL;
}

SchemeListElem *first_operand(struct SchemeList *operands)
{
    return operands->car;
}

struct SchemeList *rest_operands(struct SchemeList *operands)
{
    return operands->cdr;
}

bool is_if(SchemeListElem *exp)
{
    return is_tagged_list(exp, "if");
}

SchemeListElem *if_predicate(SchemeListElem *exp)
{
    return exp->list->cdr->car;
}

SchemeListElem *if_consequent(SchemeListElem *exp)
{
    return exp->list->cdr->cdr->car;
}

SchemeListElem *if_alternative(SchemeListElem *exp)
{
    struct SchemeList *cdddr = exp->list->cdr->cdr->cdr;
    if (!is_null_list(cdddr))
    {
        return cdddr->car;
    } else
    {
        return make_symbol("false");
    }
}

bool is_cond(SchemeListElem *exp)
{
    return is_tagged_list(exp, "cond");
}

struct SchemeList *cond_clauses(SchemeListElem *exp)
{
    return exp->list->cdr;
}

bool is_cond_else_clause(SchemeListElem *clause)
{
    SchemeListElem *pred = clause->list->car;

    return is_symbol(pred) && strcmp(pred->atom->val->sym, "else") == 0;
}

SchemeListElem *cond_predicate(SchemeListElem *clause)
{
    return clause->list->car;
}

struct SchemeList *cond_actions(struct SchemeList *clause)
{
    return clause->cdr;
}

SchemeListElem *cond_first_clause(struct SchemeList *clauses)
{
    return clauses->car;
}

struct SchemeList *cond_rest_clauses(struct SchemeList *clauses)
{
    return clauses->cdr;
}

bool is_cond_empty_clauses(struct SchemeList *clauses)
{
    return is_null_list(clauses);
}

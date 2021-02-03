#ifndef __SYNTAX_H_
#define __SYNTAX_H_

#include "types.h"
#include "heap.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_self_evaluating(SchemeAtom *elem);
bool is_variable(SchemeAtom *elem);

bool is_quoted(SchemeAtom *exp);
SchemeAtom *text_of_quotation(SchemeAtom *exp);

bool is_lambda(SchemeAtom *exp);
SchemeAtom *lambda_parameters(SchemeAtom *exp);
SchemeAtom *lambda_body(SchemeAtom *exp);

bool is_definition(SchemeAtom *elem);
SchemeAtom *definition_variable(SchemeAtom *exp);
SchemeAtom *definition_value(SchemeAtom *exp);

bool is_assignment(SchemeAtom *exp);
SchemeAtom *assignment_variable(SchemeAtom *exp);
SchemeAtom *assignment_value(SchemeAtom *exp);

bool is_begin(SchemeAtom *exp);
SchemeAtom *begin_actions(SchemeAtom *exp);
SchemeAtom *first_exp(SchemeAtom *exps);
SchemeAtom *rest_exps(SchemeAtom *exps);
bool is_last_exp(SchemeAtom *exps);

bool is_application(SchemeAtom *exp);
SchemeAtom *operator(SchemeAtom *exp);
SchemeAtom *operands(SchemeAtom *exp);
bool has_no_operands(SchemeAtom *operands);
bool is_last_operand(SchemeAtom *operands);
SchemeAtom *first_operand(SchemeAtom *operands);
SchemeAtom *rest_operands(SchemeAtom *operands);

bool is_if(SchemeAtom *exp);
SchemeAtom *if_predicate(SchemeAtom *exp);
SchemeAtom *if_consequent(SchemeAtom *exp);
SchemeAtom *if_alternative(SchemeAtom *exp);

bool is_cond(SchemeAtom *exp);
SchemeAtom *cond_clauses(SchemeAtom *exp);
bool is_cond_else_clause(SchemeAtom *clause);
SchemeAtom *cond_predicate(SchemeAtom *clause);
SchemeAtom *cond_actions(SchemeAtom *clause);
SchemeAtom *cond_first_clause(SchemeAtom *clauses);
SchemeAtom *cond_rest_clauses(SchemeAtom *clauses);
bool is_cond_empty_clauses(SchemeAtom *clauses);

bool is_let(SchemeAtom *exp);
SchemeAtom *let_to_combination(SchemeAtom *exp);

#endif // __SYNTAX_H_

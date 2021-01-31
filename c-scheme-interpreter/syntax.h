#ifndef __SYNTAX_H_
#define __SYNTAX_H_

#include "types.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_self_evaluating(SchemeListElem *elem);
bool is_variable(SchemeListElem *elem);

bool is_quoted(SchemeListElem *exp);
SchemeListElem *text_of_quotation(SchemeListElem *exp);

bool is_lambda(SchemeListElem *exp);
struct SchemeList *lambda_parameters(SchemeListElem *exp);
struct SchemeList *lambda_body(SchemeListElem *exp);

bool is_definition(SchemeListElem *elem);
SchemeListElem *definition_variable(SchemeListElem *exp);
SchemeListElem *definition_value(SchemeListElem *exp);

bool is_assignment(SchemeListElem *exp);
SchemeListElem *assignment_variable(SchemeListElem *exp);
SchemeListElem *assignment_value(SchemeListElem *exp);

bool is_begin(SchemeListElem *exp);
struct SchemeList *begin_actions(SchemeListElem *exp);
SchemeListElem *first_exp(struct SchemeList *exps);
struct SchemeList *rest_exps(struct SchemeList *exps);
bool is_last_exp(struct SchemeList *exps);

bool is_application(SchemeListElem *exp);
SchemeListElem *operator(SchemeListElem *exp);
struct SchemeList *operands(SchemeListElem *exp);
bool has_no_operands(struct SchemeList *operands);
bool is_last_operand(struct SchemeList *operands);
SchemeListElem *first_operand(struct SchemeList *operands);
struct SchemeList *rest_operands(struct SchemeList *operands);

bool is_if(SchemeListElem *exp);
SchemeListElem *if_predicate(SchemeListElem *exp);
SchemeListElem *if_consequent(SchemeListElem *exp);
SchemeListElem *if_alternative(SchemeListElem *exp);

#endif // __SYNTAX_H_

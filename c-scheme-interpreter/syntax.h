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

bool is_definition(SchemeListElem *elem);
SchemeListElem *definition_variable(SchemeListElem *exp);
SchemeListElem *definition_value(SchemeListElem *exp);

bool is_assignment(SchemeListElem *exp);
SchemeListElem *assignment_variable(SchemeListElem *exp);
SchemeListElem *assignment_value(SchemeListElem *exp);

#endif // __SYNTAX_H_

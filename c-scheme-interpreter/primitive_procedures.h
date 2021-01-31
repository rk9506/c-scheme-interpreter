#ifndef __PRIMITIVE_PROCEDURES_H_
#define __PRIMITIVE_PROCEDURES_H_

#include "types.h"

#include <stdio.h>
#include <stdlib.h>

SchemeListElem *apply_primitive_procedure(SchemeListElem *proc_elem, struct SchemeList *args);

SchemeListElem *primitive_add(struct SchemeList *args);
SchemeListElem *primitive_subtract(struct SchemeList *args);
SchemeListElem *primitive_multiply(struct SchemeList *args);
SchemeListElem *primitive_divide(struct SchemeList *args);
SchemeListElem *primitive_remainder(struct SchemeList *args);

SchemeListElem *primitive_number_equality(struct SchemeList *args);
SchemeListElem *primitive_lt(struct SchemeList *args);
SchemeListElem *primitive_lte(struct SchemeList *args);
SchemeListElem *primitive_gt(struct SchemeList *args);
SchemeListElem *primitive_gte(struct SchemeList *args);

SchemeListElem *primitive_and(struct SchemeList *args);
SchemeListElem *primitive_or(struct SchemeList *args);
SchemeListElem *primitive_not(struct SchemeList *args);

SchemeListElem *primitive_display(struct SchemeList *args);
SchemeListElem *primitive_newline(struct SchemeList *args);

#endif // __PRIMITIVE_PROCEDURES_H_

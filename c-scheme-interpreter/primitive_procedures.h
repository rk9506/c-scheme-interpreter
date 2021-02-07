#ifndef __PRIMITIVE_PROCEDURES_H_
#define __PRIMITIVE_PROCEDURES_H_

#include "types.h"
#include "parser.h"
#include "heap.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

SchemeAtom *primitive_temp;

SchemeAtom *apply_primitive_procedure(SchemeAtom *proc_elem, SchemeAtom *args);

SchemeAtom *primitive_add(SchemeAtom *args);
SchemeAtom *primitive_subtract(SchemeAtom *args);
SchemeAtom *primitive_multiply(SchemeAtom *args);
SchemeAtom *primitive_divide(SchemeAtom *args);
SchemeAtom *primitive_remainder(SchemeAtom *args);

SchemeAtom *primitive_number_equality(SchemeAtom *args);
SchemeAtom *primitive_lt(SchemeAtom *args);
SchemeAtom *primitive_lte(SchemeAtom *args);
SchemeAtom *primitive_gt(SchemeAtom *args);
SchemeAtom *primitive_gte(SchemeAtom *args);

SchemeAtom *primitive_and(SchemeAtom *args);
SchemeAtom *primitive_or(SchemeAtom *args);
SchemeAtom *primitive_not(SchemeAtom *args);

SchemeAtom *primitive_display(SchemeAtom *args);
SchemeAtom *primitive_newline(SchemeAtom *args);
SchemeAtom *primitive_read(SchemeAtom *args);

SchemeAtom *primitive_cons(SchemeAtom *args);
SchemeAtom *primitive_car(SchemeAtom *args);
SchemeAtom *primitive_cdr(SchemeAtom *args);
SchemeAtom *primitive_list(SchemeAtom *args);
SchemeAtom *primitive_is_null(SchemeAtom *args);
SchemeAtom *primitive_length(SchemeAtom *args);

#endif // __PRIMITIVE_PROCEDURES_H_

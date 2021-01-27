#ifndef __PRIMITIVE_PROCEDURES_H_
#define __PRIMITIVE_PROCEDURES_H_

#include "types.h"

#include <stdio.h>
#include <stdlib.h>

SchemeListElem *apply_primitive_procedure(SchemeListElem *proc_elem, struct SchemeList *args);

SchemeListElem *primitive_add(struct SchemeList *args);

#endif // __PRIMITIVE_PROCEDURES_H_

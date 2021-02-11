#ifndef __RUNTIME_H_
#define __RUNTIME_H_

#include "primitive_procedures.h"
#include "heap.h"
#include "types.h"
#include "env.h"
#include "registers.h"

#include <stdlib.h>

void save(SchemeAtom *val);
SchemeAtom *restore();
void initialise_env();
SchemeAtom *pad_list(SchemeAtom *l, int size);
void initialise_root();
SchemeAtom *get_root();
void set_root(SchemeAtom *new_root);
void initialise_runtime();
void free_regs();

#endif // __RUNTIME_H_

#ifndef __GC_H_
#define __GC_H_

#include "types.h"
#include "heap.h"
#include "registers.h"
#include "parser.h"
#include "table.h"
#include "primitive_procedures.h"
#include "hash_table.h"

#include <stdlib.h>
#include <stdbool.h>

void collect_garbage();

#endif // __GC_H_

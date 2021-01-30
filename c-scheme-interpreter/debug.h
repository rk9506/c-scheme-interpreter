#ifndef __DEBUG_H_
#define __DEBUG_H_

#include "printer.h"
#include "env.h"

#include <stdio.h>
#include <stdlib.h>

#define DEBUGGING true

void debug_log(char *message);
void debug_log_env(struct Environment *env);

#endif // __DEBUG_H_

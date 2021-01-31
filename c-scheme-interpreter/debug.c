#include "debug.h"

void debug_log(char *message)
{
    if (DEBUGGING) printf("%s\n", message);
}

void debug_log_env(struct Environment *env)
{
    if (DEBUGGING)
    {
        print_list(env->bindings);
        printf("\n");
    }
}

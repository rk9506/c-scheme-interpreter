#include "debug.h"

void debug_log(char *message)
{
    if (DEBUGGING) printf("%s\n", message);
}

void debug_log_env(SchemeAtom *env)
{
    if (DEBUGGING)
    {
        print_list(env_bindings(env));
        printf("\n");
    }
}

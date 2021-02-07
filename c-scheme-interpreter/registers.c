#include "registers.h"

// Used in repl.c
void initialise_regs()
{
    regs = malloc(sizeof(Registers));
    regs->exp = the_empty_list();
    regs->env = the_empty_list();
    regs->val = the_empty_list();
    regs->unev = the_empty_list();
    regs->argl = the_empty_list();
    regs->proc = the_empty_list();
    regs->the_stack = the_empty_list();
}

Registers *get_regs()
{
    return regs;
}

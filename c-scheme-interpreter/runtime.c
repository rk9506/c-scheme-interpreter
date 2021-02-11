#include "runtime.h"

// Pre-allocated list which will be used to hold all the registers for
// garbage collection
SchemeAtom *root;

void save(SchemeAtom *val)
{
    regs->the_stack = cons(val, regs->the_stack);
}

SchemeAtom *restore()
{
    if (is_null_list(regs->the_stack))
    {
        debug_log("Trying to restore from empty stack!");
        return NULL;
    }

    SchemeAtom *top = car(regs->the_stack);

    regs->the_stack = cdr(regs->the_stack);

    return top;
}

void initialise_env()
{
    regs->env = get_global_environment();
}

SchemeAtom *pad_list(SchemeAtom *l, int size)
{
    if (size == 0)
    {
        return l;
    } else
    {
        return pad_list(cons(the_empty_list(), l), size - 1);
    }
}

void initialise_root()
{
    root = pad_list(root, NUM_REGS);
}

SchemeAtom *get_root()
{
    return root;
}

void set_root(SchemeAtom *new_root)
{
    root = new_root;
}

void initialise_runtime()
{
    initialise_regs();
    initialise_heap();
    setup_global_environment();
    initialise_env();
    initialise_root();
}

void free_regs()
{
    if (regs->exp != NULL) free_atom(regs->exp);
    if (regs->val != NULL) free_atom(regs->val);
    if (regs->unev != NULL) free_atom(regs->unev);
}

#ifndef __EVAL_H_
#define __EVAL_H_

#include "syntax.h"
#include "env.h"
#include "heap.h"

typedef struct
{
    SchemeAtom *exp;
    SchemeAtom *env;
    SchemeAtom *val;
    SchemeAtom *proc;
    SchemeAtom *argl;
    // void (*continue)();
    SchemeAtom *unev;
    SchemeAtom *the_stack;
    SchemeAtom *temp;
} Registers;

void initialise_regs();
void initialise_env();
void initialise_eval();

void free_regs();
Registers *get_regs();

SchemeAtom *get_root();
void set_root(SchemeAtom *new_root);

SchemeAtom *eval_exp(SchemeAtom *exp);

void save(SchemeAtom *val);
SchemeAtom *restore();

#endif // __EVAL_H_

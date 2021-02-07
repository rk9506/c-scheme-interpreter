#ifndef __REGISTERS_H_
#define __REGISTERS_H_

#include "types.h"

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

Registers *regs;

void initialise_regs();

#endif // __REGISTERS_H_

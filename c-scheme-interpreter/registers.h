#ifndef __REGISTERS_H_
#define __REGISTERS_H_

#include "types.h"

// 8 registers here + parsing register in parser.c + entry register in table.c
// + primitive_temp in primitive_procedures.c
#define NUM_REGS 11

typedef struct
{
    SchemeAtom *exp;
    SchemeAtom *env;
    SchemeAtom *val;
    SchemeAtom *proc;
    SchemeAtom *argl;
    SchemeAtom *unev;
    SchemeAtom *the_stack;
    SchemeAtom *temp;
    void *cont;
    void *compapp;
    bool flag;
} Registers;

Registers *regs;

void initialise_regs();

#endif // __REGISTERS_H_

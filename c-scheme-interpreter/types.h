#ifndef __TYPES_H_
#define __TYPES_H_

#include <stdbool.h>
#include <stdlib.h>

typedef char* SchemeString;
typedef float SchemeNumber;
typedef bool SchemeBoolean;
typedef char* SchemeSymbol;

// A SchemePairPointer is an index into the_cars/the_cdrs, i.e. it is
// a pointer within our "Scheme virtual machine", as opposed to a C pointer
typedef unsigned int SchemePairPointer;

typedef enum { SCHEME_STRING, SCHEME_NUMBER, SCHEME_BOOLEAN, SCHEME_SYMBOL, SCHEME_PROCEDURE, PRIMITIVE_PROCEDURE, SCHEME_PAIR_POINTER } TypeTag;

typedef struct SchemeAtom SchemeProcedure;

// A primitive procedure is a function which takes a pointer
// to a list of arguments, and returns a result as a SchemeAtom
typedef struct SchemeAtom *(*PrimitiveProcedure)(struct SchemeAtom*);

typedef union
{
    SchemeString str;
    SchemeNumber num;
    SchemeBoolean boolean;
    SchemeSymbol sym;
    SchemePairPointer pair;
    SchemeProcedure *proc;
    PrimitiveProcedure primitive_proc;
} SchemePrimitive;

typedef struct SchemeAtom
{
    TypeTag type_tag;
    SchemePrimitive *val;
} SchemeAtom;

SchemeAtom *the_empty_list();
bool is_null_list(SchemeAtom *list);

SchemeAtom *make_atom();
SchemePrimitive *make_primitive();
SchemeAtom *make_number(float num);
SchemeAtom *make_boolean(bool boolean);
SchemeAtom *make_symbol(char *sym);
SchemeAtom *make_pair(SchemePairPointer ptr);
SchemeAtom *make_primitive_procedure(PrimitiveProcedure proc);

void free_atom(SchemeAtom *atom);

bool is_symbol(SchemeAtom *atom);
bool is_number(SchemeAtom *atom);
bool is_string(SchemeAtom *atom);
bool is_pair(SchemeAtom *atom);
bool is_boolean(SchemeAtom *atom);

unsigned int list_length(SchemeAtom *l);

#endif // __TYPES_H_

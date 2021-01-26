#ifndef __TYPES_H_
#define __TYPES_H_

#include <stdbool.h>
#include <stdlib.h>

struct SchemeList;

typedef char* SchemeString;
typedef float SchemeNumber;
typedef bool SchemeBoolean;
typedef char* SchemeSymbol;

// A SchemePairPointer is an index into the_cars/the_cdrs, i.e. it is
// a pointer within our "Scheme virtual machine", as opposed to a C pointer
typedef unsigned int SchemePairPointer;

typedef enum { SCHEME_STRING, SCHEME_NUMBER, SCHEME_BOOLEAN, SCHEME_SYMBOL, /* SCHEME_PAIR_POINTER */ } TypeTag;

typedef union
{
    SchemeString str;
    SchemeNumber num;
    SchemeBoolean boolean;
    SchemeSymbol sym;
    SchemePairPointer pair;
} SchemePrimitive;

typedef struct
{
    TypeTag type_tag;
    SchemePrimitive *val;
} SchemeAtom;

typedef struct { SchemeAtom *atom; struct SchemeList *list; } SchemeListElem;
struct SchemeList { SchemeListElem *car; struct SchemeList *cdr; };

struct SchemeList *make_list();
SchemeAtom *make_atom();
SchemePrimitive *make_primitive();
SchemeListElem *make_symbol(char *sym);

unsigned int list_length(struct SchemeList *l);

#endif // __TYPES_H_

#ifndef __TYPES_H_
#define __TYPES_H_

#include <stdbool.h>
#include <stdlib.h>

struct SchemeList;

typedef char* SchemeString;
typedef float SchemeNumber;
typedef bool SchemeBoolean;
typedef char* SchemeSymbol;

typedef enum { SCHEME_STRING, SCHEME_NUMBER, SCHEME_BOOLEAN, SCHEME_SYMBOL } TypeTag;

typedef union
{
    SchemeString str;
    SchemeNumber num;
    SchemeBoolean boolean;
    SchemeSymbol sym;
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

#endif // __TYPES_H_

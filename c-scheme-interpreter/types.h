#ifndef __TYPES_H_
#define __TYPES_H_

#include <stdbool.h>
#include <stdlib.h>

struct SchemeList;

// Dumb hack to get around C's dumb rules regarding
// mutually recursive type declarations
struct scheme_list_elem_t;

typedef char* SchemeString;
typedef float SchemeNumber;
typedef bool SchemeBoolean;
typedef char* SchemeSymbol;

// A SchemePairPointer is an index into the_cars/the_cdrs, i.e. it is
// a pointer within our "Scheme virtual machine", as opposed to a C pointer
typedef unsigned int SchemePairPointer;

typedef enum { SCHEME_STRING, SCHEME_NUMBER, SCHEME_BOOLEAN, SCHEME_SYMBOL, SCHEME_PROCEDURE, PRIMITIVE_PROCEDURE /* SCHEME_PAIR_POINTER */ } TypeTag;

typedef struct
{
    struct SchemeList *parameters;
    struct SchemeList *body;
    struct Environment *env;
} SchemeProcedure;

// A primitive procedure is a function which takes a pointer
// to a SchemeList of arguments, and returns a result as a SchemeListElem
typedef struct scheme_list_elem_t *(*PrimitiveProcedure)(struct SchemeList*);

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

typedef struct
{
    TypeTag type_tag;
    SchemePrimitive *val;
} SchemeAtom;

typedef struct scheme_list_elem_t { SchemeAtom *atom; struct SchemeList *list; } SchemeListElem;
struct SchemeList { SchemeListElem *car; struct SchemeList *cdr; };

struct SchemeList *the_empty_list();
bool is_null_list(struct SchemeList *list);

SchemeListElem *make_elem();
struct SchemeList *make_list();
SchemeAtom *make_atom();
SchemePrimitive *make_primitive();
SchemeListElem *make_number(float num);
SchemeListElem *make_boolean(bool boolean);
SchemeListElem *make_symbol(char *sym);
SchemeListElem *make_procedure(struct SchemeList *parameters,
                               struct SchemeList *body,
                               struct Environment *env);
SchemeListElem *make_primitive_procedure(PrimitiveProcedure proc);

void free_list(struct SchemeList *list);
void free_elem(SchemeListElem *elem);
void free_atom(SchemeAtom *atom);

unsigned int list_length(struct SchemeList *l);

#endif // __TYPES_H_

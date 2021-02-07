#include "types.h"

SchemeAtom *the_empty_list()
{
    return NULL;
}

bool is_null_list(SchemeAtom *list)
{
    return list == NULL;
}

SchemeAtom *make_atom()
{
    return malloc(sizeof(SchemeAtom));
}

void free_atom(SchemeAtom *atom)
{
    if (atom == NULL) return;

    free(atom);

    if (atom->type_tag == SCHEME_PROCEDURE)
    {
        free(atom->val->proc);
    }

    if (atom->val != NULL)
    {
        free(atom->val);
    }
}

SchemePrimitive *make_primitive()
{
    return malloc(sizeof(SchemePrimitive));
}

SchemeAtom *make_number(float num)
{
    SchemeAtom *atom = make_atom();

    atom->type_tag = SCHEME_NUMBER;
    atom->val = make_primitive();
    atom->val->num = num;

    return atom;
}

SchemeAtom *make_boolean(bool boolean)
{
    SchemeAtom *atom = make_atom();

    atom->type_tag = SCHEME_BOOLEAN;
    atom->val = make_primitive();
    atom->val->boolean = boolean;

    return atom;
}


SchemeAtom *make_symbol(char *sym)
{
    SchemeAtom *atom = make_atom();

    atom->type_tag = SCHEME_SYMBOL;
    atom->val = make_primitive();
    atom->val->sym = sym;

    return atom;
}

SchemeAtom *make_pair(SchemePairPointer ptr)
{
    SchemeAtom *atom = make_atom();

    atom->type_tag = SCHEME_PAIR_POINTER;
    atom->val = make_primitive();
    atom->val->pair = ptr;

    return atom;
}

SchemeAtom *make_primitive_procedure(PrimitiveProcedure proc)
{
    SchemeAtom *atom = make_atom();

    atom->type_tag = PRIMITIVE_PROCEDURE;
    atom->val = make_primitive();
    atom->val->primitive_proc = proc;

    return atom;
}

bool is_symbol(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_SYMBOL;
}

bool is_number(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_NUMBER;
}

bool is_string(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_STRING;
}

bool is_pair(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_PAIR_POINTER;
}

bool is_boolean(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_BOOLEAN;
}

bool is_compound_procedure(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_PROCEDURE;
}

bool symbol_eq_str(SchemeAtom *symbol, char *str)
{
    return is_symbol(symbol) && strcmp(symbol->val->sym, str) == 0;
}

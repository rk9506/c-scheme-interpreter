#include "heap.h"

void initialise_heap()
{
    the_cars = calloc(HEAP_SIZE, sizeof(SchemeAtom*));
    the_cdrs = calloc(HEAP_SIZE, sizeof(SchemeAtom*));
    free_ptr = 0;
}

SchemeAtom *car(SchemeAtom *pair)
{
    if (!is_pair(pair))
    {
        printf("Trying to car a non-pair!\n");
        print_elem(pair);
        printf("\n");
        return NULL;
    }

    SchemePairPointer p = pair->val->pair;

    return the_cars[p];
}

SchemeAtom *cdr(SchemeAtom *pair)
{
    if (!is_pair(pair))
    {
        printf("Trying to cdr a non-pair!\n");
        print_elem(pair);
        printf("\n");
        return NULL;
    }

    SchemePairPointer p = pair->val->pair;

    return the_cdrs[p];
}

void set_car(SchemeAtom *pair, SchemeAtom *atom)
{
    if (!is_pair(pair))
    {
        printf("Trying to set_car on a non-pair!\n");
        print_atom(pair);
        return;
    }

    SchemePairPointer p = pair->val->pair;
    the_cars[p] = atom;
}

void set_cdr(SchemeAtom *pair, SchemeAtom *atom)
{
    if (!is_pair(pair))
    {
        printf("Trying to set_cdr on a non-pair!\n");
        print_atom(pair);
        return;
    }

    SchemePairPointer p = pair->val->pair;
    the_cdrs[p] = atom;
}

SchemeAtom *cons(SchemeAtom *a, SchemeAtom *b)
{
    if (free_ptr == HEAP_SIZE)
    {
        debug_log("Performing garbage collection...\n");
        perform_gc();
    }

    SchemeAtom *atom = make_atom();
    SchemePrimitive *prim = make_primitive();
    atom->val = prim;
    atom->type_tag = SCHEME_PAIR_POINTER;
    atom->val->pair = free_ptr;

    the_cars[free_ptr] = a;
    the_cdrs[free_ptr] = b;
    free_ptr++;

    return atom;
}

SchemePairPointer get_free_ptr()
{
    return free_ptr;
}

void set_free_ptr(SchemePairPointer new_free)
{
    free_ptr = new_free;
}

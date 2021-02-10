#include "heap.h"

void initialise_cdrs();

void initialise_heap()
{
    the_cars = calloc(HEAP_SIZE, sizeof(SchemeAtom*));
    the_cdrs = calloc(HEAP_SIZE, sizeof(SchemeAtom*));

    initialise_cdrs();
    free_ptr = 0;
}

// Initialise the cdrs such that each pair links to the next
// consecutive pair. We do this so that we can use a pointer to
// the first pair as our "free list" for consing.
void initialise_cdrs()
{
    int i;
    for (i = 0; i < HEAP_SIZE - 1; i++)
    {
        the_cdrs[i] = make_pair(i + 1);
    }
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
    SchemeAtom *free_cdr = the_cdrs[free_ptr];

    if (is_null_list(free_cdr))
    {
        perform_gc();
        free_cdr = the_cdrs[free_ptr];
    }

    if (is_null_list(free_cdr))
    {
        throw_exception("That's all folks: we've run out of memory!");
    }

    SchemeAtom *atom = make_pair(free_ptr);

    the_cars[free_ptr] = a;
    the_cdrs[free_ptr] = b;

    free_ptr = free_cdr->val->pair;
    // free_atom(free_cdr);

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

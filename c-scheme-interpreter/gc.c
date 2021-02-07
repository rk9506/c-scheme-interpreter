#include "gc.h"

#define BROKEN_HEART_TAG -1

SchemeAtom **new_cars;
SchemeAtom **new_cdrs;

SchemeAtom *old;
SchemeAtom *new;

SchemeAtom *oldcr;

SchemePairPointer scan;

void relocate_old_result_in_new();
void gc_loop();
void gc_flip();
void debug_dump_heap(SchemeAtom **the_cars, SchemeAtom **the_cdrs);

SchemeAtom *get_populated_root()
{
    SchemeAtom *root = get_root();

    SchemeAtom *current = root;

    // This is so ugly...
    set_car(current, regs->exp);
    current = cdr(current);

    set_car(current, regs->env);
    current = cdr(current);

    set_car(current, regs->val);
    current = cdr(current);

    set_car(current, regs->proc);
    current = cdr(current);

    set_car(current, regs->argl);
    current = cdr(current);

    set_car(current, regs->unev);
    current = cdr(current);

    set_car(current, regs->the_stack);
    current = cdr(current);

    set_car(current, parsing);
    current = cdr(current);

    set_car(current, entry);
    current = cdr(current);

    set_car(current, primitive_temp);

    return root;
}

void initialise_new_memory()
{
    new_cars = calloc(HEAP_SIZE, sizeof(SchemeAtom*));
    new_cdrs = calloc(HEAP_SIZE, sizeof(SchemeAtom*));
}

void collect_garbage()
{
    initialise_new_memory();
    debug_log("Old heap: \n");
    debug_dump_heap(the_cars, the_cdrs);

    // begin-garbage-collection
    free_ptr = 0;
    scan = 0;
    old = get_populated_root();

    relocate_old_result_in_new();

    // reassign-root
    set_root(new);
    gc_loop();
}

void gc_loop()
{
    if (scan > free_ptr)
    {
        gc_flip();
        debug_dump_heap(the_cars, the_cdrs);
        return;
    }

    old = new_cars[scan];

    relocate_old_result_in_new();

    // update-car
    new_cars[scan] = new;
    old = new_cdrs[scan];
    relocate_old_result_in_new();

    // update-cdr
    new_cdrs[scan] = new;
    scan++;
    gc_loop();
}

void sweep_garbage(SchemeAtom **vec)
{
    int i;
    SchemeAtom *curr;

    for (i = 0; i < HEAP_SIZE; i++)
    {
        curr = vec[i];
        if (curr != NULL && curr != (SchemeAtom*) BROKEN_HEART_TAG)
        {
            free_atom(curr);
        }
    }
}

void gc_flip()
{
    // sweep_garbage(the_cars);
    // sweep_garbage(the_cdrs);

    free(the_cars);
    free(the_cdrs);

    the_cars = new_cars;
    the_cdrs = new_cdrs;
}

bool is_broken_heart(SchemeAtom *pair)
{
    return (int) pair == BROKEN_HEART_TAG;
}

void relocate_old_result_in_new()
{
    if (is_pair(old))
    {
        // pair
        oldcr = the_cars[old->val->pair];

        if (is_broken_heart(oldcr))
        {
            // already-moved
            new = the_cdrs[old->val->pair];
            return;
        } else
        {
            SchemePairPointer old_ptr = old->val->pair;
            SchemePairPointer new_ptr = free_ptr;
            old->val->pair = new_ptr;
            new = old;

            // Update free pointer
            free_ptr++;

            // Copy the car and cdr to new memory
            new_cars[new_ptr] = oldcr;
            oldcr = the_cdrs[old_ptr];
            new_cdrs[new_ptr] = oldcr;

            // Construct the broken heart
            the_cars[old_ptr] = (SchemeAtom*) BROKEN_HEART_TAG;
            the_cdrs[old_ptr] = new;
            return;
        }
    } else
    {
        new = old;
    }
}

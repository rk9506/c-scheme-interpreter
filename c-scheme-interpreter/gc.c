#include "gc.h"

#define BROKEN_HEART_TAG "broken-heart"

SchemeAtom **new_cars;
SchemeAtom **new_cdrs;

SchemeAtom *old;
SchemeAtom *new;

SchemeAtom *oldcr;

SchemePairPointer scan;

void relocate_old_result_in_new();
void gc_loop();
void gc_flip();
bool is_broken_heart(SchemeAtom *atom);

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

    /* set_car(current, parsing); */
    /* current = cdr(current); */

    /* set_car(current, entry); */
    /* current = cdr(current); */

    /* set_car(current, primitive_temp); */
    /* current = cdr(current); */

    set_car(current, regs->temp);

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

    debug_log("Old root");
    debug_log_atom(get_populated_root());

    relocate_old_result_in_new();

    // reassign-root
    set_root(new);
    gc_loop();
}

void gc_loop()
{
    if (scan == free_ptr)
    {
        gc_flip();
        debug_dump_heap(the_cars, the_cdrs);
        debug_log("New root");
        debug_log_atom(get_populated_root());
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
        if (curr != NULL && !is_broken_heart(curr))
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

bool is_broken_heart(SchemeAtom *atom)
{
    return symbol_eq_str(atom, BROKEN_HEART_TAG);
}

SchemeAtom *make_broken_heart()
{
    return make_symbol(BROKEN_HEART_TAG);
}

bool is_pointer_to_pair(SchemeAtom *atom)
{
    if (atom == NULL) return false;

    return atom->type_tag == SCHEME_PAIR_POINTER || atom->type_tag == SCHEME_PROCEDURE;
}

SchemePairPointer get_pair_pointer(SchemeAtom *atom)
{
    if (atom->type_tag == SCHEME_PROCEDURE)
    {
        return atom->val->proc->val->pair;
    } else
    {
        return atom->val->pair;
    }
}

void replace_pair_pointer(SchemeAtom *atom, SchemePairPointer new_ptr)
{
    if (is_compound_procedure(atom))
    {
        atom->val->proc->val->pair = new_ptr;
    } else
    {
        atom->val->pair = new_ptr;
    }
}

void relocate_old_result_in_new()
{
    if (is_pointer_to_pair(old))
    {
        SchemePairPointer old_ptr = get_pair_pointer(old);
        // pair
        oldcr = the_cars[old_ptr];

        if (is_broken_heart(oldcr))
        {
            // already-moved
            new = the_cdrs[old_ptr];
            // replace_pair_pointer(new, the_cdrs[old_ptr]->val->num);
            return;
        } else
        {
            SchemePairPointer new_ptr = free_ptr;
            new = old;
            replace_pair_pointer(new, new_ptr);

            // Update free pointer
            free_ptr++;

            // Copy the car and cdr to new memory
            new_cars[new_ptr] = oldcr;
            oldcr = the_cdrs[old_ptr];
            new_cdrs[new_ptr] = oldcr;

            // Construct the broken heart
            the_cars[old_ptr] = make_broken_heart();
            the_cdrs[old_ptr] = new;
            return;
        }
    } else
    {
        new = old;
    }
}

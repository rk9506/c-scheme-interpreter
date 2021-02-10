#include "gc.h"

#define BROKEN_HEART_TAG "broken-heart"

// SchemeAtom **new_cars;
// SchemeAtom **new_cdrs;
//
// SchemeAtom *old;
// SchemeAtom *new;
//
// SchemeAtom *oldcr;

bool *the_marks;

SchemePairPointer scan;

bool is_pointer_to_pair(SchemeAtom *atom);
SchemePairPointer get_pair_pointer(SchemeAtom *atom);
void mark(SchemeAtom *atom);
void sweep();

// void relocate_old_result_in_new();
// void gc_loop();
// void gc_flip();
// bool is_broken_heart(SchemeAtom *atom);

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

    set_car(current, entry);
    current = cdr(current);

    /* set_car(current, primitive_temp); */
    /* current = cdr(current); */

    set_car(current, regs->temp);

    return root;
}

void collect_garbage()
{
    debug_log("Performing garbage collection...\n");

    the_marks = calloc(HEAP_SIZE, sizeof(bool));

    SchemeAtom *populated_root = get_populated_root();

    mark(populated_root);
    sweep();

    debug_log("Completed garbage collection\n");
}

void mark(SchemeAtom *atom)
{
    if (!is_pointer_to_pair(atom)) return;

    // pair
    SchemePairPointer ptr = get_pair_pointer(atom);

    if (the_marks[ptr]) return;

    the_marks[ptr] = true;

    // mcar
    mark(the_cars[ptr]);
    mark(the_cdrs[ptr]);
}

void sweep()
{
    SchemeAtom *free_list = the_empty_list();

    for (scan = HEAP_SIZE - 1; scan >= 0; scan--)
    {
        if (the_marks[scan])
        {
            // unmark
            the_marks[scan] = false;
        } else
        {
            // scan-loop
            // Can't free atoms here because they might be duplicated
            // somewhere else!!
            // TODO: Implement SchemeAtoms as typed pointers so that
            // I don't have to deal with this nonsense
            // free_atom(the_cars[scan]);
            // free_atom(the_cdrs[scan]);

            the_cdrs[scan] = free_list;

            free_ptr = scan;
            free_list = make_pair(free_ptr);
        }
    }

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

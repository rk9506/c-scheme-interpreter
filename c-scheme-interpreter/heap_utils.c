#include "heap_utils.h"

void perform_gc()
{
    collect_garbage();
}

void display_heap_entry(SchemeAtom *atom)
{
    if (atom == NULL)
    {
        printf("NULL");
        return;
    }

    if (atom == (SchemeAtom*) -1)
    {
        printf("BROKEN_HEART");
        return;
    }

    switch (atom->type_tag)
    {
        case SCHEME_NUMBER:
            printf("%.*g", DECIMAL_DIG, atom->val->num);
            break;
        case SCHEME_STRING:
            printf("%s", atom->val->str);
            break;
        case SCHEME_SYMBOL:
            printf("%s", atom->val->sym);
            break;
        case SCHEME_BOOLEAN:
            printf("b%d", atom->val->boolean);
            break;
        case SCHEME_PAIR_POINTER:
            printf("p%d", atom->val->pair);
            break;
        case SCHEME_PROCEDURE:
            printf("<proc>");
            break;
        case PRIMITIVE_PROCEDURE:
            printf("<prim>");
            break;
        case COMPILED_PROCEDURE:
            printf("<compiled>");
            break;
    }
}

void debug_dump_heap(SchemeAtom **the_cars, SchemeAtom **the_cdrs)
{
    if (DEBUGGING)
    {
        int null_count = 0;

        printf("Dumping heap:\n");

        int i;
        for (i = 0; i < HEAP_SIZE; i++)
        {
            if (the_cars[i] == NULL && the_cdrs[i] == NULL)
            {
                null_count++;
            }

            if (null_count == 20)
            {
                // Reached empty memory (probably lol)
                break;
            }

            printf("%3d:   ", i);
            display_heap_entry(the_cars[i]);
            printf("\t\t");
            display_heap_entry(the_cdrs[i]);
            printf("\n");
        }
    }
}

#include "printer.h"

void print_atom(SchemeAtom *atom);
void print_string(SchemeString str);
void print_number(SchemeNumber num);
void print_boolean(SchemeBoolean boolean);
void print_symbol(SchemeSymbol sym);
void print_procedure(SchemeProcedure *proc);
void print_list(SchemeAtom *list);

void print_elem(SchemeAtom *elem)
{
    if (is_null_list(elem))
    {
        // Print the empty list
        print_list(elem);
        return;
    }

    print_atom(elem);
}

void print_atom(SchemeAtom *atom)
{
    switch (atom->type_tag)
    {
        case SCHEME_STRING:
            print_string(atom->val->str);
            break;

        case SCHEME_NUMBER:
            print_number(atom->val->num);
            break;

        case SCHEME_BOOLEAN:
            print_boolean(atom->val->boolean);
            break;

        case SCHEME_SYMBOL:
            print_symbol(atom->val->sym);
            break;

        case SCHEME_PAIR_POINTER:
            print_list(atom);
            break;

        case SCHEME_PROCEDURE:
            print_procedure(atom->val->proc);
            break;

        case PRIMITIVE_PROCEDURE:
            printf("<primitive-procedure>");
            break;
    }
}


void print_string(SchemeString str)
{
    printf("\"");
    printf("%s", str);
    printf("\"");
}

void print_number(SchemeNumber num)
{
    printf("%.*g", DECIMAL_DIG, num);
}
void print_boolean(SchemeBoolean boolean)
{
    printf("#");

    if (boolean)
        printf("t");
    else
        printf("f");
}

void print_symbol(SchemeSymbol sym)
{
    printf("%s", sym);
}

void print_procedure(SchemeProcedure *proc)
{
    printf("<procedure ");
    print_list(proc->body);
    printf(">");
}

void print_list_contents(SchemeAtom *list)
{
    if (list == NULL) return;

    print_elem(car(list));

    SchemeAtom *list_cdr = cdr(list);

    if (!is_null_list(list_cdr))
    {
        if (is_pair(list_cdr))
        {
            printf(" ");
            print_list_contents(list_cdr);
        } else
        {
            printf(" . ");
            print_elem(list_cdr);
        }
    }
}

void print_list(SchemeAtom *list)
{
    printf("(");
    print_list_contents(list);
    printf(")");
}

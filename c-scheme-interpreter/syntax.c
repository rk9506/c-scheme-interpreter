#include "syntax.h"

bool is_self_evaluating(SchemeListElem *elem)
{
    SchemeAtom *atom = elem->atom;

    if (atom != NULL)
    {
        TypeTag type_tag = atom->type_tag;

        return type_tag == SCHEME_STRING
            || type_tag == SCHEME_NUMBER
            || type_tag == SCHEME_BOOLEAN;
    }

    return false;
}

#include "procedure_utils.h"

SchemeAtom *make_procedure(SchemeAtom *parameters,
                               SchemeAtom *body,
                               SchemeAtom *env)
{
    SchemeAtom *atom = make_atom();
    SchemePrimitive *prim = make_primitive();

    regs->val = cons(env, the_empty_list());
    regs->val = cons(body, regs->val);
    regs->val = cons(parameters, regs->val);

    atom->type_tag = SCHEME_PROCEDURE;
    prim->proc = regs->val;
    atom->val = prim;

    return atom;
}

SchemeAtom *procedure_parameters(SchemeProcedure *proc)
{
    return car(proc);
}

SchemeAtom *procedure_body(SchemeProcedure *proc)
{
    return car(cdr(proc));
}

SchemeAtom *procedure_env(SchemeProcedure *proc)
{
    return car(cdr(cdr(proc)));
}

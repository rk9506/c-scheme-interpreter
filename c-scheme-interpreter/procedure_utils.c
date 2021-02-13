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

bool is_primitive_procedure(SchemeAtom *atom)
{
    return atom->type_tag == PRIMITIVE_PROCEDURE;
}

bool is_compiled_procedure(SchemeAtom *atom)
{
    return atom->type_tag == COMPILED_PROCEDURE;
}

SchemeAtom *make_compiled_procedure(void *entry, SchemeAtom *env)
{
    SchemeAtom *atom = make_atom();
    SchemePrimitive *prim = make_primitive();

    atom->type_tag = COMPILED_PROCEDURE;
    prim->compiled_proc = malloc(sizeof(CompiledProcedure));
    prim->compiled_proc->entry = entry;
    prim->compiled_proc->env = env;
    atom->val = prim;

    return atom;
}

void *compiled_procedure_entry(SchemeAtom *proc)
{
    return proc->val->compiled_proc->entry;
}

SchemeAtom *compiled_procedure_env(SchemeAtom *proc)
{
    return proc->val->compiled_proc->env;
}

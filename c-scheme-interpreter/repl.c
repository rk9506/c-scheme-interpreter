#include "repl.h"

#define INPUT_PROMPT ";;; C-Scheme input:\n"
#define RESULT_ANNOUNCEMENT ";;; C-Scheme value:\n"

void start_repl();
void repl();

int main()
{
    start_repl();
}

void start_repl()
{
    initialise_regs();
    // initialise_stack();
    repl();
}

void repl()
{
    char exp[1024 * 1024];
    printf(INPUT_PROMPT);
    scanf("%s", exp);
    printf("\n");

    SchemeListElem *ast = generate_ast(exp);
    SchemeListElem *result = eval_exp(ast);

    printf(RESULT_ANNOUNCEMENT);
    print_elem(result);
    printf("\n");
    printf("\n");

    repl();
}

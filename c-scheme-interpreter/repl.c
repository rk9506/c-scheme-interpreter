#include "repl.h"

#define INPUT_BUFFER_SIZE 1024 * 1024

#define INPUT_PROMPT ";;; C-Scheme input:\n"
#define RESULT_ANNOUNCEMENT ";;; C-Scheme value:\n"

int start_repl();
int repl();

int main()
{
    return start_repl();
}

int start_repl()
{
    initialise_eval();
    // initialise_stack();
    return repl();
}

int repl()
{
    char exp[INPUT_BUFFER_SIZE];
    printf(INPUT_PROMPT);
    fgets(exp, INPUT_BUFFER_SIZE, stdin);
    printf("\n");

    SchemeListElem *ast = generate_ast(exp);
    SchemeListElem *result = eval_exp(ast);

    if (result == NULL) return 1;

    printf(RESULT_ANNOUNCEMENT);
    print_elem(result);
    printf("\n");
    printf("\n");

    return repl();
}

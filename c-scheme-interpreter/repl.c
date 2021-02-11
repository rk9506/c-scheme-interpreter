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
    initialise_runtime();
    // initialise_stack();
    return repl();
}

void initialise_buffer(char *exp)
{
    char c;
    for (c = *exp; c != '\0'; exp++)
    {
        *exp = '\0';
    }
}

int repl()
{
    char exp[INPUT_BUFFER_SIZE];
    // initialise_buffer(exp);
    printf(INPUT_PROMPT);
    fgets(exp, INPUT_BUFFER_SIZE, stdin);
    printf("\n");

    SchemeAtom *ast = generate_ast(exp);
    SchemeAtom *result = eval_exp(ast);

    printf(RESULT_ANNOUNCEMENT);
    print_elem(result);
    printf("\n");
    printf("\n");
    initialise_env();

    debug_log("Global env: ");
    debug_log_env(get_global_environment());

    return repl();
}

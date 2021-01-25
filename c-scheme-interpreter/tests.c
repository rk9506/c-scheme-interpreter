#include "tests.h"

#define BUFFER_SIZE 1024

int stdout_save;
char *output_buffer;

void run_all_tests();
void test_self_evaluating();
void run_test(char *title, char *input, char *expected);

int main()
{
    run_all_tests();
    return 0;
}

// A huge hack to get the output from the repl so that it can
// be tested, because that's easier than traversing the SchemeList resulting
// from eval. "Inspired" by https://stackoverflow.com/questions/60307605/get-the-last-string-printed-in-c-c
void replace_stdout()
{
    fflush(stdout); // Clean everything first
    stdout_save = dup(STDOUT_FILENO); // Save the stdout state
    freopen("NUL", "a", stdout); // Redirect stdout to null pointer
    setvbuf(stdout, output_buffer, _IOFBF, BUFFER_SIZE); // Set buffer to stdout
}

void restore_stdout()
{
    freopen("NUL", "a", stdout); //redirect stdout to null again
    dup2(stdout_save, STDOUT_FILENO); //restore the previous state of stdout
    setvbuf(stdout, NULL, _IONBF, BUFFER_SIZE); //disable buffer to print to screen instantly
}

void run_all_tests()
{
    test_self_evaluating();
}

void test_self_evaluating()
{
    run_test("should evaluate numbers", "2500", "2500");
    run_test("should evaluate strings", "\"Hello\"", "\"Hello\"");
    run_test("should evaluate true", "#t", "#t");
    run_test("should evaluate false", "#f", "#f");
}

void run_test(char *title, char *input, char *expected)
{
    printf("Running test: \t%s\n", title);
    printf("\tInput: \t\t%s\n", input);
    printf("\tExpected: \t%s\n", expected);

    SchemeListElem *ast = generate_ast(input);
    SchemeListElem *result = eval_exp(ast);

    output_buffer = malloc(sizeof(char) * BUFFER_SIZE);

    replace_stdout();
    print_elem(result);
    restore_stdout();

    char *actual = output_buffer;

    bool passed = strcmp(actual, expected) == 0;

    printf("\tActual: \t%s\n", actual);

    free(output_buffer);
    free(result);

    if (passed)
    {
        printf("\tPassed!\n");

    } else {
        printf("\tFailed!\n");
    }
}

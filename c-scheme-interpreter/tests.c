#include "tests.h"

#define BUFFER_SIZE 1024

int stdout_save;

void run_all_tests();
void run_test(char *title, char *input, char *expected);

void test_self_evaluating();
void test_quoted();
void test_definition();
void test_assignment();
void test_primitive_procedures();
void test_compound_procedures();

int num_passed;
int num_failed;

int main()
{
    run_all_tests();
    return 0;
}

// A huge hack to get the output from the repl so that it can
// be tested, because that's easier than traversing the SchemeList resulting
// from eval. "Inspired" by https://stackoverflow.com/questions/60307605/get-the-last-string-printed-in-c-c
void replace_stdout(char *output_buffer)
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
    num_passed = 0;
    num_failed = 0;

    test_self_evaluating();
    test_quoted();
    test_definition();
    test_assignment();
    test_primitive_procedures();
    test_compound_procedures();

    printf("Total passed:\t%d\n", num_passed);
    printf("Total failed:\t%d\n", num_failed);
}

void test_self_evaluating()
{
    run_test("should evaluate numbers", "2500", "2500");
    // run_test("should evaluate strings", "\"Hello world\"", "\"Hello world\"");
    run_test("should evaluate true", "#t", "#t");
    run_test("should evaluate false", "#f", "#f");
}

void test_quoted()
{
    run_test("should evaluate quoted symbols", "(quote sym)", "sym");
    run_test("should evaluate quoted lists", "(quote (define a 1))", "(define a 1)");
    run_test("should evaluate quoted empty list", "(quote ())", "()");
}

void test_definition()
{
    run_test("should be able to define a variable", "(begin (define x 5) x)", "5");
    run_test("should be able to redefine a variable", "(begin (define x 5) (define x 10) x)", "10");
}

void test_assignment()
{
    run_test("should be able to set a variable", "(begin (define x 5) (set! x 6) x)", "6");
}

void test_primitive_procedures()
{
    run_test("should be able to add with +", "(+ 1 2)", "3");
}

void test_compound_procedures()
{
    run_test("should be able to evaluate compound procedures and applications",
             "(begin (define f (lambda (x) (+ 1 x))) (f 5))",
             "6");

    run_test("should be able to use higher-order procedures",
             "(begin \
                 (define apply-twice (lambda (f x) (f (f x)))) \
                 (define inc (lambda (x) (+ x 1))) \
                 (apply-twice inc 5))",
             "7");

    run_test("should be able to create list structure using procedures",
             "(begin \
                (define cons (lambda (x y) (lambda (m) (m x y)))) \
                (define car (lambda (p) (p (lambda (x y) x)))) \
                (define cdr (lambda (p) (p (lambda (x y) y)))) \
                (define l (cons 1 (cons 2 (cons 3 (quote ()))))) \
                (car (cdr (cdr l))))",
             "3");
}

void run_test(char *title, char *input, char *expected)
{
    printf("Running test: \t%s\n", title);
    printf("\tInput: \t\t%s\n", input);
    printf("\tExpected: \t%s\n", expected);

    SchemeListElem *ast = generate_ast(input);
    initialise_eval();
    SchemeListElem *result = eval_exp(ast);

    char *output_buffer = calloc(BUFFER_SIZE, sizeof(char));

    replace_stdout(output_buffer);
    print_elem(result);
    restore_stdout();

    bool passed = strcmp(output_buffer, expected) == 0;

    printf("\tActual: \t%s\n", output_buffer);

    free(output_buffer);
    free_elem(result);

    if (passed)
    {
        printf("\tPassed!\n");
        num_passed++;

    } else {
        printf("\tFailed!\n");
        num_failed++;
    }
}

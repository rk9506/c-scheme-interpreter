#include "parser.h"


#define LPAREN '('
#define RPAREN ')'
#define WHITESPACE " \t\n\v\f\r"

struct SchemeList;

typedef struct { char *atom; struct SchemeList *list; } ListElem;
struct SchemeList { ListElem *car; struct SchemeList *cdr; };

struct SchemeList *the_empty_list()
{
    return NULL;
}

bool is_null_list(struct SchemeList *list)
{
    return list == NULL;
}

ListElem *generate_ast(char *exp)
{
    char **save_ptr = malloc(sizeof(char*));
    ListElem *elem = malloc(sizeof(ListElem));
    elem->atom = NULL;
    elem->list = NULL;

    char *pch = strtok_r(exp, WHITESPACE, save_ptr);

    if (*pch == LPAREN)
    {
        elem->list = parse_list(pch, save_ptr);
    } else
    {
        elem->atom = pch;
    }

    return elem;
}

struct SchemeList *make_list()
{
    struct SchemeList *result = malloc(sizeof(struct SchemeList));
    result->cdr = NULL;
    ListElem *result_car = malloc(sizeof(ListElem));
    result_car->atom = NULL;
    result_car->list = NULL;

    result->car = result_car;

    return result;
}

struct SchemeList *parse_list(char *tokens, char **save_ptr)
{
    // Move forward
    tokens = strtok_r(NULL, WHITESPACE, save_ptr);

    if (tokens == NULL)
    {
        printf("Error: Did not find closing parenthesis\n");
        return NULL;
    }

    if (*tokens == RPAREN)
    {
        return NULL;
    }

    struct SchemeList *result = make_list();

    // Parse first element
    if ((*tokens) == LPAREN)
    {
        result->car->list = parse_list(tokens, save_ptr);
    } else
    {
        result->car->atom = tokens;
    }


    // Parse the rest of the elements
    result->cdr = parse_list(tokens, save_ptr);

    return result;
}

int count_parentheses(char *exp)
{
    char c;
    int count = 0;

    while ((c = *exp))
    {
        if (c == LPAREN || c == RPAREN)
        {
            count++;
        }

        exp++;
    }

    return count;
}

char *pad_parentheses(char *exp)
{
    int num_parens = count_parentheses(exp);
    size_t old_length = strlen(exp);

    size_t new_length = old_length + 2 * num_parens;

    char *padded = malloc(sizeof(char) * new_length);
    char *curr = padded;

    char c;
    while ((c = *exp) != '\0')
    {
        if (c == LPAREN || c == RPAREN)
        {
            *(curr++) = ' ';
            *(curr++) = c;
            *(curr++) = ' ';
        } else
        {
            *(curr++) = c;
        }
        exp++;
    }

    return padded;
}

void print_elem(ListElem *elem)
{
    if (elem->atom != NULL)
    {
        printf("%s", elem->atom);
    } else
    {
        print_list(elem->list);
    }
}

void print_list_contents(struct SchemeList *list)
{
    print_elem(list->car);

    if (list->cdr != NULL)
    {
        printf(" ");
        print_list_contents(list->cdr);
    }
}

void print_list(struct SchemeList *list)
{
    if (list == NULL) return;

    printf("(");
    print_list_contents(list);
    printf(")");
}

int main(int argc, char *argv[])
{
    char *padded = pad_parentheses("(define f (lambda (x) (+ x 10)))");
    ListElem *ast = generate_ast(padded);
    print_elem(ast);

    return 0;
}

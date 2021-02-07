#include "parser.h"

#define LPAREN '('
#define RPAREN ')'
#define DOUBLEQUOTE '"'
#define SINGLEQUOTE '\''
#define BOOL_PREFIX '#'
#define WHITESPACE " \t\n\v\f\r"

bool is_number_atom(char *atom);
bool is_boolean_atom(char *atom);
bool is_string_atom(char *atom);
bool is_list(char *token);
bool is_shorthand_quoted(char *token);

char *pad_special_characters(char *exp);

SchemeAtom *parse_atom(char *atom, char **save_ptr);
void parse_string(char *token, SchemeAtom *atom, char **save_ptr);
SchemeAtom *parse_shorthand_quoted(char *token, char **save_ptr);

void raise_parse_error(char *message)
{
    printf("Parse error: %s\n", message);
}

SchemeAtom *generate_ast(char *exp)
{
    debug_log("Started parsing\n");

    parsing = NULL;

    char **save_ptr = malloc(sizeof(char*));

    exp = pad_special_characters(exp);

    char *pch = strtok_r(exp, WHITESPACE, save_ptr);

    SchemeAtom *elem = parse_atom(pch, save_ptr);

    debug_log("Completed parsing\n");

    parsing = NULL;

    return elem;
}

SchemeAtom *parse_atom(char *token, char **save_ptr)
{
    SchemeAtom *atom = make_atom();
    SchemePrimitive *prim = make_primitive();

    atom->val = prim;

    if (is_number_atom(token))
    {
        char *next_non_digit;

        prim->num = strtof(token, &next_non_digit);

        atom->type_tag = SCHEME_NUMBER;
    } else if (is_boolean_atom(token))
    {
        char bool_letter = *(token + 1);

        if (bool_letter == 't')
            prim->boolean = true;
        else if (bool_letter == 'f')
            prim->boolean = false;
        else raise_parse_error("Invalid boolean");

        atom->type_tag = SCHEME_BOOLEAN;
    } else if (is_string_atom(token))
    {
        parse_string(token, atom, save_ptr);
    } else if (is_list(token))
    {
        free_atom(atom);
        return parse_list(token, save_ptr);
    } else if (is_shorthand_quoted(token))
    {
        return parse_shorthand_quoted(token, save_ptr);
    } else
    {
        // Treat the atom as a symbol
        prim->sym = strdup(token);
        atom->type_tag = SCHEME_SYMBOL;
    }

    return atom;
}

void parse_string(char *token, SchemeAtom *atom, char **save_ptr)
{
    atom->val->str = calloc(1, sizeof(char));
    atom->type_tag = SCHEME_STRING;

    //.Right now, token points at "
    token++;

    // Token points at start of string
    int token_len = strlen(token);
    char *new_str;

    while (token[token_len - 1] != DOUBLEQUOTE)
    {
        // +2: +1 for a space character, +1 for null terminator
        new_str = calloc(strlen(atom->val->str), token_len + 2);

        strcpy(new_str, atom->val->str);

        free(atom->val->str);

        strcat(new_str, token);
        new_str[strlen(new_str)] = ' ';

        atom->val->str = new_str;

        token = strtok_r(NULL, WHITESPACE, save_ptr);
        token_len = strlen(token);
    }

    new_str = calloc(strlen(atom->val->str), token_len);
    strcpy(new_str, atom->val->str);
    strncat(new_str, token, token_len - 1);
    free(atom->val->str);
    atom->val->str = new_str;
}

bool is_number_atom(char *atom)
{
    char *end;

    strtof(atom, &end);

    return *end == '\0';
}

bool is_boolean_atom(char *atom)
{
    return *atom == BOOL_PREFIX;
}

bool is_string_atom(char *atom)
{
    return *atom == DOUBLEQUOTE;
}

bool is_list(char *token)
{
    return *token == LPAREN;
}

SchemeAtom *parse_list(char *tokens, char **save_ptr)
{
    // Move forward
    tokens = strtok_r(NULL, WHITESPACE, save_ptr);

    if (tokens == NULL)
    {
        raise_parse_error("Error: Did not find closing parenthesis");
        return NULL;
    }

    if (*tokens == RPAREN)
    {
        return NULL;
    }

    parsing = cons(the_empty_list(), the_empty_list());

    save(parsing);

    // Parse first element
    set_car(parsing, parse_atom(tokens, save_ptr));

    parsing = restore();
    save(parsing);

    // Parse the rest of the elements
    set_cdr(parsing, parse_list(tokens, save_ptr));

    parsing = restore();

    return parsing;
}

bool is_shorthand_quoted(char *token)
{
    return *token == SINGLEQUOTE;
}

SchemeAtom *parse_shorthand_quoted(char *token, char **save_ptr)
{
    // Move past the '
    token = strtok_r(NULL, WHITESPACE, save_ptr);

    parsing = cons(parse_atom(token, save_ptr), the_empty_list());

    parsing = cons(make_symbol("quote"), parsing);

    return parsing;
}

bool is_special_character(char c)
{
    return c == LPAREN || c == RPAREN || c == SINGLEQUOTE;
}

// Special characters are parentheses and singlequotes
int count_special_characters(char *exp)
{
    char c;
    int count = 0;

    while ((c = *exp))
    {
        if (is_special_character(c))
        {
            count++;
        }

        exp++;
    }

    return count;
}

char *pad_special_characters(char *exp)
{
    int num_parens = count_special_characters(exp);
    size_t old_length = strlen(exp);

    size_t new_length = old_length + 2 * num_parens;

    char *padded = malloc(sizeof(char) * new_length);
    char *curr = padded;

    char c;
    while ((c = *exp) != '\0')
    {
        if (is_special_character(c))
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

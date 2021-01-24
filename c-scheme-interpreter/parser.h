#ifndef __PARSER_H_
#define __PARSER_H_

#include "types.h"
#include "printer.h"

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

SchemeListElem *generate_ast(char *exp);

struct SchemeList *parse_list(char *tokens, char **save_ptr);
void print_list(struct SchemeList *list);

#endif // __PARSER_H_

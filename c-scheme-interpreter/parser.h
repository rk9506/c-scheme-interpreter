#ifndef __PARSER_H_
#define __PARSER_H_

#include "types.h"
#include "printer.h"
#include "heap.h"

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

SchemeAtom *generate_ast(char *exp);

SchemeAtom *parse_list(char *tokens, char **save_ptr);

#endif // __PARSER_H_

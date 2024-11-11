#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "postfix.h"

#define MAX_TOKENS 128

double evaluate_infix_expression(char ** expr, int nterms);

int establish_precedence(char operator);

#endif

#pragma once

/* Checking validity of parsed arguments and writing them to output. */

#include <stdbool.h>

#include "output.h"
#include "parse.h"

void resetEval(Out *);
bool eval(Parse *, Out *);
bool loop(Parse *);

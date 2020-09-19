#pragma once

#include <stdbool.h>

#include "output.h"
#include "parse.h"

void resetEval(Out *);
bool eval(Parse *, Out *);
bool loop(Parse *);

#pragma once

#include <stdbool.h>

#include "signatures.h"
#include "sizes.h"
#include "types.h"

typedef struct Parse {
  char            buf[SIZE_IN];
  char          * head;
  ArgVal          args[SIZE_ARGS];
  const Sig     * sig;
} Parse;

void resetParse(Parse *p);
bool parse(Parse *);
void showParseError(Parse *p);

#pragma once

#include "signatures.h"
#include "sizes.h"
#include "types.h"

typedef struct Parse {
  char            buf[SIZE_IN];
  char          * head;
  ArgVal          args[SIZE_ARGS];
  const Sig     * sig;
} Parse;

void parse(Parse *);

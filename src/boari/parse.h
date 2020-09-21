#pragma once

/* Turning a line of text into an array of validated types. */

#include <stdbool.h>

#include "../constants/sizes.h"
#include "signatures.h"
#include "types.h"

typedef struct Parse {

/* The Parse object tracks the process of parsing its input at `buf` into an
 * array containing one function enum and various ArgVals in `args`. `head` is
 * a pointer against `buf` that points to the next piece of text to evaluate.
 * `sig` points to the Sig that input will be validated against.
 *
 * Even though input size is well-defined, `buf` is a pointer rather than a
 * static array. This is because `head` is assigned to `buf` in recursive
 * parsing situations, such as with the echo command.
 *
 * All string values parsed into `args` are pointers to tokens in `buf`. No
 * copying takes place. The strings are further refined into enums before `buf`
 * is filled again, so this is not a problem. */

  char          * buf;
  char          * head;
  ArgVal          args[SIZE_ARGS];
  const Sig     * sig;
} Parse;

void resetParse(Parse *);
bool parse(Parse *);
void showParseError(Parse *);
Parse makeParse(char *);

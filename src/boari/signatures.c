#include <string.h>

#include "../constants/sizes.h"
#include "signatures.h"
#include "types.h"

static void cat(char *, char *);

static void
cat(char *s, char *x) {

/* A more readable way to append strings. */

  (void)strlcat(s, x, SIZE_IN);
}

char *
showSignature(Sig g, char *s) {

/* When an input string doesn't match a Sig, print the expected input. */

  int n = 0;

  memset(s, 0, SIZE_IN);
  if (g.count == 0) { return "nothing "; }
  for (; n < g.count; n++) {
    if (n == g.required) { cat(s, "| "); }
    cat(s, showArgType(g.args[n]));
  }
  return s;
}

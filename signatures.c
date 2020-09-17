#include <string.h>

#include "signatures.h"
#include "sizes.h"
#include "types.h"

static void cat(char *, char *);

static void
cat(char *s, char *x) {
  (void)strlcat(s, x, SIZE_LINE);
}

char *
showSignature(Sig g, char *s) {
  unsigned int n = 0;
  memset(s, 0, SIZE_LINE);
  if (g.count == 0) { return "nothing "; }
  for (; n < g.count; n++) {
    if (n == g.required) { cat(s, "| "); }
    cat(s, showArgType(g.args[n]));
  }
  return s;
}

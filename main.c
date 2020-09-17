#include <err.h>
#include <stdio.h>

#include "funcs.h"
#include "parse.h"
#include "sizes.h"

static void errorCheck(Parse *);

static void
errorCheck(Parse *p) {
  switch(p->args[0].i) {
    case F_ERROR:
      warnx("expected %s", showSignature(*p->sig, p->buf));
      break;
    case F_UNKNOWN:
      warnx("unknown function");
      break;
  }
}

int
main(void) {
  Parse p = {{0}};
  warnx("Welcome. You can exit at any time by pressing q + enter.");
  while(fgets(p.buf, SIZE_IN, stdin) != NULL) {
    parse(&p);
    errorCheck(&p);
  }
  return 0;
}

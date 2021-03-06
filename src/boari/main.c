#include <err.h>
#include <stdio.h>

#include "../constants/sizes.h"
#include "eval.h"
#include "output.h"
#include "parse.h"

int
main(void) {

/* The top level REPL. Read a line, parse it, evaluate it, output binary. */

  char buf[SIZE_IN] = {0};
  Parse p = makeParse(buf);
  Out o = makeOut();

  warnx("Welcome. You can exit at any time by pressing q + enter.");
  while(fgets(p.buf, SIZE_IN, stdin) != NULL) {
    resetParse(&p);
    if (! parse(&p))     { showParseError(&p); continue; }
    resetEval(&o);
    if (! eval(&p, &o))  { continue; }
    if (! writeFunc(&o)) { warnx("write error"); continue; }
    if (! loop(&p))      { break; }
  }

  return 0;
}

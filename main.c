#include <err.h>
#include <stdio.h>

#include "output.h"
#include "parse.h"
#include "sizes.h"

int
main(void) {
  char buf[SIZE_IN] = {0};
  Parse p = makeParse(buf);
  Out o = makeOut();
  warnx("Welcome. You can exit at any time by pressing q + enter.");
  while(fgets(p.buf, SIZE_IN, stdin) != NULL) {
    resetParse(&p);
    if (! parse(&p)) { showParseError(&p); continue; }
  }
  return 0;
}

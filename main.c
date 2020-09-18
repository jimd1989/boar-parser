#include <err.h>
#include <stdio.h>

#include "parse.h"
#include "sizes.h"

int
main(void) {
  char buf[SIZE_IN] = {0};
  Parse p = {0};
  p.buf = buf;
  warnx("Welcome. You can exit at any time by pressing q + enter.");
  while(fgets(p.buf, SIZE_IN, stdin) != NULL) {
    resetParse(&p);
    if (! parse(&p)) { showParseError(&p); continue; }
  }
  return 0;
}

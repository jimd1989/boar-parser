#include <err.h>
#include <stdio.h>

#include "funcs.h"
#include "parse.h"
#include "sizes.h"

int
main(void) {
  Parse p = {0};
  int n = 0;
  warnx("Welcome. You can exit at any time by pressing q + enter.");
  while(fgets(p.buf, SIZE_LINE, stdin) != NULL) {
    parse(&p);
    if (p.args[0].i == F_NOTE_ON || p.args[0].i == F_NOTE_OFF) {
      warnx("yes %d %d %d %d", p.args[0].i, p.args[1].i, p.args[2].i, p.args[3].i);
    } else {
      warnx("no %d %d %d %d", p.args[0].i, p.args[1].i, p.args[2].i, p.args[3].i);
    }
  }
}

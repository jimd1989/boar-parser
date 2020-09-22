#include <err.h>
#include <stdbool.h>
#include <stdio.h>

#include "../constants/funcs.h"
#include "../constants/magic.h"
#include "../constants/sizes.h"
#include "input.h"

static bool
runEcho(In *i) {
  fwrite(i->head, 1, i->cmdSize, stdout);
  fflush(stdout);
  advance(i, i->cmdSize);
  return true;
}

bool
dispatch(In *i) {
  Fn f = i->cmd;
  bool r =
    f == F_ECHO ? runEcho(i) : false;
  if (! r) { advance(i, i->cmdSize); }
  return r;
}

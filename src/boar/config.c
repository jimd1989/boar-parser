#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define STREQ(x, y) (strcmp(x, y) == 0)

Config
makeConfig(int argc, char **argv) {
  int n = 1;
  Config c = {0};
  c.chan = CONFIG_CHAN;
  c.allChans = false;
  c.echoNotes = false;
  c.passNotes = false;
  c.rate = CONFIG_RATE;
  for (; n < argc ; n++) {
    if (STREQ(argv[n], "-chan"))      { c.chan = atoi(argv[++n]); }
    else if (STREQ(argv[n], "-rate")) { c.rate = atoi(argv[++n]); }
    else if (STREQ(argv[n], "-all"))  { c.allChans = true; }
    else if (STREQ(argv[n], "-echo")) { c.echoNotes = true; }
    else if (STREQ(argv[n], "-pass")) { c.passNotes = true; }
    else                              { warnx("unknown: %s", argv[n]); }
  }
  return c;
}

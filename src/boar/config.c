#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define STREQ(x, y) (strcmp(x, y) == 0)

Config
makeConfig(int argc, char **argv) {
  int n = 1;
  Config c = {{0}};
  c.in.chan = CONFIG_CHAN;
  c.in.allChans = false;
  c.in.echoNotes = false;
  c.in.passNotes = false;
  c.audio.rate = CONFIG_RATE;
  for (; n < argc ; n++) {
    if (STREQ(argv[n], "-chan"))      { c.in.chan = atoi(argv[++n]); }
    else if (STREQ(argv[n], "-rate")) { c.audio.rate = atoi(argv[++n]); }
    else if (STREQ(argv[n], "-all"))  { c.in.allChans = true; }
    else if (STREQ(argv[n], "-echo")) { c.in.echoNotes = true; }
    else if (STREQ(argv[n], "-pass")) { c.in.passNotes = true; }
    else                              { warnx("unknown: %s", argv[n]); }
  }
  return c;
}

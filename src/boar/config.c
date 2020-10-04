#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define STREQ(x, y) (strcmp(x, y) == 0)

static void setChan(Config *, int);
static void setRate(Config *, int);

static void
setChan(Config *c, int n) {
  if (n < 1 || n > 16) { warnx("channel must be 1 - 16"); return; }
  c->in.chan = --n;
}

static void
setRate(Config *c, int n) {
  if (n < 1) { warnx("rate must be greater than zero"); return; }
  c->audio.rate = n;
}

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
    if (STREQ(argv[n], "-chan"))      { setChan(&c, atoi(argv[++n])); }
    else if (STREQ(argv[n], "-rate")) { setRate(&c, atoi(argv[++n])); }
    else if (STREQ(argv[n], "-all"))  { c.in.allChans = true; }
    else if (STREQ(argv[n], "-echo")) { c.in.echoNotes = true; }
    else if (STREQ(argv[n], "-pass")) { c.in.passNotes = true; }
    else                              { warnx("unknown: %s", argv[n]); }
  }
  return c;
}

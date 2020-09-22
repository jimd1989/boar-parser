#include <err.h>
#include <stdbool.h>
#include <stdint.h>
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

static bool
runQuit(In *i) {
  uint8_t buf[7] = {0};
  int *w = (int *)buf;
  int16_t *sz = (int16_t *)(buf + sizeof(*w));
  *w = BOAR_WORD;
  *sz = (int16_t)1;
  buf[6] = F_QUIT;
  fwrite(buf, 1, 7, stdout);
  fflush(stdout);
  advance(i, i->cmdSize);
  return true;
}

static bool
runLoudness(In *i) {
  float *fx = (float *)i->head;
  warnx("Loudness run with %f", *fx);
  advance(i, sizeof(float));
  return true;
}

bool
dispatch(In *i) {
  Fn f = i->cmd;
  bool r =
    f == F_ECHO     ? runEcho(i)     :
    f == F_LOUDNESS ? runLoudness(i) :
    f == F_QUIT     ? runQuit(i)     : false;
  if (! r) { advance(i, i->cmdSize); }
  return r;
}

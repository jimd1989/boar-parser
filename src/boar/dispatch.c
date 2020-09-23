/* This module makes use of the guard macro _O. Please refer to control.h for
 * more information. */

#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../constants/funcs.h"
#include "../constants/magic.h"
#include "../constants/sizes.h"
#include "control.h"
#include "input.h"

static bool
runNote(In *i) {
  uint8_t note = 0;
  uint8_t vel = 0;
  _O(readByte(i, &note, true));
  _O(readByte(i, &vel, true));
  if (vel == 0) { warnx("Note %d turned off", note); }
  else          { warnx("Note %d turned on with %d velocity", note, vel); }
  return true;
}

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
  float vol = 0.0f;
  _O(readFloat(i, &vol, true));
  warnx("l run with %f", vol);
  return true;
}

bool
dispatch(In *i) {
  Fn f = i->cmd;
  bool r =
    f == F_NOTE_ON      ? runNote(i)     :
    f == F_ATTACK       ? false          :
    f == F_ATTACK_WAVE  ? false          :
    f == F_DECAY        ? false          :
    f == F_DECAY_WAVE   ? false          :
    f == F_ENV_ASSIGN   ? false          :
    f == F_ECHO         ? runEcho(i)     :
    f == F_KEY_CURVE    ? false          :
    f == F_LOUDNESS     ? runLoudness(i) :
    f == F_AMPLITUDE    ? false          :
    f == F_MODULATE     ? false          :
    f == F_ENV_LOOP     ? false          :
    f == F_PITCH        ? false          :
    f == F_QUIT         ? runQuit(i)     :
    f == F_RELEASE      ? false          :
    f == F_RELEASE_WAVE ? false          :
    f == F_SUSTAIN      ? false          :
    f == F_TOUCH        ? false          :
    f == F_TUNE         ? false          :
    f == F_WAVE         ? false          : false;
  if (! r) { advance(i, i->cmdSize); }
  return r;
}

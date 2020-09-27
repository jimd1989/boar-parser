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

static bool isAllRead(In *);
static bool note(In *);
static bool echo(In *);
static bool loudness(In *);
static bool quit(In *);
static bool env(In *);

static bool
isAllRead(In *i) {

/* Ensure that the entire command was read before dispatching any actions. */

  return i->cmdSize == 0;
}

static bool
note(In *i) {
  uint8_t note = 0;
  uint8_t vel = 0;
  _O(readByte(i, &note, true));
  _O(readByte(i, &vel, true));
  _O(isAllRead(i));
  if (vel == 0) { warnx("Note %d turned off", note); }
  else          { warnx("Note %d turned on with %d velocity", note, vel); }
  return true;
}

static bool
echo(In *i) {
  fwrite(i->head, 1, i->cmdSize, stdout);
  fflush(stdout);
  advance(i, i->cmdSize);
  return true;
}

static bool
loudness(In *i) {
  float vol = 0.0f;
  _O(readFloat(i, &vol, true));
  _O(isAllRead(i));
  warnx("l run with %f", vol);
  return true;
}

static bool
quit(In *i) {
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
env(In *i) {
  uint8_t e = 0;
  float f = 0.0f;
  char c = 
    i->cmd == F_ATTACK  ? 'a' :
    i->cmd == F_DECAY   ? 'd' :
    i->cmd == F_RELEASE ? 'r' :
    i->cmd == F_SUSTAIN ? 's' : '?';
  _O(readByte(i, &e, true));
  _O(readFloat(i, &f, true));
  _O(isAllRead(i));
  warnx("Set env no %d's %c to %f", e, c, f);
  return true;
}

bool
dispatch(In *i) {
  Fn f = i->cmd;
  bool r =
    f == F_NOTE_ON      ? note(i)        :
    f == F_ATTACK       ? env(i)         :
    f == F_ATTACK_WAVE  ? false          :
    f == F_DECAY        ? env(i)         :
    f == F_DECAY_WAVE   ? false          :
    f == F_ENV_ASSIGN   ? false          :
    f == F_ECHO         ? echo(i)        :
    f == F_KEY_CURVE    ? false          :
    f == F_LOUDNESS     ? loudness(i)    :
    f == F_AMPLITUDE    ? false          :
    f == F_MODULATE     ? false          :
    f == F_ENV_LOOP     ? false          :
    f == F_PITCH        ? false          :
    f == F_QUIT         ? quit(i)        :
    f == F_RELEASE      ? env(i)         :
    f == F_RELEASE_WAVE ? false          :
    f == F_SUSTAIN      ? env(i)         :
    f == F_TOUCH        ? false          :
    f == F_TUNE         ? false          :
    f == F_WAVE         ? false          : false;
  if (! r) { advance(i, i->cmdSize); }
  return r;
}

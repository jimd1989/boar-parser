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
static bool env(In *);
static bool envAssign(In *);
static bool envWave(In *);
static bool key(In *);
static bool loudness(In *);
static bool amplitude(In *);
static bool modulate(In *);
static bool envLoop(In *);
static bool quit(In *);

static void
readError(In *i) {
  warnx("%d bytes unread in %d", i->cmdSize, i->cmd);
}

static bool
isAllRead(In *i) {

/* Ensure that the entire command was read before dispatching any actions. */

  if (i->cmdSize == 0) { return true; }
  else                 { readError(i); return false; }
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

static bool
envAssign(In *i) {
  uint8_t e = 0;
  uint8_t o = 0;
  uint8_t t = 0;
  float f = 0.0f;
  _O(readByte(i, &e, true));
  _O(readByte(i, &o, true));
  _O(readByte(i, &t, true));
  _O(readFloat(i, &f, true));
  _O(isAllRead(i));
  warnx("Assigned env %d to osc %d's %d at depth %f", e, o, t, f);
  return true;
}

static bool
envWave(In *i) {
  uint8_t e = 0;
  uint8_t w = 0;
  char c = 
    i->cmd == F_ATTACK_WAVE  ? 'A' :
    i->cmd == F_DECAY_WAVE   ? 'D' :
    i->cmd == F_RELEASE_WAVE ? 'R' : '?';
  _O(readByte(i, &e, true));
  _O(readByte(i, &w, true));
  _O(isAllRead(i));
  warnx("Set env no %d's %c wave to %d", e, c, (int8_t)w);
  return true;
}

static bool key(In *i) {
  uint8_t o = 0;
  uint8_t w = 0;
  _O(readByte(i, &o, true));
  _O(readByte(i, &w, true));
  _O(isAllRead(i));
  warnx("Set osc no %d's key curve to %d", o, (int8_t)w);

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

static bool amplitude(In *i) {
  uint8_t o = 0;
  float f = 0.0f;
  float b = 0.0f;
  _O(readByte(i, &o, true));
  _O(readFloat(i, &f, true));
  _O(readFloat(i, &b, true));
  _O(isAllRead(i));
  warnx("Set osc no %d to amplitude %f balance %f", o, f, b);
  return true;
}

static bool modulate(In *i) {
  uint8_t o1 = 0;
  uint8_t o2 = 0;
  float f = 0.0f;
  uint8_t m = 0;
  _O(readByte(i, &o1, true));
  _O(readByte(i, &o2, true));
  _O(readFloat(i, &f, true));
  _O(readByte(i, &m, true));
  _O(isAllRead(i));
  warnx("osc %d modulates osc %d's %d at depth %f", o1, o2, m, f);
  return true;
}

static bool
envLoop(In *i) {
  bool l = false;
  uint8_t e = 0;
  _O(readByte(i, &e, true));
  _O(readByte(i, (uint8_t *)&l, true));
  _O(isAllRead(i));
  warnx("env %d is %s", e, l ? "looped" : "unlooped");
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

bool
dispatch(In *i) {
  Fn f = i->cmd;
  bool r =
    f == F_NOTE_ON      ? note(i)        :
    f == F_ATTACK       ? env(i)         :
    f == F_ATTACK_WAVE  ? envWave(i)     :
    f == F_DECAY        ? env(i)         :
    f == F_DECAY_WAVE   ? envWave(i)     :
    f == F_ENV_ASSIGN   ? envAssign(i)   :
    f == F_ECHO         ? echo(i)        :
    f == F_KEY_CURVE    ? key(i)         :
    f == F_LOUDNESS     ? loudness(i)    :
    f == F_AMPLITUDE    ? amplitude(i)   :
    f == F_MODULATE     ? modulate(i)    :
    f == F_ENV_LOOP     ? envLoop(i)     :
    f == F_PITCH        ? false          :
    f == F_QUIT         ? quit(i)        :
    f == F_RELEASE      ? env(i)         :
    f == F_RELEASE_WAVE ? envWave(i)     :
    f == F_SUSTAIN      ? env(i)         :
    f == F_TOUCH        ? false          :
    f == F_TUNE         ? false          :
    f == F_WAVE         ? false          : false;
  if (! r) { advance(i, i->cmdSize); }
  return r;
}

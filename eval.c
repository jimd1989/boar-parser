#include <err.h>
#include <stdbool.h>
#include <stdint.h>

#include "control.h"
#include "funcs.h"
#include "parse.h"
#include "midi.h"
#include "output.h"
#include "types.h"

static bool boundI(int, int, int);
static bool boundF(float, float, float);
static void boundIError(int, int, int);
static void boundFError(float, float, float);
static OutResult noteOn(ArgVal *, Out *);
static OutResult noteOff(ArgVal *, Out *);

static bool
boundI(int n, int m, int x) {
  if (x < n || x > m) { boundIError(n, m, x); return false; }
  else                { return true; }
}

static bool
boundF(float n, float m, float x) {
  if (x < n || x > m) { boundIError(n, m, x); return false; }
  else                { return true; }
}

static void
boundIError(int n, int m, int x) {
  warnx("%d not between %d and %d", x, n, m);
}

static void
boundFError(float n, float m, float x) {
  warnx("%f not between %f and %f", x, n, m);
}

static OutResult
noteOn(ArgVal *as, Out *o) {
  _O(boundI(0, MIDI_MAX, as[0].i))
  _O(boundI(0, MIDI_MAX, as[1].i))
  _O(boundI(1, MIDI_CHANNELS, as[2].i))
  _O(writeHead(o, (int16_t)3))
  _O(writeInt(o, MIDI_NOTE_ON + (as[2].i - 1)))
  _O(writeInt(o, as[0].i))
  _O(writeInt(o, as[1].i))
  return OUT_SUCCESS;
}

static OutResult
noteOff(ArgVal *as, Out *o) {
  _O(boundI(0, MIDI_MAX, as[0].i))
  _O(boundI(1, MIDI_CHANNELS, as[1].i))
  _O(writeHead(o, (int16_t)3))
  _O(writeInt(o, MIDI_NOTE_ON + (as[1].i - 1)))
  _O(writeInt(o, as[0].i))
  _O(writeInt(o, 0))
  return OUT_SUCCESS;
}

void
eval(Parse *p, Out *o) {
  OutResult r = OUT_ERROR;
  ArgVal *as = p->args;
  Fn f = as[0].i;
  r =
    f == F_NOTE_ON      ? noteOn(as++, o)  :
    f == F_NOTE_OFF     ? noteOff(as++, o) :
    f == F_ATTACK       ? true :
    f == F_ATTACK_WAVE  ? true :
    f == F_DECAY        ? true :
    f == F_DECAY_WAVE   ? true :
    f == F_ENV_ASSIGN   ? true :
    f == F_ECHO         ? true :
    f == F_KEY_CURVE    ? true :
    f == F_LOUDNESS     ? true :
    f == F_AMPLITUDE    ? true :
    f == F_MODULATE     ? true :
    f == F_ENV_LOOP     ? true :
    f == F_PITCH        ? true :
    f == F_QUIT         ? true :
    f == F_RELEASE      ? true :
    f == F_RELEASE_WAVE ? true :
    f == F_TOUCH        ? true :
    f == F_TUNE         ? true :
    f == F_WAVE         ? true : false;
  if (r) writeFunc(o);
}

#include <err.h>
#include <stdbool.h>
#include <stdint.h>

#include "control.h"
#include "eval.h"
#include "funcs.h"
#include "parse.h"
#include "midi.h"
#include "output.h"
#include "types.h"

static bool boundI(int, int, int);
static bool boundF(float, float, float);
static void boundIError(int, int, int);
static void boundFError(float, float, float);
static bool noteOn(ArgVal *, Out *);
static bool noteOff(ArgVal *, Out *);
static bool setEnv(ArgVal *, Out *);
static bool setWave(ArgVal *, Out *);
static bool assignEnv(ArgVal *, Out *);
static bool echo(ArgVal *, Parse *, Out *);

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

static bool
noteOn(ArgVal *as, Out *o) {
  _O(boundI(0, MIDI_MAX, as[0].i))
  _O(boundI(0, MIDI_MAX, as[1].i))
  _O(boundI(1, MIDI_CHANNELS, as[2].i))
  _O(writeHead(o, (int16_t)3))
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[2].i - 1))))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeByte(o, (uint8_t)as[1].i))
  return true;
}

static bool
noteOff(ArgVal *as, Out *o) {
  _O(boundI(0, MIDI_MAX, as[0].i))
  _O(boundI(1, MIDI_CHANNELS, as[1].i))
  _O(writeHead(o, (int16_t)3))
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[1].i - 1))))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeByte(o, (uint8_t)0))
  return true;
}

static bool
setEnv(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(float) + sizeof(float);
  _O(writeHead(o, size))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  return true;
}

static bool
setWave(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(int);
  _O(writeHead(o, size))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeInt(o, as[1].i))
  _O(writeEnum(o, as[2].s))
  return true;
}

static bool
assignEnv(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(int) + sizeof(float);
  _O(writeHead(o, size))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeInt(o, as[1].i))
  _O(writeInt(o, as[2].i))
  _O(writeFloat(o, as[3].f))
  return true;
}

static bool
echo(ArgVal *as, Parse *p, Out *o) {
  char *startPos, *endPos = NULL;
  startPos = p->buf;
  p->buf = as[1].s;
  if (! parse(p)) { p->buf = startPos; showParseError(p); return false; }
  startPos = (char *)o->head;
  _O(writeHead(o, (int16_t)0))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(eval(p, o))
  endPos = (char *)o->head;
  o->head = (uint8_t *)startPos;
  _O(writeHead(o, (int16_t)(endPos - (startPos + sizeof(OUT_WORD)))))
  o->head = (uint8_t *)endPos;
  return true;
}

bool
eval(Parse *p, Out *o) {
  bool r = false;
  ArgVal *as = p->args;
  Fn f = as[0].i;
  r =
    f == F_NOTE_ON      ? noteOn(as++, o)  :
    f == F_NOTE_OFF     ? noteOff(as++, o) :
    f == F_ATTACK       ? setEnv(as, o)    :
    f == F_ATTACK_WAVE  ? setWave(as, o)   :
    f == F_DECAY        ? setEnv(as, o)    :
    f == F_DECAY_WAVE   ? setWave(as, o)   :
    f == F_ENV_ASSIGN   ? assignEnv(as, o) :
    f == F_ECHO         ? echo(as, p, o)   :
    f == F_KEY_CURVE    ? setWave(as, o)   :
    f == F_LOUDNESS     ? true             :
    f == F_AMPLITUDE    ? true             :
    f == F_MODULATE     ? true             :
    f == F_ENV_LOOP     ? true             :
    f == F_PITCH        ? true             :
    f == F_QUIT         ? true             :
    f == F_RELEASE      ? setEnv(as, o)    :
    f == F_RELEASE_WAVE ? setWave(as, o)   :
    f == F_SUSTAIN      ? setEnv(as, o)    :
    f == F_TOUCH        ? true             :
    f == F_TUNE         ? true             :
    f == F_WAVE         ? setWave(as,o)    : false;
  return r;
}

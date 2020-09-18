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
static OutResult noteOn(ArgVal *, Out *);
static OutResult noteOff(ArgVal *, Out *);
static OutResult setEnv(ArgVal *, Out *);
static OutResult setWave(ArgVal *, Out *);
static OutResult echo(ArgVal *, Parse *, Out *);

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
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[2].i - 1))))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeByte(o, (uint8_t)as[1].i))
  return OUT_SUCCESS;
}

static OutResult
noteOff(ArgVal *as, Out *o) {
  _O(boundI(0, MIDI_MAX, as[0].i))
  _O(boundI(1, MIDI_CHANNELS, as[1].i))
  _O(writeHead(o, (int16_t)3))
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[1].i - 1))))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeByte(o, (uint8_t)0))
  return OUT_SUCCESS;
}

static OutResult
setEnv(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(float) + sizeof(float);
  _O(writeHead(o, size))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  return OUT_SUCCESS;
}

static OutResult
setWave(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(int);
  _O(writeHead(o, size))
  _O(writeByte(o, (uint8_t)as[0].i))
  _O(writeInt(o, as[1].i))
  _O(writeEnum(o, as[2].s))
  return OUT_SUCCESS;
}

static OutResult
echo(ArgVal *as, Parse *p, Out *o) {
  char *startPos, *endPos = NULL;
  startPos = p->buf;
  p->buf = as[1].s;
  if (! parse(p)) { p->buf = startPos; showParseError(p); return OUT_ERROR; }
  startPos = (char *)o->head;
  _O(writeHead(o, (int16_t)0))
  _O(writeByte(o, (uint8_t)as[0].1))
  _O(eval(p, o))
  endPos = (char *)o->head;
  o->head = (uint8_t *)startPos;
  _O(writeHead(o, (int16_t)(endPos - (startPos + sizeof(OUT_WORD)))))
  o->head = (uint8_t *)endPos;
  return OUT_SUCCESS;
}

OutResult
eval(Parse *p, Out *o) {
  OutResult r = OUT_ERROR;
  ArgVal *as = p->args;
  Fn f = as[0].i;
  r =
    f == F_NOTE_ON      ? noteOn(as++, o)  :
    f == F_NOTE_OFF     ? noteOff(as++, o) :
    f == F_ATTACK       ? setEnv(as, o)    :
    f == F_ATTACK_WAVE  ? setWave(as, o)   :
    f == F_DECAY        ? setEnv(as, o)    :
    f == F_DECAY_WAVE   ? setWave(as, o)   :
    f == F_ENV_ASSIGN   ? true             :
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

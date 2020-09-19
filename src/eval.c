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
static bool loudness(ArgVal *, Out *);
static bool amplitude(ArgVal *, Out *);
static bool modulate(ArgVal *, Out *);
static bool setText(ArgVal *, Out *);
static bool pitch(ArgVal *, Out *);
static bool quit(ArgVal *, Out *);
static bool touch(ArgVal *, Out *);
static bool tune(ArgVal *, Out *);
static bool echo(ArgVal *, Parse *, Out *);

static bool
boundI(int n, int m, int x) {
  if (x < n || x > m) { boundIError(n, m, x); return false; }
  else                { return true; }
}

static bool
boundF(float n, float m, float x) {
  if (x < n || x > m) { boundFError(n, m, x); return false; }
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
  _O(boundI(0, MIDI_MAX, as[0].i));
  _O(boundI(0, MIDI_MAX, as[1].i));
  _O(boundI(1, MIDI_CHANNELS, as[2].i));
  _O(writeHead(o, (int16_t)3));
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[2].i - 1))));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, (uint8_t)as[1].i));
  return true;
}

static bool
noteOff(ArgVal *as, Out *o) {
  _O(boundI(0, MIDI_MAX, as[0].i));
  _O(boundI(1, MIDI_CHANNELS, as[1].i));
  _O(writeHead(o, (int16_t)3));
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[1].i - 1))));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, (uint8_t)0));
  return true;
}

static bool
setEnv(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(float) + sizeof(float);
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  return true;
}

static bool
setWave(ArgVal *as, Out *o) {
  int16_t size = (sizeof(uint8_t) *2) + sizeof(int);
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeEnum(o, as[2].s));
  return true;
}

static bool
assignEnv(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + sizeof(int) + sizeof(float);
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeInt(o, as[2].i));
  _O(writeFloat(o, as[3].f));
  return true;
}

static bool
loudness(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(float);
  _O(boundF(0.0f, 1.0f, as[1].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeFloat(o, as[1].f));
  return true;
}

static bool
amplitude(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + (sizeof(float) * 3);
  _O(boundF(0.0f, 1.0f, as[2].f));
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(boundF(0.0f, 1.0f, as[4].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  _O(writeFloat(o, as[4].f));
  return true;
}

static bool
modulate(ArgVal *as, Out *o) {
  int16_t size = (sizeof(uint8_t) * 2) + (sizeof(int) * 2) + sizeof(float);
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeInt(o, as[2].i));
  _O(writeFloat(o, as[3].f));
  _O(writeEnum(o, as[4].s));
  return true;
}

static bool
setText(ArgVal *as, Out *o) {
  int16_t size = (sizeof(uint8_t) * 2) + sizeof(int);
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeEnum(o, as[2].s));
  return true;
}

static bool
pitch(ArgVal *as, Out *o) {
  int16_t size = (sizeof(uint8_t) * 2) + sizeof(int) + (sizeof(float) * 2);
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  _O(writeEnum(o, as[4].s));
  return true;
}

static bool
quit(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t);
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  return true;
}

static bool
touch(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + (sizeof(float) * 2);
  _O(boundF(0.0f, 1.0f, as[2].f));
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  return true;
}

static bool
tune(ArgVal *as, Out *o) {
  int16_t size = sizeof(uint8_t) + sizeof(int) + (sizeof(float) * 2);
  _O(boundI(0, MIDI_MAX, as[1].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeInt(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  return true;
}

static bool
echo(ArgVal *as, Parse *p, Out *o) {
  char *startPos, *endPos = NULL;
  startPos = p->buf;
  p->buf = as[1].s;
  if (! parse(p)) { p->buf = startPos; showParseError(p); return false; }
  p->buf = startPos;
  startPos = (char *)o->head;
  _O(writeHead(o, (int16_t)0));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(eval(p, o));
  endPos = (char *)o->head;
  o->head = (uint8_t *)startPos;
  _O(writeHead(o, (int16_t)(endPos - (startPos + sizeof(OUT_WORD)))));
  o->head = (uint8_t *)endPos;
  return true;
}

void
resetEval(Out *o) {
  o->head = o->buf;
}

bool
eval(Parse *p, Out *o) {
  bool r = false;
  ArgVal *as = p->args;
  Fn f = as[0].i;
  r =
    f == F_NOTE_ON      ? noteOn(++as, o)  :
    f == F_NOTE_OFF     ? noteOff(++as, o) :
    f == F_ATTACK       ? setEnv(as, o)    :
    f == F_ATTACK_WAVE  ? setWave(as, o)   :
    f == F_DECAY        ? setEnv(as, o)    :
    f == F_DECAY_WAVE   ? setWave(as, o)   :
    f == F_ENV_ASSIGN   ? assignEnv(as, o) :
    f == F_ECHO         ? echo(as, p, o)   :
    f == F_KEY_CURVE    ? setWave(as, o)   :
    f == F_LOUDNESS     ? loudness(as, o)  :
    f == F_AMPLITUDE    ? amplitude(as, o) :
    f == F_MODULATE     ? modulate(as, o)  :
    f == F_ENV_LOOP     ? setText(as, o)   :
    f == F_PITCH        ? pitch(as, o)     :
    f == F_QUIT         ? quit(as, o)      :
    f == F_RELEASE      ? setEnv(as, o)    :
    f == F_RELEASE_WAVE ? setWave(as, o)   :
    f == F_SUSTAIN      ? setEnv(as, o)    :
    f == F_TOUCH        ? touch(as, o)     :
    f == F_TUNE         ? tune(as, o)      :
    f == F_WAVE         ? setWave(as,o)    : false;
  return r;
}

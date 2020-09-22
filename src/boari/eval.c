#include <err.h>
#include <stdbool.h>
#include <stdint.h>

/* This module makes use of the guard macro _O. Please refer to control.h for
 * more information. */

#include "../constants/funcs.h"
#include "../constants/magic.h"
#include "../constants/midi.h"
#include "control.h"
#include "eval.h"
#include "parse.h"
#include "output.h"
#include "types.h"

static bool boundI(int, int, int);
static bool boundF(float, float, float);
static void boundIError(int, int, int);
static void boundFError(float, float, float);
static bool noteOn(ArgVal *, Out *);
static bool noteOff(ArgVal *, Out *);
static bool setEnv(ArgVal *, Out *);
static bool assignEnv(ArgVal *, Out *);
static bool loudness(ArgVal *, Out *);
static bool amplitude(ArgVal *, Out *);
static bool modulate(ArgVal *, Out *);
static bool setEnvText(ArgVal *, Out *);
static bool setOscText(ArgVal *, Out *);
static bool pitch(ArgVal *, Out *);
static bool quit(ArgVal *, Out *);
static bool touch(ArgVal *, Out *);
static bool tune(ArgVal *, Out *);
static bool echo(ArgVal *, Parse *, Out *);

static bool
boundI(int n, int m, int x) {

/* Check if an integer ∈ [n, m]. */

  if (x < n || x > m) { boundIError(n, m, x); return false; }
  else                { return true; }
}

static bool
boundF(float n, float m, float x) {

/* Check if a float ∈ [n, m]. */

  if (x < n || x > m) { boundFError(n, m, x); return false; }
  else                { return true; }
}

static void
boundIError(int n, int m, int x) {

/* Invoked when an integer is out of range. */

  warnx("%d not between %d and %d", x, n, m);
}

static void
boundFError(float n, float m, float x) {

/* Invoked when a float is out of range. */

  warnx("%.3f not between %.3f and %.3f", x, n, m);
}

static bool
noteOn(ArgVal *as, Out *o) {

/* Write the n command to boar. Is identical to a MIDI note on event. */

  _O(boundI(0, MIDI_MAX, as[0].i));
  _O(boundI(0, MIDI_MAX, as[1].i));
  _O(boundI(1, MIDI_CHANNELS, as[2].i));
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[2].i - 1))));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, (uint8_t)as[1].i));

  return true;
}

static bool
noteOff(ArgVal *as, Out *o) {

/* Write the o command to boar. Is identical to a MIDI note off event.
 * Communicated as a note on with zero velocity, as opposed to an explicit
 * note off byte. This corresponds to the behavior exhibited by the author's
 * personal synthesizers and sequencers. */

  _O(boundI(0, MIDI_MAX, as[0].i));
  _O(boundI(1, MIDI_CHANNELS, as[1].i));
  _O(writeByte(o, (uint8_t)(MIDI_NOTE_ON + (as[1].i - 1))));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, (uint8_t)0));

  return true;
}

static bool
setEnv(ArgVal *as, Out *o) {

/* Write an envelope value command to boar: a, d, r, s */

  int16_t size = (sizeof(uint8_t) * 2) + (sizeof(float) * 2);

  _O(boundI(0, SIZE_ENVS, as[1].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));

  return true;
}

static bool
setEnvText(ArgVal *as, Out *o) {

/* Write an envelope text command to boar: A, D, R, O */

  int16_t size = sizeof(uint8_t) * 3;

  _O(boundI(0, SIZE_ENVS, as[1].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeEnum(o, as[2].s));

  return true;
}

static bool
setOscText(ArgVal *as, Out *o) {

/* Write an osc text command to boar: k, w */

  int16_t size = sizeof(uint8_t) * 3;

  _O(boundI(0, SIZE_OSCS, as[1].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeEnum(o, as[2].s));

  return true;
}

static bool
assignEnv(ArgVal *as, Out *o) {

/* Write the e command to boar. */

  int16_t size = (sizeof(uint8_t) * 3) + sizeof(float);

  _O(boundI(0, SIZE_ENVS, as[1].i));
  _O(boundI(0, SIZE_OSCS, as[2].i));
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeByte(o, as[2].i));
  _O(writeFloat(o, as[3].f));

  return true;
}

static bool
loudness(ArgVal *as, Out *o) {

/* Write the l command to boar. This will eventually be refactored to be
 * identical to the volume slider output of the JX-8P, which will allow for
 * more hardware control. */

  int16_t size = sizeof(uint8_t) + sizeof(float);

  _O(boundF(0.0f, 1.0f, as[1].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeFloat(o, as[1].f));

  return true;
}

static bool
amplitude(ArgVal *as, Out *o) {

/* Write the L command to boar. */

  int16_t size = (sizeof(uint8_t) * 2) + (sizeof(float) * 3);

  _O(boundI(0, SIZE_OSCS, as[1].i));
  _O(boundF(0.0f, 1.0f, as[2].f));
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(boundF(0.0f, 1.0f, as[4].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  _O(writeFloat(o, as[4].f));

  return true;
}

static bool
modulate(ArgVal *as, Out *o) {

/* Write the m command to boar. */

  int16_t size = (sizeof(uint8_t) * 4) + sizeof(float);

  _O(boundI(0, SIZE_OSCS, as[1].i));
  _O(boundI(0, SIZE_OSCS, as[2].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeByte(o, as[2].i));
  _O(writeFloat(o, as[3].f));
  _O(writeEnum(o, as[4].s));

  return true;
}

static bool
pitch(ArgVal *as, Out *o) {

/* Write the p command to boar. */

  int16_t size = (sizeof(uint8_t) * 3) + (sizeof(float) * 2);

  _O(boundI(0, SIZE_OSCS, as[1].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));
  _O(writeEnum(o, as[4].s));

  return true;
}

static bool
quit(ArgVal *as, Out *o) {

/* Write the q command to boar. */

  int16_t size = sizeof(uint8_t);

  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));

  return true;
}

static bool
touch(ArgVal *as, Out *o) {

/* Write the t command to boar. */

  int16_t size = (sizeof(uint8_t) * 2) + (sizeof(float) * 2);

  _O(boundI(0, SIZE_OSCS, as[1].i));
  _O(boundF(0.0f, 1.0f, as[2].f));
  _O(boundF(0.0f, 1.0f, as[3].f));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));

  return true;
}

static bool
tune(ArgVal *as, Out *o) {

/* Write the T command to boar. */

  int16_t size = (sizeof(uint8_t) * 2) + (sizeof(float) * 2);

  _O(boundI(0, MIDI_MAX, as[1].i));
  _O(writeHead(o, size));
  _O(writeByte(o, (uint8_t)as[0].i));
  _O(writeByte(o, as[1].i));
  _O(writeFloat(o, as[2].f));
  _O(writeFloat(o, as[3].f));

  return true;
}

static bool
echo(ArgVal *as, Parse *p, Out *o) {

/* Write the E command to boar. This is by far the most painful function to
 * implement, as it defers parsing to eval time. parse() is called within this
 * function—possibly recursively—until a flat stream of boar messages is
 * produced. It is important to ensure that the `buf` of the parse() struct is
 * properly reset when exiting from recursive scopes, and that the payload
 * sizes of nested messages are accurate. */

  char *startPos, *endPos = NULL;

  startPos = p->buf;
  p->buf = as[1].s;
  if (! parse(p)) { p->buf = startPos; showParseError(p); return false; }
  p->buf = startPos;
  startPos = (char *)o->head;
  _O(writeHead(o, (int16_t)0));
  _O(writeByte(o, (uint8_t)F_ECHO));
  _O(eval(p, o));
  endPos = (char *)o->head;
  o->head = (uint8_t *)startPos;
  _O(writeHead(o, (int16_t)(endPos - (startPos + sizeof(BOAR_WORD)))));
  o->head = (uint8_t *)endPos;

  return true;
}

void
resetEval(Out *o) {

/* Return the write head back to the start of the output buffer. */

  o->head = o->buf;
}

bool
eval(Parse *p, Out *o) {

/* Match a func enum to its corresponding output procedure. Run it. */

  bool r = false;
  ArgVal *as = p->args;
  Fn f = as[0].i;

  r =
    f == F_NOTE_ON      ? noteOn(++as, o)   :
    f == F_NOTE_OFF     ? noteOff(++as, o)  :
    f == F_ATTACK       ? setEnv(as, o)     :
    f == F_ATTACK_WAVE  ? setEnvText(as, o) :
    f == F_DECAY        ? setEnv(as, o)     :
    f == F_DECAY_WAVE   ? setEnvText(as, o) :
    f == F_ENV_ASSIGN   ? assignEnv(as, o)  :
    f == F_ECHO         ? echo(as, p, o)    :
    f == F_KEY_CURVE    ? setOscText(as, o) :
    f == F_LOUDNESS     ? loudness(as, o)   :
    f == F_AMPLITUDE    ? amplitude(as, o)  :
    f == F_MODULATE     ? modulate(as, o)   :
    f == F_ENV_LOOP     ? setEnvText(as, o) :
    f == F_PITCH        ? pitch(as, o)      :
    f == F_QUIT         ? quit(as, o)       :
    f == F_RELEASE      ? setEnv(as, o)     :
    f == F_RELEASE_WAVE ? setEnvText(as, o) :
    f == F_SUSTAIN      ? setEnv(as, o)     :
    f == F_TOUCH        ? touch(as, o)      :
    f == F_TUNE         ? tune(as, o)       :
    f == F_WAVE         ? setOscText(as,o)  : false;

  return r;
}

bool
loop(Parse *p) {

/* Check if the q command has been run. If not, the REPL will be allowed to
 * continue reading and evaluating input. */

  return (p->args[0].i != F_QUIT);
}

#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "enums.h"
#include "output.h"
#include "signatures.h"
#include "types.h"

static bool isBounded(Out *, int);
static bool writeInt(Out *, int);
static bool writeShort(Out *, int16_t);
static bool writeFloat(Out *, float);
static bool writeEnum(Out *, char *);
static bool writeError(void);

static bool
isBounded(Out *o, int n) {
  if (n + (o->head - o->buf) >= o->limit) { warnx("too long"); return false; }
  else                                    { return true; }
}

static bool
writeInt(Out *o, int n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

static bool
writeShort(Out *o, int16_t n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

static bool
writeFloat(Out *o, float f) {
  float *os = (float *)o->head;
  if (isBounded(o, sizeof(f))) { *os = f; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

static bool
writeEnum(Out *o, char *s) {
  int n = toI(s);
  return n == ENUM_UNKNOWN ? false : writeInt(o, n);
}

static bool
writeError(void) {
  warnx("internal output type error");
  return false;
}

static bool
writeArg(Out *o, ArgType t, ArgVal a) {
  return
    t == ARG_UINT || t == ARG_INT     ? writeInt(o, a.i)   :
    t == ARG_UFLOAT || t == ARG_FLOAT ? writeFloat(o, a.f) :
    t == ARG_TEXT                     ? writeEnum(o, a.s)  : writeError();
}

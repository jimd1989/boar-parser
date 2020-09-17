#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "enums.h"
#include "output.h"
#include "signatures.h"
#include "types.h"

static bool isBounded(Out *, int);
static OutResult writeInt(Out *, int);
static OutResult writeShort(Out *, int16_t);
static OutResult writeFloat(Out *, float);
static OutResult writeEnum(Out *, char *);
static OutResult writeError(void);

static bool
isBounded(Out *o, int n) {
  if (n + (o->head - o->buf) >= o->limit) { warnx("too long"); return false; }
  else                                    { return true; }
}

static OutResult
writeInt(Out *o, int n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return OUT_ERROR; }
  return OUT_SUCCESS;
}

static OutResult
writeShort(Out *o, int16_t n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return OUT_ERROR; }
  return OUT_SUCCESS;
}

static OutResult
writeFloat(Out *o, float f) {
  float *os = (float *)o->head;
  if (isBounded(o, sizeof(f))) { *os = f; os++; o->head = (uint8_t *)os; }
  else                         { return OUT_ERROR; }
  return OUT_SUCCESS;
}

static OutResult
writeEnum(Out *o, char *s) {
  int n = toI(s);
  return n == ENUM_UNKNOWN ? OUT_ERROR : writeInt(o, n);
}

static OutResult
writeError(void) {
  warnx("internal output type error");
  return OUT_ERROR;
}

static OutResult
writeArg(Out *o, ArgType t, ArgVal a) {
  return
    t == ARG_ANY                      ? OUT_RECURSE        :
    t == ARG_UINT || t == ARG_INT     ? writeInt(o, a.i)   :
    t == ARG_UFLOAT || t == ARG_FLOAT ? writeFloat(o, a.f) :
    t == ARG_TEXT                     ? writeEnum(o, a.s)  : writeError();
}

OutResult
writeFunc(Out *o, Sig g, ArgVal *as) {

/* Parent calling function should keep pointer to o->head, which will allow
 * backtracking and filling in correct size slots in the event of recursion. */  

  int n = 0;
  uint8_t *startPos, *endPos = NULL;
  OutResult r = OUT_ERROR;
  startPos = o->head;
  writeInt(o, OUT_WORD);
  writeShort(o, (int16_t)0);
  for (; n < g.count; n++) {
    r = writeArg(o, g.args[n], as[n]);
    if (r == OUT_ERROR)        { o->head = startPos; return r; }
    else if (r == OUT_RECURSE) { return r; }
  }
  endPos = o->head;
  o->head = startPos + sizeof(OUT_WORD);
  writeShort(o, endPos - o->head);
  o->head = endPos;
  return true;
}

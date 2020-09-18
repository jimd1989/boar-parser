#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "enums.h"
#include "output.h"
#include "parse.h"
#include "signatures.h"
#include "types.h"

static bool isBounded(Out *, int);
static bool writeShort(Out *, int16_t);

static bool
isBounded(Out *o, int n) {
  if (n + (o->head - o->buf) >= o->limit) { warnx("too long"); return false; }
  else                                    { return true; }
}

bool
writeInt(Out *o, int n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

bool
writeShort(Out *o, int16_t n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

bool
writeByte(Out *o, uint8_t n) {
  uint8_t *os = o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = os; }
  else                         { return false; }
  return true;
}

bool
writeFloat(Out *o, float f) {
  float *os = (float *)o->head;
  if (isBounded(o, sizeof(f))) { *os = f; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

bool
writeEnum(Out *o, char *s) {
  int n = toI(s);
  return n == ENUM_UNKNOWN ? false : writeInt(o, n);
}

/*bool
writeArg(Out *o, ArgType t, ArgVal a) {
  return
    t == ARG_ANY                      ? OUT_RECURSE                 :
    t == ARG_UINT || t == ARG_INT     ? writeInt(o, a.i)            :
    t == ARG_SIZE                     ? writeShort(o, (int16_t)a.i) :
    t == ARG_UFLOAT || t == ARG_FLOAT ? writeFloat(o, a.f)          :
    t == ARG_TEXT                     ? writeEnum(o, a.s)           : error();
} */

bool
writeHead(Out *o, int16_t n) {
  if (writeInt(o, OUT_WORD) == false) { return false; }
  return writeShort(o, n);
}

bool
writeFunc(Out *o) {
  return !fwrite(o->buf, 1, o->head - o->buf, o->out) ? false : true;
}

/* static bool
recurse(Out *o, Parse *p) {
  bool r = false;
  char *startPos = p->buf;
  p->buf = p->args[1].s; 
  parse(p);              
                         
  r = writeFunc(o, p);
  p->buf = startPos;
  return r;
}

static bool
writeFunc(Out *o, Parse *p) {
  int n = 0;
  uint8_t *startPos, *endPos = NULL;
  Sig g = *p->sig;
  ArgVal *as = p->args;
  bool r = false;
  startPos = o->head;
  writeInt(o, OUT_WORD);
  writeShort(o, (int16_t)0);
  for (as++; n < g.count; n++) {
    r = writeArg(o, g.args[n], as[n]);
    if (r == false)            { o->head = startPos; return r; }
    else if (r == OUT_RECURSE) { return r; }
  }
  endPos = o->head;
  o->head = startPos + sizeof(OUT_WORD);
  writeShort(o, endPos - o->head);
  o->head = endPos;
  return true;
} */

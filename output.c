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
  if (n + (o->head - o->buf) >= SIZE_OUT) { warnx("too long"); return false; }
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
  return n == ENUM_UNKNOWN ? false : writeByte(o, n);
}

bool
writeHead(Out *o, int16_t n) {
  if (writeInt(o, OUT_WORD) == false) { return false; }
  return writeShort(o, n);
}

bool
writeFunc(Out *o) {
  return !fwrite(o->buf, 1, o->head - o->buf, stdout) ? false : true;
}

Out
makeOut(void) {
  Out o = {{0}};
  o.head = o.buf;
  return o;
}

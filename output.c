#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "output.h"

static bool isBounded(Out *, int);

static bool
isBounded(Out *o, int n) {
  if (n + (o->head - o->buf) >= o->limit) { warnx("too long"); return false; }
  else                                    { return true; }
}

bool
outI(Out *o, int n) {
  int *os = (int *)o->head;
  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

bool
outF(Out *o, float f) {
  float *os = (float *)o->head;
  if (isBounded(o, sizeof(f))) { *os = f; os++; o->head = (uint8_t *)os; }
  else                         { return false; }
  return true;
}

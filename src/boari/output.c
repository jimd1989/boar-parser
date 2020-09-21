#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../constants/enums.h"
#include "../constants/magic.h"
#include "output.h"
#include "parse.h"
#include "signatures.h"
#include "text.h"
#include "types.h"

static bool isBounded(Out *, int);
static bool writeShort(Out *, int16_t);

static bool
isBounded(Out *o, int n) {

/* Where `n` is the size of a payload, check if `n` is within the bounds of
 * the output buffer. */

  if (n + (o->head - o->buf) >= SIZE_OUT) { warnx("too long"); return false; }
  else                                    { return true; }
}

bool
writeInt(Out *o, int n) {

/* Write a 4 byte int to the output stream. */  

  int *os = (int *)o->head;

  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }

  return true;
}

bool
writeShort(Out *o, int16_t n) {

/* Write a 2 byte int to the output stream. */  

  int16_t *os = (int16_t *)o->head;

  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = (uint8_t *)os; }
  else                         { return false; }

  return true;
}

bool
writeByte(Out *o, uint8_t n) {

/* Write a 1 byte int to the output stream. */  

  uint8_t *os = o->head;

  if (isBounded(o, sizeof(n))) { *os = n; os++; o->head = os; }
  else                         { return false; }

  return true;
}

bool
writeFloat(Out *o, float f) {

/* Write a 4 byte float to the output stream. */

  float *os = (float *)o->head;

  if (isBounded(o, sizeof(f))) { *os = f; os++; o->head = (uint8_t *)os; }
  else                         { return false; }

  return true;
}

bool
writeEnum(Out *o, char *s) {

/* Write a string as a 1 byte int to the output stream. */  
  
  int n = toI(s);
  return n == ENUM_UNKNOWN ? false : writeByte(o, n);
}

bool
writeHead(Out *o, int16_t n) {

/* Write the magic word and payload size `n` to the output stream, signalling
 * the start of a boar message. */

  if (writeInt(o, BOAR_WORD) == false) { return false; }
  return writeShort(o, n);
}

bool
writeFunc(Out *o) {

/* Print the full output stream to stdout. */

  int n = fwrite(o->buf, 1, o->head - o->buf, stdout);
 
  if (n) { fflush(stdout); return true;}
  else   { return false;}
}

Out
makeOut(void) {

/* Initialize an output stream writer. */

  Out o = {{0}};

  o.head = o.buf;

  return o;
}

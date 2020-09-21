#pragma once

/* Writing ArgVals into a binary output stream. */

#include <stdbool.h>
#include <stdint.h>

#include "../constants/sizes.h"
#include "parse.h"
#include "types.h"

typedef struct Out {

/* boar messages are written to `buf` as binary data. `head` points to the
 * current write position. When all values have been written, the entire
 * stretch of data is printed to stdout. */

  uint8_t         buf[SIZE_OUT];
  uint8_t       * head;
} Out;

#define OUT_WORD 1918988130 /* magic word "boar" for output header */

bool writeInt(Out *, int n);
bool writeByte(Out *, uint8_t n);
bool writeFloat(Out *, float);
bool writeEnum(Out *, char *);
bool writeHead(Out *, int16_t);
bool writeFunc(Out *);
Out makeOut(void);

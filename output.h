#pragma once

#include <stdint.h>

#include "sizes.h"

typedef struct Out {
  uint8_t         buf[SIZE_LINE];
  uint8_t       * head;
  int             limit;
} Out;

#define OUT_WORD 1918988130 /* magic word "boar" for output header */

bool outI(Out *, int);
bool outF(Out *, float);

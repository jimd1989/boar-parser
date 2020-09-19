#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "parse.h"
#include "sizes.h"
#include "types.h"

typedef struct Out {
  uint8_t         buf[SIZE_OUT];
  uint8_t       * head;
  FILE          * out;
} Out;

#define OUT_WORD 1918988130 /* magic word "boar" for output header */

bool writeInt(Out *, int n);
bool writeByte(Out *, uint8_t n);
bool writeFloat(Out *, float);
bool writeEnum(Out *, char *);
bool writeHead(Out *, int16_t);
bool writeFunc(Out *);
Out makeOut(void);

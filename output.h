#pragma once

#include <stdint.h>

#include "sizes.h"

typedef enum OutResult {
  OUT_ERROR = 0,
  OUT_RECURSE,
  OUT_SUCCESS
} OutResult;

typedef struct Out {
  uint8_t         buf[SIZE_OUT];
  uint8_t       * head;
  int             limit;
} Out;

#define OUT_WORD 1918988130 /* magic word "boar" for output header */

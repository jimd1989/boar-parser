#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "../constants/sizes.h"

typedef struct In {
  uint8_t         buf[SIZE_OUT];
  uint8_t       * head;
  int             size;
  int             chan;
  int16_t         cmdSize;
  uint8_t         cmd;
} In;

void advance(In *, int);
bool input(In *);
In makeIn(void);

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "../constants/sizes.h"

typedef struct In {
  uint8_t         buf[SIZE_OUT];
  uint8_t       * head;
  int             size;
} In;

bool input(In *);
In makeIn(void);
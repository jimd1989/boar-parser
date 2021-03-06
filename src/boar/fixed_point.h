#pragma once

#include <stdint.h>

/* Representing wave phase as 16.16 format fixed point numbers. */

/* Scale a float into 16.16. */
#define FIXED_SCALE 16

/* Isolate the fractional part of a fixed num. */
#define FIXED_FRAC_MASK ((1 << FIXED_SCALE) - 1)
#define FIXED_FRAC(X) ((X) & FIXED_FRAC_MASK)

/* Isolate the integer part of a fixed num. */
#define FIXED_INT(X) ((X) >> FIXED_SCALE)

/* Multiply two 16.16 numbers. */
#define FIXED_MUL(X, Y) (((int64_t)(X) * (int64_t)(Y)) >> 16)

/* Multiply 16.16 number against 1.31 number. */
#define FIXED_MUL_ONE(X, Y) (((int64_t)(X) * (int64_t)(Y)) >> 32)

/* Convert float to 16.16 number. */
#define FIXED_FROM_FLOAT(X) ((uint32_t)((X) * (float)(1 << FIXED_SCALE)))


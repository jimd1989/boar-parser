#pragma once

/* Generating and reading from wavetables. */

/* Size of wavetables should be 2^n to take advantage of bit shifting. */
#define TABLE_SIZE 4096

/* Turn a 32 bit int representing wave phase into an index of wavetable. */
#define TABLE_SHIFT 20
#define TABLE_INDEX(X) ((X) >> TABLE_SHIFT)

/* Add this value to wave phase at wavetable index n to get phase at n+1. */
#define TABLE_INC (1 << TABLE_SHIFT)


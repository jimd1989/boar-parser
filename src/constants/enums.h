#pragma once

/* Numerical equivalents of user-provided text tokens. Ideally these values
 * would all be placed in a single enum range, allowing for stronger type
 * checking, but the default argument behavior of the boari Sig struct demands
 * that unspecified text be a null pointer. Thus every enum must alias one of
 * its members against zero. */

#include <limits.h>

#include "sizes.h"

typedef enum OnOff {

/* Allows words like on/off yes/no to be used instead of 1/0. */

  ENUM_OFF = 0,
  ENUM_ON
} OnOff;

typedef enum WaveType {

/* Allows waves to be specified by name rather than numbers. Because reverse
 * waves are passed as negative enum values, and UCHAR_MAX is used to signal
 * an unknown enum value, no wave can be represented by 1, as -1 = UCHAR_MAX. */

  ENUM_FLAT = 0,
  ENUM_SINE = 2,
  ENUM_SQUARE,
  ENUM_TRIANGLE,
  ENUM_RAMP,
  ENUM_EXPONENTIAL,
  ENUM_LOGARITHMIC,
  ENUM_NOISE
} WaveType;

typedef enum ModType {

/* The type of modulation that will take place between two oscillators. */

  ENUM_MOD = 0,
  ENUM_MIX,
  ENUM_SYNC,
  ENUM_AMP
} ModType;

#define ENUM_UNKNOWN UCHAR_MAX /* Returned by toI() when no enum matches. */

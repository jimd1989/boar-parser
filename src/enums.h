#pragma once

/* Encoding textual tokens to enums that boar can understand. Most of these
 * will be duplicated on the boar server as well. */

/* TODO: make it so that no enum can be a synonym for another, like how
 * 'flat' and 'no' are both zero valued. This may make it painful to fit all
 * textual representations inside a single byte, however. Especially if there
 * are multiple words for the same enum, like 'rand' and 'noise'. */

#include <limits.h>

typedef enum OnOff {

/* Allows words like on/off yes/no to be used instead of 1/0. */

  ENUM_OFF = 0,
  ENUM_ON
} OnOff;

typedef enum WaveType {

/* Allows waves to be specified by name rather than numbers. */

  ENUM_FLAT = 0,
  ENUM_SINE,
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

#define ENUM_UNKNOWN INT_MAX

int toI(char *);

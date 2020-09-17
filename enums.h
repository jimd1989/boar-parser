#pragma once

#include <limits.h>

typedef enum OnOff {
  ENUM_OFF = 0,
  ENUM_ON
} OnOff;

typedef enum WaveType {
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
  ENUM_MOD = 0,
  ENUM_MIX,
  ENUM_SYNC,
  ENUM_AMP
} ModType;

#define ENUM_UNKNOWN INT_MAX

int toI(char *);

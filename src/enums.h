#pragma once

/* Encoding textual tokens to enums that boar can understand. Most of these
 * will be duplicated on the boar server as well. */

/* TODO: make it so that no enum can be a synonym for another, like how
 * 'flat' and 'no' are both zero valued. This may make it painful to fit all
 * textual representations inside a single byte, however. */

#include <limits.h>
#include <stdint.h>

#include "sizes.h"

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

typedef struct EnumDef {

/* Used to match a text token `key` against an enum `val`. */

  char          * key;
  uint8_t         val;
} EnumDef;

#define ENUM_UNKNOWN UCHAR_MAX /* Returned by toI() when no enum matches. */

/* Master list of all possible enums, ordered alphabetically so that it can be
 * binary searched against. */
static const EnumDef ENUMS[SIZE_ENUMS] = {
  {"amp",          ENUM_AMP},
  {"exp",          ENUM_EXPONENTIAL},
  {"exponential",  ENUM_EXPONENTIAL},
  {"fixed",        ENUM_ON},
  {"flat",         ENUM_FLAT},
  {"log",          ENUM_LOGARITHMIC},
  {"logarithmic",  ENUM_LOGARITHMIC},
  {"mix",          ENUM_MIX},
  {"mod",          ENUM_MOD},
  {"no",           ENUM_OFF},
  {"noise",        ENUM_NOISE},
  {"off",          ENUM_OFF},
  {"on",           ENUM_ON },
  {"ramp",         ENUM_RAMP},
  {"rand",         ENUM_NOISE},
  {"random",       ENUM_NOISE},
  {"rexp",         ENUM_EXPONENTIAL * -1},
  {"rexponential", ENUM_EXPONENTIAL * -1},
  {"rlog",         ENUM_LOGARITHMIC * -1},
  {"rlogarithmic", ENUM_LOGARITHMIC * -1},
  {"rramp",        ENUM_RAMP * -1},
  {"rsaw",         ENUM_RAMP * -1},
  {"rsin",         ENUM_SINE * -1},
  {"rsine",        ENUM_SINE * -1},
  {"rsq",          ENUM_SQUARE * -1},
  {"rsquare",      ENUM_SQUARE * -1},
  {"rtri",         ENUM_TRIANGLE * -1},
  {"rtriangle",    ENUM_TRIANGLE * -1},
  {"saw",          ENUM_RAMP},
  {"silence",      ENUM_FLAT},
  {"sin",          ENUM_SINE},
  {"sine",         ENUM_SINE},
  {"sq",           ENUM_SQUARE},
  {"square",       ENUM_SQUARE},
  {"sync",         ENUM_SYNC},
  {"tri",          ENUM_TRIANGLE},
  {"triangle",     ENUM_TRIANGLE},
  {"yes",          ENUM_ON},
};

uint8_t toI(char *);

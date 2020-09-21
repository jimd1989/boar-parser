#pragma once

/* Encoding textual tokens to enums that boar can understand. */

#include <limits.h>
#include <stdint.h>

#include "../constants/enums.h"
#include "../constants/sizes.h"

typedef struct EnumDef {

/* Used to match a text token `key` against an enum `val`. */

  char          * key;
  uint8_t         val;
} EnumDef;

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

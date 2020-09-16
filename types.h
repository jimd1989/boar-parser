#pragma once

typedef enum ArgFlag {
  ARG_NUMBER    = (1 << 0),
  ARG_FLOATING  = (1 << 1),
  ARG_SIGNED    = (1 << 2),
  ARG_ALPHA     = (1 << 3),
  ARG_OTHER     = (1 << 4),
  ARG_ANYTHING  = (1 << 5)
} ArgFlag;

typedef enum ArgType {
  ARG_NIL    = 0,
  ARG_UINT   = ARG_NUMBER,
  ARG_UFLOAT = ARG_NUMBER | ARG_FLOATING,
  ARG_INT    = ARG_NUMBER | ARG_SIGNED,
  ARG_FLOAT  = ARG_NUMBER | ARG_SIGNED | ARG_FLOATING,
  ARG_TEXT   = ARG_ALPHA,
  ARG_ANY    = ARG_ANYTHING
} ArgType;

typedef struct ArgVal {
  int     i;
  float   f;
  char  * s;
} ArgVal;

char * showArgType(ArgType);

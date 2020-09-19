#pragma once

/* Representing textual tokens as concrete data. */

typedef enum ArgFlag {

/* An ArgFlag describes one (of potentially many) features of a token, such as
 * whether it is a number, positive/negative, etc. */

  ARG_NUMBER    = (1 << 0), /* token contains digit [0-9]          */
  ARG_FLOATING  = (1 << 1), /* token contains '.'                  */
  ARG_SIGNED    = (1 << 2), /* token contains '-'                  */
  ARG_ALPHA     = (1 << 3), /* token contains char [A-z]           */
  ARG_OTHER     = (1 << 4), /* token contains anything else        */
  ARG_ANYTHING  = (1 << 5)  /* not used; specified for consistency */
} ArgFlag;

typedef enum ArgType {

/* ArgTypes are composites of ArgFlags. They are the actual types used
 * throughout the interpreter. */

  ARG_NIL    = 0,                                      /* no argument     */
  ARG_UINT   = ARG_NUMBER,                             /* positive int    */
  ARG_UFLOAT = ARG_NUMBER | ARG_FLOATING,              /* positive float  */
  ARG_INT    = ARG_NUMBER | ARG_SIGNED,                /* signed int      */
  ARG_FLOAT  = ARG_NUMBER | ARG_SIGNED | ARG_FLOATING, /* signed float    */
  ARG_TEXT   = ARG_ALPHA,                              /* alphabetic text */
  ARG_ANY    = ARG_ANYTHING                            /* any input       */
} ArgType;

typedef struct ArgVal {

/* An ArgVal is the actual value of the parsed token, encoded as an int, float,
 * or string based upon its ArgType. */

  int     i;
  float   f;
  char  * s;
} ArgVal;

char * showArgType(ArgType);

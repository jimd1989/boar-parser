#pragma once

/* Checking if the tokens provided to a function are correctly typed. */

#include <stdlib.h>

#include "nums.h"
#include "../constants/sizes.h"
#include "types.h"

typedef struct Sig {

/* A Sig is an of ArgTypes, `count` items long, associated with a specific
 * function. The function will only be evaluated if its arguments match those
 * specified in the Sig. Some functions can be called with omitted arguments,
 * only needing `required` parameters. For all arguments past `required`, the
 * interpreter will select from a default value specified in the Sig's
 * `defaults` array. */
  
  const int       count;
  const int       required;
  const ArgType * args;
  const ArgVal  * defaults;
} Sig;


#define SIG_NULL {0 , 0, NULL, NULL} /* Blank Sig */
#define SIG_NULL_POS 26              /* Points to a blank Sig index */

/* Default argument arrays to be used across Sigs */
static const ArgVal SIG_ZERO_DEFS[1] = {{0}};
static const ArgVal SIG_ONE_DEFS[1] = {{NUM_ONE}};

/* Sig expecting any input */
static const ArgType SIG_ANY_ARGS[1] = {ARG_ANY};
#define SIG_ANY {1, 1, SIG_ANY_ARGS, NULL}

/* Sig expecting float+ */
static const ArgType SIG_UF_ARGS[1] = {ARG_UFLOAT};
#define SIG_UF {1, 1, SIG_UF_ARGS, NULL}

/* Sig expecting int+ float+ */
static const ArgType SIG_UI_UF_ARGS[3] = {ARG_UINT, ARG_UFLOAT};
#define SIG_UI_UF {2, 2, SIG_UI_UF_ARGS, NULL} 

/* Sig expecting int+ text */
static const ArgType SIG_UI_T_ARGS[2] = {ARG_UINT, ARG_TEXT};
#define SIG_UI_T {2, 2, SIG_UI_T_ARGS, NULL}

/* Sig for envelope functions */
static const
ArgType SIG_ENV_ASSIGN_ARGS[4] = {ARG_UINT, ARG_UINT, ARG_TEXT, ARG_UFLOAT};
static const ArgVal SIG_ENV_ASSIGN_DEFS[2] = {{0}, {NUM_ONE}};
#define SIG_ENV_ASSIGN {4, 2, SIG_ENV_ASSIGN_ARGS, SIG_ENV_ASSIGN_DEFS}

/* Sig for modulate function */
static const ArgType
SIG_MODULATE_ARGS[4] = {ARG_UINT, ARG_UINT, ARG_UFLOAT, ARG_TEXT};
#define SIG_MODULATE {4, 3, SIG_MODULATE_ARGS, SIG_ZERO_DEFS}

/* Sig for note on */
static const ArgType SIG_NOTE_ON_ARGS[3] = {ARG_UINT, ARG_UINT, ARG_UINT};
static const ArgVal SIG_NOTE_ON_DEFS[2] = {{127}, {1}};
#define SIG_NOTE_ON {3, 1, SIG_NOTE_ON_ARGS, SIG_NOTE_ON_DEFS}

/* Sig for note off */
static const ArgType SIG_NOTE_OFF_ARGS[2] = {ARG_UINT, ARG_UINT};
static const ArgVal SIG_NOTE_OFF_DEFS[1] = {{1}};
#define SIG_NOTE_OFF {2, 1, SIG_NOTE_OFF_ARGS, SIG_NOTE_OFF_DEFS}

/* Sig for set amplitude function */
static const ArgType
SIG_AMPLITUDE_ARGS[3] = {ARG_UINT, ARG_UFLOAT, ARG_FLOAT};
#define SIG_AMPLITUDE {3, 2, SIG_AMPLITUDE_ARGS, SIG_ZERO_DEFS}

/* Sig for set pitch function */
static const ArgType
SIG_PITCH_ARGS[3] = {ARG_UINT, ARG_UFLOAT, ARG_TEXT};
#define SIG_PITCH {3, 2, SIG_PITCH_ARGS, SIG_ZERO_DEFS}

/* There are three alphabets representing boar commands: A/A./A:
 * When a command of any of these forms is encountered, its respective signature
 * is looked up in one of the following three arrays. */
static const Sig SIG_PURE[SIZE_FS] = {
  SIG_UI_T,       /* A */
  SIG_NULL,       /* B */
  SIG_NULL,       /* C */
  SIG_UI_T,       /* D */
  SIG_ANY,        /* E */
  SIG_NULL,       /* F */
  SIG_NULL,       /* G */
  SIG_NULL,       /* H */
  SIG_NULL,       /* I */
  SIG_NULL,       /* J */
  SIG_NULL,       /* K */
  SIG_AMPLITUDE,  /* L */
  SIG_NULL,       /* M */
  SIG_NULL,       /* N */
  SIG_UI_T,       /* O */
  SIG_NULL,       /* P */
  SIG_NULL,       /* Q */
  SIG_UI_T,       /* R */
  SIG_NULL,       /* S */
  SIG_UI_UF,      /* T */
  SIG_NULL,       /* U */
  SIG_NULL,       /* V */
  SIG_NULL,       /* W */
  SIG_NULL,       /* X */
  SIG_NULL,       /* Y */
  SIG_NULL,       /* Z */
  SIG_NULL,       /* ignored */
  SIG_NULL,       /* ignored */
  SIG_NULL,       /* ignored */
  SIG_NULL,       /* ignored */
  SIG_NULL,       /* ignored */
  SIG_NULL,       /* ignored */
  SIG_UI_UF,      /* a */
  SIG_NULL,       /* b */
  SIG_NULL,       /* c */
  SIG_UI_UF,      /* d */
  SIG_ENV_ASSIGN, /* e */
  SIG_NULL,       /* f */
  SIG_NULL,       /* g */
  SIG_NULL,       /* h */
  SIG_NULL,       /* i */
  SIG_NULL,       /* j */
  SIG_UI_T,       /* k */
  SIG_UF,         /* l */
  SIG_MODULATE,   /* m */
  SIG_NOTE_ON,    /* n */
  SIG_NOTE_OFF,   /* o */
  SIG_PITCH,      /* p */
  SIG_NULL,       /* q */
  SIG_UI_UF,      /* r */
  SIG_UI_UF,      /* s */
  SIG_UI_UF,      /* t */
  SIG_NULL,       /* u */
  SIG_NULL,       /* v */
  SIG_UI_T,       /* w */
  SIG_NULL,       /* x */
  SIG_NULL,       /* y */
  SIG_NULL        /* z */
};

static const Sig SIG_PERIOD[SIZE_FS] = {
  SIG_NULL, /* A. */
  SIG_NULL, /* B. */
  SIG_NULL, /* C. */
  SIG_NULL, /* D. */
  SIG_NULL, /* E. */
  SIG_NULL, /* F. */
  SIG_NULL, /* G. */
  SIG_NULL, /* H. */
  SIG_NULL, /* I. */
  SIG_NULL, /* J. */
  SIG_NULL, /* K. */
  SIG_NULL, /* L. */
  SIG_NULL, /* M. */
  SIG_NULL, /* N. */
  SIG_NULL, /* O. */
  SIG_NULL, /* P. */
  SIG_NULL, /* Q. */
  SIG_NULL, /* R. */
  SIG_NULL, /* S. */
  SIG_NULL, /* T. */
  SIG_NULL, /* U. */
  SIG_NULL, /* V. */
  SIG_NULL, /* W. */
  SIG_NULL, /* X. */
  SIG_NULL, /* Y. */
  SIG_NULL, /* Z. */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* a. */
  SIG_NULL, /* b. */
  SIG_NULL, /* c. */
  SIG_NULL, /* d. */
  SIG_NULL, /* e. */
  SIG_NULL, /* f. */
  SIG_NULL, /* g. */
  SIG_NULL, /* h. */
  SIG_NULL, /* i. */
  SIG_NULL, /* j. */
  SIG_NULL, /* k. */
  SIG_NULL, /* l. */
  SIG_NULL, /* m. */
  SIG_NULL, /* n. */
  SIG_NULL, /* o. */
  SIG_NULL, /* p. */
  SIG_NULL, /* q. */
  SIG_NULL, /* r. */
  SIG_NULL, /* s. */
  SIG_NULL, /* t. */
  SIG_NULL, /* u. */
  SIG_NULL, /* v. */
  SIG_NULL, /* w. */
  SIG_NULL, /* x. */
  SIG_NULL, /* y. */
  SIG_NULL  /* z. */
};

static const Sig SIG_COLON[SIZE_FS] = {
  SIG_NULL, /* A: */
  SIG_NULL, /* B: */
  SIG_NULL, /* C: */
  SIG_NULL, /* D: */
  SIG_NULL, /* E: */
  SIG_NULL, /* F: */
  SIG_NULL, /* G: */
  SIG_NULL, /* H: */
  SIG_NULL, /* I: */
  SIG_NULL, /* J: */
  SIG_NULL, /* K: */
  SIG_NULL, /* L: */
  SIG_NULL, /* M: */
  SIG_NULL, /* N: */
  SIG_NULL, /* O: */
  SIG_NULL, /* P: */
  SIG_NULL, /* Q: */
  SIG_NULL, /* R: */
  SIG_NULL, /* S: */
  SIG_NULL, /* T: */
  SIG_NULL, /* U: */
  SIG_NULL, /* V: */
  SIG_NULL, /* W: */
  SIG_NULL, /* X: */
  SIG_NULL, /* Y: */
  SIG_NULL, /* Z: */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* ignored */
  SIG_NULL, /* a: */
  SIG_NULL, /* b: */
  SIG_NULL, /* c: */
  SIG_NULL, /* d: */
  SIG_NULL, /* e: */
  SIG_NULL, /* f: */
  SIG_NULL, /* g: */
  SIG_NULL, /* h: */
  SIG_NULL, /* i: */
  SIG_NULL, /* j: */
  SIG_NULL, /* k: */
  SIG_NULL, /* l: */
  SIG_NULL, /* m: */
  SIG_NULL, /* n: */
  SIG_NULL, /* o: */
  SIG_NULL, /* p: */
  SIG_NULL, /* q: */
  SIG_NULL, /* r: */
  SIG_NULL, /* s: */
  SIG_NULL, /* t: */
  SIG_NULL, /* u: */
  SIG_NULL, /* v: */
  SIG_NULL, /* w: */
  SIG_NULL, /* x: */
  SIG_NULL, /* y: */
  SIG_NULL  /* z: */
};

char * showSignature(Sig, char *);

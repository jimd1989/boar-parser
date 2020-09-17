#pragma once

#include <stdlib.h>

#include "nums.h"
#include "sizes.h"
#include "types.h"

typedef struct Sig {
  const unsigned int      count;
  const unsigned int      required;
  const ArgType         * args;
  const ArgVal          * defaults;
} Sig;

#define SIG_NULL {0 , 0, NULL, NULL}
#define SIG_NULL_POS 26

static const ArgVal SIG_ZERO_DEFS[1] = {{0}};
static const ArgVal SIG_ONE_DEFS[1] = {{NUM_ONE}};

static const ArgType SIG_ANY_ARGS[1] = {ARG_ANY};
#define SIG_ANY {1, 1, SIG_ANY_ARGS, NULL}

static const ArgType SIG_UFLOAT_ARGS[1] = {ARG_UFLOAT};
#define SIG_UFLOAT {1, 1, SIG_UFLOAT_ARGS, NULL}

static const ArgType SIG_UINT_UFLOAT_ARGS[2] = {ARG_UINT, ARG_UFLOAT};
#define SIG_UINT_UFLOAT {2, 2, SIG_UINT_UFLOAT_ARGS, NULL}

static const ArgType SIG_UINT_TEXT_ARGS[2] = {ARG_UINT, ARG_TEXT};
#define SIG_UINT_TEXT {2, 2, SIG_UINT_TEXT_ARGS, NULL}

static const ArgType SIG_ENV_ASSIGN_ARGS[3] = {ARG_UINT, ARG_UINT, ARG_UFLOAT};
#define SIG_ENV_ASSIGN {3, 2, SIG_ENV_ASSIGN_ARGS, SIG_ONE_DEFS}

static const
ArgType SIG_MODULATE_ARGS[4] = {ARG_UINT, ARG_UINT, ARG_UFLOAT, ARG_TEXT};
#define SIG_MODULATE {4, 3, SIG_MODULATE_ARGS, SIG_ZERO_DEFS}

static const ArgType SIG_NOTE_ON_ARGS[3] = {ARG_UINT, ARG_UINT, ARG_UINT};
static const ArgVal SIG_NOTE_ON_DEFS[2] = {{127}, {1}};
#define SIG_NOTE_ON {3, 1, SIG_NOTE_ON_ARGS, SIG_NOTE_ON_DEFS}

static const ArgType SIG_NOTE_OFF_ARGS[2] = {ARG_UINT, ARG_UINT};
static const ArgVal SIG_NOTE_OFF_DEFS[1] = {{1}};
#define SIG_NOTE_OFF {2, 1, SIG_NOTE_OFF_ARGS, SIG_NOTE_OFF_DEFS}

static const ArgType SIG_PITCH_ARGS[3] = {ARG_UINT, ARG_UFLOAT, ARG_TEXT};
#define SIG_PITCH {3, 2, SIG_PITCH_ARGS, SIG_ZERO_DEFS}

static const Sig SIG_PURE[SIZE_FS] = {
  SIG_UINT_TEXT,       /* A */
  SIG_NULL,            /* B */
  SIG_NULL,            /* C */
  SIG_UINT_TEXT,       /* D */
  SIG_ANY,             /* E */
  SIG_NULL,            /* F */
  SIG_NULL,            /* G */
  SIG_NULL,            /* H */
  SIG_NULL,            /* I */
  SIG_NULL,            /* J */
  SIG_NULL,            /* K */
  SIG_UINT_TEXT,       /* L */
  SIG_NULL,            /* M */
  SIG_NULL,            /* N */
  SIG_NULL,            /* O */
  SIG_NULL,            /* P */
  SIG_NULL,            /* Q */
  SIG_UINT_TEXT,       /* R */
  SIG_NULL,            /* S */
  SIG_UINT_UFLOAT,     /* T */
  SIG_NULL,            /* U */
  SIG_NULL,            /* V */
  SIG_NULL,            /* W */
  SIG_NULL,            /* X */
  SIG_NULL,            /* Y */
  SIG_NULL,            /* Z */
  SIG_NULL,            /* ignored */
  SIG_NULL,            /* ignored */
  SIG_NULL,            /* ignored */
  SIG_NULL,            /* ignored */
  SIG_NULL,            /* ignored */
  SIG_NULL,            /* ignored */
  SIG_UINT_UFLOAT,     /* a */
  SIG_NULL,            /* b */
  SIG_NULL,            /* c */
  SIG_UINT_UFLOAT,     /* d */
  SIG_ENV_ASSIGN,      /* e */
  SIG_NULL,            /* f */
  SIG_NULL,            /* g */
  SIG_NULL,            /* h */
  SIG_NULL,            /* i */
  SIG_NULL,            /* j */
  SIG_UINT_TEXT,       /* k */
  SIG_UFLOAT,          /* l */
  SIG_MODULATE,        /* m */
  SIG_NOTE_ON,         /* n */
  SIG_NOTE_OFF,        /* o */
  SIG_PITCH,           /* p */
  SIG_NULL,            /* q */
  SIG_UINT_UFLOAT,     /* r */
  SIG_UINT_UFLOAT,     /* s */
  SIG_UINT_UFLOAT,     /* t */
  SIG_NULL,            /* u */
  SIG_NULL,            /* v */
  SIG_UINT_TEXT,       /* w */
  SIG_NULL,            /* x */
  SIG_NULL,            /* y */
  SIG_NULL             /* z */
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

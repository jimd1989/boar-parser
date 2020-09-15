#include "sizes.h"

typedef enum Fn {
  F_ERROR,
  F_BLANK,
  F_UNKNOWN,
  F_NOTE_ON,
  F_NOTE_OFF
} Fn;

static const unsigned int F_PURE[SIZE_FS] = {
  F_UNKNOWN,  /* A */
  F_UNKNOWN,  /* B */
  F_UNKNOWN,  /* C */
  F_UNKNOWN,  /* D */
  F_UNKNOWN,  /* E */
  F_UNKNOWN,  /* F */
  F_UNKNOWN,  /* G */
  F_UNKNOWN,  /* H */
  F_UNKNOWN,  /* I */
  F_UNKNOWN,  /* J */
  F_UNKNOWN,  /* K */
  F_UNKNOWN,  /* L */
  F_UNKNOWN,  /* M */
  F_UNKNOWN,  /* N */
  F_UNKNOWN,  /* O */
  F_UNKNOWN,  /* P */
  F_UNKNOWN,  /* Q */
  F_UNKNOWN,  /* R */
  F_UNKNOWN,  /* S */
  F_UNKNOWN,  /* T */
  F_UNKNOWN,  /* U */
  F_UNKNOWN,  /* V */
  F_UNKNOWN,  /* W */
  F_UNKNOWN,  /* X */
  F_UNKNOWN,  /* Y */
  F_UNKNOWN,  /* Z */
  F_UNKNOWN,  /* ignored */
  F_UNKNOWN,  /* ignored */
  F_UNKNOWN,  /* ignored */
  F_UNKNOWN,  /* ignored */
  F_UNKNOWN,  /* ignored */
  F_UNKNOWN,  /* ignored */
  F_UNKNOWN,  /* a */
  F_UNKNOWN,  /* b */
  F_UNKNOWN,  /* c */
  F_UNKNOWN,  /* d */
  F_UNKNOWN,  /* e */
  F_UNKNOWN,  /* f */
  F_UNKNOWN,  /* g */
  F_UNKNOWN,  /* h */
  F_UNKNOWN,  /* i */
  F_UNKNOWN,  /* j */
  F_UNKNOWN,  /* k */
  F_UNKNOWN,  /* l */
  F_UNKNOWN,  /* m */
  F_NOTE_ON,  /* n */
  F_NOTE_OFF, /* o */
  F_UNKNOWN,  /* p */
  F_UNKNOWN,  /* q */
  F_UNKNOWN,  /* r */
  F_UNKNOWN,  /* s */
  F_UNKNOWN,  /* t */
  F_UNKNOWN,  /* u */
  F_UNKNOWN,  /* v */
  F_UNKNOWN,  /* w */
  F_UNKNOWN,  /* x */
  F_UNKNOWN,  /* y */
  F_UNKNOWN   /* z */
};

static const unsigned int F_PERIOD[SIZE_FS] = {
  F_UNKNOWN, /* A. */
  F_UNKNOWN, /* B. */
  F_UNKNOWN, /* C. */
  F_UNKNOWN, /* D. */
  F_UNKNOWN, /* E. */
  F_UNKNOWN, /* F. */
  F_UNKNOWN, /* G. */
  F_UNKNOWN, /* H. */
  F_UNKNOWN, /* I. */
  F_UNKNOWN, /* J. */
  F_UNKNOWN, /* K. */
  F_UNKNOWN, /* L. */
  F_UNKNOWN, /* M. */
  F_UNKNOWN, /* N. */
  F_UNKNOWN, /* O. */
  F_UNKNOWN, /* P. */
  F_UNKNOWN, /* Q. */
  F_UNKNOWN, /* R. */
  F_UNKNOWN, /* S. */
  F_UNKNOWN, /* T. */
  F_UNKNOWN, /* U. */
  F_UNKNOWN, /* V. */
  F_UNKNOWN, /* W. */
  F_UNKNOWN, /* X. */
  F_UNKNOWN, /* Y. */
  F_UNKNOWN, /* Z. */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* a. */
  F_UNKNOWN, /* b. */
  F_UNKNOWN, /* c. */
  F_UNKNOWN, /* d. */
  F_UNKNOWN, /* e. */
  F_UNKNOWN, /* f. */
  F_UNKNOWN, /* g. */
  F_UNKNOWN, /* h. */
  F_UNKNOWN, /* i. */
  F_UNKNOWN, /* j. */
  F_UNKNOWN, /* k. */
  F_UNKNOWN, /* l. */
  F_UNKNOWN, /* m. */
  F_UNKNOWN, /* n. */
  F_UNKNOWN, /* o. */
  F_UNKNOWN, /* p. */
  F_UNKNOWN, /* q. */
  F_UNKNOWN, /* r. */
  F_UNKNOWN, /* s. */
  F_UNKNOWN, /* t. */
  F_UNKNOWN, /* u. */
  F_UNKNOWN, /* v. */
  F_UNKNOWN, /* w. */
  F_UNKNOWN, /* x. */
  F_UNKNOWN, /* y. */
  F_UNKNOWN  /* z. */
};

static const unsigned int F_COLON[SIZE_FS] = {
  F_UNKNOWN, /* A: */
  F_UNKNOWN, /* B: */
  F_UNKNOWN, /* C: */
  F_UNKNOWN, /* D: */
  F_UNKNOWN, /* E: */
  F_UNKNOWN, /* F: */
  F_UNKNOWN, /* G: */
  F_UNKNOWN, /* H: */
  F_UNKNOWN, /* I: */
  F_UNKNOWN, /* J: */
  F_UNKNOWN, /* K: */
  F_UNKNOWN, /* L: */
  F_UNKNOWN, /* M: */
  F_UNKNOWN, /* N: */
  F_UNKNOWN, /* O: */
  F_UNKNOWN, /* P: */
  F_UNKNOWN, /* Q: */
  F_UNKNOWN, /* R: */
  F_UNKNOWN, /* S: */
  F_UNKNOWN, /* T: */
  F_UNKNOWN, /* U: */
  F_UNKNOWN, /* V: */
  F_UNKNOWN, /* W: */
  F_UNKNOWN, /* X: */
  F_UNKNOWN, /* Y: */
  F_UNKNOWN, /* Z: */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* ignored */
  F_UNKNOWN, /* a: */
  F_UNKNOWN, /* b: */
  F_UNKNOWN, /* c: */
  F_UNKNOWN, /* d: */
  F_UNKNOWN, /* e: */
  F_UNKNOWN, /* f: */
  F_UNKNOWN, /* g: */
  F_UNKNOWN, /* h: */
  F_UNKNOWN, /* i: */
  F_UNKNOWN, /* j: */
  F_UNKNOWN, /* k: */
  F_UNKNOWN, /* l: */
  F_UNKNOWN, /* m: */
  F_UNKNOWN, /* n: */
  F_UNKNOWN, /* o: */
  F_UNKNOWN, /* p: */
  F_UNKNOWN, /* q: */
  F_UNKNOWN, /* r: */
  F_UNKNOWN, /* s: */
  F_UNKNOWN, /* t: */
  F_UNKNOWN, /* u: */
  F_UNKNOWN, /* v: */
  F_UNKNOWN, /* w: */
  F_UNKNOWN, /* x: */
  F_UNKNOWN, /* y: */
  F_UNKNOWN  /* z: */
};

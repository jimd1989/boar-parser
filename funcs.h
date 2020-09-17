#include "sizes.h"

typedef enum Fn {
  F_ERROR,        /* error parsing func                           */
  F_BLANK,        /* no input provided                            */
  F_UNKNOWN,      /* func undefined                               */
  F_ATTACK,       /* a - env num, mono val | stereo val           */
  F_ATTACK_WAVE,  /* A - env num, wave name                       */
  F_DECAY,        /* d - env num, mono val | stereo val           */
  F_DECAY_WAVE,   /* D - env num, wave name                       */
  F_ENV_ASSIGN,   /* e - env num, osc num | depth                 */
  F_ECHO,         /* E - anything (special condition?)            */
  F_KEY_CURVE,    /* k - osc num, wave name                       */
  F_LOUDNESS,     /* l - value                                    */
  F_AMPLITUDE,    /* L - osc num, mono val | stereo val, balance  */
  F_MODULATE,     /* m - osc num, osc num, depth | mod type       */
  F_NOTE_ON,      /* n - MIDI note | velocity, channel            */
  F_NOTE_OFF,     /* o - MIDI note | channel                      */
  F_ENV_LOOP,     /* O - env num, on/off                          */
  F_PITCH,        /* p - osc num, mono pitch | stereo pitch fixed */
  F_QUIT,         /* q - nil                                      */
  F_RELEASE,      /* r - env num, mono val | stereo val           */
  F_RELEASE_WAVE, /* R - env num, wave name                       */
  F_SUSTAIN,      /* s - env num, mono val | stereo val           */
  F_TOUCH,        /* t - osc num, mono val | stero val            */
  F_TUNE,         /* T - MIDI note, mono pitch | stereo pitch     */
  F_WAVE          /* w - osc num, wave name                       */
} Fn;

static const unsigned int F_PURE[SIZE_FS] = {
  F_ATTACK_WAVE,  /* A */
  F_UNKNOWN,      /* B */
  F_UNKNOWN,      /* C */
  F_DECAY_WAVE,   /* D */
  F_ECHO,         /* E */
  F_UNKNOWN,      /* F */
  F_UNKNOWN,      /* G */
  F_UNKNOWN,      /* H */
  F_UNKNOWN,      /* I */
  F_UNKNOWN,      /* J */
  F_UNKNOWN,      /* K */
  F_AMPLITUDE,    /* L */
  F_UNKNOWN,      /* M */
  F_UNKNOWN,      /* N */
  F_ENV_LOOP,     /* O */
  F_UNKNOWN,      /* P */
  F_UNKNOWN,      /* Q */
  F_RELEASE_WAVE, /* R */
  F_UNKNOWN,      /* S */
  F_TUNE,         /* T */
  F_UNKNOWN,      /* U */
  F_UNKNOWN,      /* V */
  F_UNKNOWN,      /* W */
  F_UNKNOWN,      /* X */
  F_UNKNOWN,      /* Y */
  F_UNKNOWN,      /* Z */
  F_UNKNOWN,      /* ignored */
  F_UNKNOWN,      /* ignored */
  F_UNKNOWN,      /* ignored */
  F_UNKNOWN,      /* ignored */
  F_UNKNOWN,      /* ignored */
  F_UNKNOWN,      /* ignored */
  F_ATTACK,       /* a */
  F_UNKNOWN,      /* b */
  F_UNKNOWN,      /* c */
  F_DECAY,        /* d */
  F_ENV_ASSIGN,   /* e */
  F_UNKNOWN,      /* f */
  F_UNKNOWN,      /* g */
  F_UNKNOWN,      /* h */
  F_UNKNOWN,      /* i */
  F_UNKNOWN,      /* j */
  F_KEY_CURVE,    /* k */
  F_LOUDNESS,     /* l */
  F_MODULATE,     /* m */
  F_NOTE_ON,      /* n */
  F_NOTE_OFF    , /* o */
  F_PITCH,        /* p */
  F_QUIT,         /* q */
  F_RELEASE,      /* r */
  F_SUSTAIN,      /* s */
  F_TOUCH,        /* t */
  F_UNKNOWN,      /* u */
  F_UNKNOWN,      /* v */
  F_WAVE,         /* w */
  F_UNKNOWN,      /* x */
  F_UNKNOWN,      /* y */
  F_UNKNOWN       /* z */
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

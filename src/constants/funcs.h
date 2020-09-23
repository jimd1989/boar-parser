#pragma once

/* Representing boar commands as enums. */

typedef enum Fn {

/* The first byte (after the header) in a message to boar is an enum telling
 * it which of its commands to run. This Fn mapping will be duplicated on the
 * boar server and used to dispatch commands. */

  F_ERROR,        /* error parsing func                     */
  F_BLANK,        /* no input provided                      */
  F_UNKNOWN,      /* func undefined                         */
  F_ATTACK,       /* a - env num, val                       */
  F_ATTACK_WAVE,  /* A - env num, wave name                 */
  F_DECAY,        /* d - env num, val                       */
  F_DECAY_WAVE,   /* D - env num, wave name                 */
  F_ENV_ASSIGN,   /* e - env num, osc num | target depth    */
  F_ECHO,         /* E - anything (special condition?)      */
  F_KEY_CURVE,    /* k - osc num, wave name                 */
  F_LOUDNESS,     /* l - value                              */
  F_AMPLITUDE,    /* L - osc num, val | balance             */
  F_MODULATE,     /* m - osc num, osc num, depth | mod type */
  F_NOTE_ON,      /* n - MIDI note | velocity, channel      */
  F_NOTE_OFF,     /* o - MIDI note | channel                */
  F_ENV_LOOP,     /* O - env num, on/off                    */
  F_PITCH,        /* p - osc num, val | fixed               */
  F_QUIT,         /* q - nil                                */
  F_RELEASE,      /* r - env num, val                       */
  F_RELEASE_WAVE, /* R - env num, wave name                 */
  F_SUSTAIN,      /* s - env num, val                       */
  F_TOUCH,        /* t - osc num, val                       */
  F_TUNE,         /* T - MIDI note, pitch                   */
  F_WAVE          /* w - osc num, wave name                 */
} Fn;

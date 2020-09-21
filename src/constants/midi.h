#pragma once

/* Interfacing with standard MIDI opcodes. */

#include <stdbool.h>

#define MIDI_CHANNELS 16  /* total number of MIDI channels */
#define MIDI_MAX 127      /* maximum MIDI value */
#define MIDI_NOTE_ON 144  /* note on command */

/* Determine if byte is a MIDI note on command. */
#define IS_NOTE(x) (x >= MIDI_NOTE_ON && x < (MIDI_NOTE_ON + MIDI_CHANNELS))

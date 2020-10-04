#pragma once

#include <stdbool.h>
#include <stdint.h>

#define CONFIG_CHAN 0     /* Default MIDI channel */
#define CONFIG_RATE 48000 /* Default sample rate */

typedef struct Config {
  uint8_t       chan;
  bool          allChans;
  bool          echoNotes;
  bool          passNotes;
  int           rate;
} Config;

Config makeConfig(int, char **);

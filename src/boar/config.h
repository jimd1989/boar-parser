#pragma once

#include <stdbool.h>
#include <stdint.h>

#define CONFIG_CHAN 0     /* Default MIDI channel */
#define CONFIG_RATE 48000 /* Default sample rate */

typedef struct InConfig {
  uint8_t       chan;
  bool          allChans;
  bool          echoNotes;
  bool          passNotes;
} InConfig;

typedef struct AudioConfig {
  int   rate;
} AudioConfig;

typedef struct Config {
  InConfig      in;
  AudioConfig   audio;
} Config;

Config makeConfig(int, char **);

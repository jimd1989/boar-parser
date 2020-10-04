#pragma once

/* Reading a binary stream of user input into commands. */

#include <stdbool.h>
#include <stdint.h>

#include "../constants/sizes.h"
#include "config.h"

typedef struct In {

/* Used by both this module and dispatch(). Reads binary data from the `head` of
 * `buf` and parses it into a boar command. With the exception of note on/off
 * events, all input is of the form
 *  
 *  (4 bytes) (2 bytes) (1 byte)  (variable bytes)
 *   boar      size      func      parameters
 *
 * The header, the size, and the function type are read in this module's input()
 * function. The parameters are evaluated in dispatch(). */

  uint8_t         cmd;
  int16_t         cmdSize;
  int             size;
  uint8_t       * head;
  InConfig        config;
  uint8_t         buf[SIZE_OUT];
} In;

void advance(In *, int);
bool readByte(In *, uint8_t *, bool);
bool readShort(In *, int16_t *, bool);
bool readInt(In *, int *, bool);
bool readFloat(In *, float *, bool);
bool input(In *);
In makeIn(InConfig);

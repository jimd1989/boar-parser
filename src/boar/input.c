#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "../constants/funcs.h"
#include "../constants/magic.h"
#include "../constants/midi.h"
#include "../constants/sizes.h"
#include "config.h"
#include "dispatch.h"
#include "dummy_dispatch.h"
#include "input.h"

static bool error(void);
static bool isNote(In *);
static void readNote(In *);
static bool isBoar(In *);
static void readBoar(In *);

static bool
error(void) {

/* Displayed when the bytes expected by a command do not match up with the bytes
 * provided. */

  warnx("misaligned input");

  return false;
}

void
advance(In *i, int n) {

/* Decrement the number of remaining bytes in the buffer count and increment
 * the `head` by the same amount. */

  i->size -= n;
  if (i->cmdSize > 0) { i->cmdSize -= n; }
  i->head += n;
}

bool
readByte(In *i, uint8_t *x, bool cmd) {

/* Read a single byte from the input buffer. */

  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *i->head; }
  advance(i, sizeof(*x));

  return true;
}
bool
readShort(In *i, int16_t *x, bool cmd) {

/* Read two bytes from the input buffer. */

  int16_t *xs = (int16_t *)i->head;

  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *xs; }
  advance(i, sizeof(*x));

  return true;
}

bool
readInt(In *i, int *x, bool cmd) {

/* Read four bytes from the input buffer. */

  int *xs = (int *)i->head;

  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *xs; }
  advance(i, sizeof(*x));

  return true;
}

bool
readFloat(In *i, float *x, bool cmd) {

/* Read a float from the input buffer. */

  float *xs = (float *)i->head;

  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *xs; }
  advance(i, sizeof(*x));

  return true;
}

static bool
isNote(In *i) {

/* Check if input buffer's head is a MIDI note on/off event. */  

  return (i->size > 2 && IS_NOTE(*i->head));
}

static void
readNote(In *i) {

/* Parse a MIDI note on/off event into a boar command. */

  i->cmdSize = 3;
  i->cmd = F_NOTE_ON;
}

static bool
isBoar(In *i) {

/* Check if the input buffer's head contains the boar magic word. */

  int *w = (int *)i->head;
  return (i->size > SIZE_HEAD && w[0] == BOAR_WORD);
}

static void
readBoar(In *i) {

/* Read a boar message into a boar command. */

  if (! readInt(i, NULL, false))          { i->cmd = F_ERROR; return; }
  if (! readShort(i, &i->cmdSize, false)) { i->cmd = F_ERROR; return; }
  i->cmdSize +=2;                         /* Undo readShort size reduction. */
  if (! readByte(i, &i->cmd, false))      { i->cmd = F_ERROR; return; }
}

bool
input(In *i) {

/* Read all available input into `buf`. Parse individual commands out of it and
 * dispatch them accordingly. */

  i->head = i->buf;
  i->size = read(STDIN_FILENO, i->buf, SIZE_OUT);
  while (i->size > 0) {
    if (isNote(i))         { readNote(i); }
    else if (isBoar(i))    { readBoar(i); }
    else                   { i->cmd = F_ERROR; advance(i, 1); }
    if (i->cmd != F_ERROR) { (void)dispatch(i); }
    if (i->cmd == F_QUIT)  { return false; }
  }

  return true;
}

In
makeIn(InConfig c) {

/* Initialize an input object. */

  In i = {0};
  i.config = c;

  return i;
}

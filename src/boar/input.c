#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "../constants/funcs.h"
#include "../constants/magic.h"
#include "../constants/midi.h"
#include "../constants/sizes.h"
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
  warnx("misaligned input");
  return false;
}

void
advance(In *i, int n) {
  i->size -= n;
  if (i->cmdSize > 0) { i->cmdSize -= n; }
  i->head += n;
}

bool
readByte(In *i, uint8_t *x, bool cmd) {
  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *i->head; }
  advance(i, sizeof(*x));
  return true;
}
bool
readShort(In *i, int16_t *x, bool cmd) {
  int16_t *xs = (int16_t *)i->head;
  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *xs; }
  advance(i, sizeof(*x));
  return true;
}

bool
readInt(In *i, int *x, bool cmd) {
  int *xs = (int *)i->head;
  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *xs; }
  advance(i, sizeof(*x));
  return true;
}

bool
readFloat(In *i, float *x, bool cmd) {
  float *xs = (float *)i->head;
  if ((int)sizeof(*x) > i->size)           { error(); return false; }
  if (cmd && (int)sizeof(*x) > i->cmdSize) { error(); return false; }
  if (x != NULL)                           { *x = *xs; }
  advance(i, sizeof(*x));
  return true;
}

static bool
isNote(In *i) {
  return (i->size > 2 && IS_NOTE(*i->head));
}

static void
readNote(In *i) {
  uint8_t b = 0;
  if (! readByte(i, &b, false)) { i->cmd = F_ERROR; return; }
  b -= MIDI_NOTE_ON;
  if (b != i->chan) { 
    /* Currently dump all non-matching MIDI. Need options for:
     * 1. Listen on all MIDI channels
     * 2. Pass along non-matching MIDI */
    i->cmd = F_ERROR; (void)readShort(i, NULL, false); return; 
  }
  i->cmdSize = 2;
  i->cmd = F_NOTE_ON;
}

static bool
isBoar(In *i) {
  int *w = (int *)i->head;
  return (i->size > SIZE_HEAD && w[0] == BOAR_WORD);
}

static void
readBoar(In *i) {
  if (! readInt(i, NULL, false))          { i->cmd = F_ERROR; return; }
  if (! readShort(i, &i->cmdSize, false)) { i->cmd = F_ERROR; return; }
  i->cmdSize +=2;                         /* Undo readShort size reduction. */
  if (! readByte(i, &i->cmd, false))      { i->cmd = F_ERROR; return; }
}

bool
input(In *i) {
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
makeIn(void) {
  In i = {{0}};
  return i;
}

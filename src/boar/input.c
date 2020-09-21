#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "../constants/magic.h"
#include "../constants/midi.h"
#include "../constants/sizes.h"
#include "input.h"

static void advance(In *, int);
static uint8_t readByte(In *i);
static int16_t readShort(In *i);
static int readInt(In *i);
static bool isNote(In *);
static void readNote(In *);
static bool isBoar(In *);
static void readBoar(In *);

static void
advance(In *i, int n) {
  i->size -= n;
  i->head += n;
}

static uint8_t
readByte(In *i) {
  uint8_t x = *i->head;
  advance(i, sizeof(x));
  return x;
}

static int16_t
readShort(In *i) {
  int16_t *xs = (int16_t *)i->head;
  advance(i, sizeof(*xs));
  return xs[0];
}

static int
readInt(In *i) {
  int *xs = (int *)i->head;
  advance(i, sizeof(*xs));
  return xs[0];
}

static bool
isNote(In *i) {
  return (i->size > 2 && IS_NOTE(*i->head));
}

static void
readNote(In *i) {
  uint8_t b1 = readByte(i);
  uint8_t b2 = readByte(i);
  uint8_t b3 = readByte(i);
  if ((b1 - MIDI_NOTE_ON) != i->chan) { return; }
  warnx("note %d %s", b2, b3 == 0 ? "off" : "on");
}

static bool
isBoar(In *i) {
  int *w = (int *)i->head;
  return (i->size > SIZE_HEAD && w[0] == BOAR_WORD);
}

static void
readBoar(In *i) {
  (void)readInt(i);
  i->cmdSize = readShort(i);
  i->cmd = readByte(i);
  advance(i, i->cmdSize);
  warnx("boar command %d", i->cmd);
}

bool
input(In *i) {
  i->head = i->buf;
  i->size = read(STDIN_FILENO, i->buf, SIZE_OUT);
  while (i->size > 0) {
    if (isNote(i))      { readNote(i); }
    else if (isBoar(i)) { readBoar(i); }
    else                { advance(i, 1); }
  }
  return true;
}

In
makeIn(void) {
  In i = {{0}};
  return i;
}

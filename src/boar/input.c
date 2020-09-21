#include <err.h>
#include <stdbool.h>
#include <unistd.h>

#include "../constants/magic.h"
#include "../constants/midi.h"
#include "../constants/sizes.h"
#include "input.h"

static bool isNote(In *);
static bool isBoar(In *);
static void readNote(In *);

static bool
isNote(In *i) {
  return (i->size > 2 && IS_NOTE(*i->head));
}

static void
readNote(In *i) {
  uint8_t b1 = i->head[0];
  uint8_t b2 = i->head[1];
  uint8_t b3 = i->head[2];
  i->size -= 3;
  i->head += 3;
  if ((b1 - MIDI_NOTE_ON) != i->chan) { return; }
  warnx("note %d %s", b2, b3 == 0 ? "off" : "on");
}

static bool
isBoar(In *i) {
  int *w = (int *)i->head;
  return (i->size > SIZE_HEAD && w[0] == BOAR_WORD);
}

bool
input(In *i) {
  i->head = i->buf;
  i->size = read(STDIN_FILENO, i->buf, SIZE_OUT);
  if (isNote(i)) { readNote(i); }
  if (isBoar(i)) { warnx("boar command"); }
  return true;
}

In
makeIn(void) {
  In i = {{0}};
  return i;
}

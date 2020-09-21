#include <err.h>
#include <stdbool.h>
#include <unistd.h>

#include "../constants/magic.h"
#include "../constants/midi.h"
#include "../constants/sizes.h"
#include "input.h"

static bool isNote(In *);
static bool isBoar(In *);

static bool
isNote(In *i) {
  return (i->size > 2 && IS_NOTE(*i->head));
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
  if (isNote(i)) { warnx("note %d %d", i->head[1], i->head[2]); }
  if (isBoar(i)) { warnx("boar command"); }
  return true;
}

In
makeIn(void) {
  In i = {{0}};
  return i;
}

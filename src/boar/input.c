#include <err.h>
#include <unistd.h>

#include "../constants/sizes.h"
#include "input.h"

void
reader(void) {
  int n = 0;
  char s[SIZE_OUT] = {0};
  while (1) {
    n = read(0, s, SIZE_OUT);
    if (n) { warnx("%d bytes read", n); }
  }
}

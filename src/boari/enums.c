#include <err.h>
#include <stdint.h>
#include <string.h>

#include "enums.h"
#include "sizes.h"

uint8_t
toI(char *s) {

/* Perform a binary search against the ENUMS array, returning the enum value
 * associated with `s` if it exists. */

  int l = 0;
  int r = SIZE_ENUMS - 1;
  int c = r / 2;
  char *kg, *kx = NULL;

  if (s == NULL) { return ENUM_OFF; }
  while (l <= r) {
    c = l + (r - l) / 2;
    for (kg = s, kx = ENUMS[c].key; *kg != '\0' || *kx != '\0'; kg++, kx++) {
      if (*kg > *kx) { l = c + 1; break; }
      if (*kg < *kx) { r = c - 1; break; }
    }
    if (*kg == '\0' && *kx == '\0') { return ENUMS[c].val; }
  }
  warnx("unknown value %s", s);

  return ENUM_UNKNOWN;
}

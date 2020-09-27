#include <err.h>
#include <stdbool.h>

#include "dispatch.h"
#include "input.h"

bool
dispatch(In *i) {
  warnx("function %d", i->cmd);
  return true;
}

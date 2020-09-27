#pragma once

#include <stdbool.h>

#include "input.h"

#ifdef DUMMY
  #define dispatch(x) dummyDispatch(x)
#endif

bool dummyDispatch(In *);

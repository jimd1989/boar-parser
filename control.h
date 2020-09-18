#pragma once

/* control macros: experimental! Maybe be more trouble than they're worth */

#include "output.h"

#define _O(x) if (! x) { return OUT_ERROR; } /* output guard */

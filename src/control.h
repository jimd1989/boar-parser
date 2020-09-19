#pragma once

/* Control macros: experimental! Maybe be more trouble than they're worth. */

#include <stdbool.h>

/* A guard that terminates evaluation if its condition doesn't hold. Allows
 * writing in a manner similar to Haskell's 'do' notation for the Maybe
 * monad. */
#define _O(x) if (! x) return false

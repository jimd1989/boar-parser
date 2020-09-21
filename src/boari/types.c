#include "types.h"

char *
showArgType(ArgType t) {

/* Return the plaintext equivalent of an ArgType, for use in error messages. */

  switch (t) {
    case ARG_NIL:
      return "nothing ";
    case ARG_UINT:
      return "int+ ";
    case ARG_UFLOAT:
      return "float+ ";
    case ARG_INT:
      return "int ";
    case ARG_FLOAT:
      return "float ";
    case ARG_TEXT:
      return "text ";
    case ARG_ANY:
      return "anything ";
    default:
      return "unknown ";
  }
}

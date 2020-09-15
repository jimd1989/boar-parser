#include <stdio.h>

#include "types.h"

static void printArgType(ArgType);

static void
printArgType(ArgType t) {
  switch (t) {
    case ARG_NIL:
      printf("nothing");
      break;
    case ARG_UINT:
      printf("positive integer");
      break;
    case ARG_UFLOAT:
      printf("positive decimal");
      break;
    case ARG_INT:
      printf("integer");
      break;
    case ARG_FLOAT:
      printf("decimal");
      break;
    case ARG_TEXT:
      printf("text");
      break;
    case ARG_ANY:
      printf("anything");
      break;
    default:
      printf("unknown");
  }
}

void
printArgTypes(ArgType *ts, const int n) {
  int i = 0;
  for (; i < n ; i++) {
    printArgType(ts[i]);
    if (i < (n - 1)) {
      printf(", ");
    }
  }
}

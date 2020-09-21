#include "input.h"

int main(void) {
  In i = makeIn();
  while(input(&i)) {
    ;
  }
  return 0;
}

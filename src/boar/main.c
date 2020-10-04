#include "config.h"
#include "input.h"

int main(int argc, char **argv) {
  Config c = makeConfig(argc, argv);
  In i = makeIn(c.in);
  while(input(&i)) {
    ;
  }
  return 0;
}

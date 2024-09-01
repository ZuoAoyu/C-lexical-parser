#include <stdio.h>

#define LIST_OF_VARIABLES \
  X(value1) \
  X(value2) \
  X(value3)


int main() {
  enum {value1, value2, value3};

  #define X(name) printf("%s = %d\n", #name, name);
  LIST_OF_VARIABLES
  #undef X
}

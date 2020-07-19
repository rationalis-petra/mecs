#include <stdio.h>

#include "test/engine/math/test_math.c"
#include "test/engine/core/test_core.c"

void test_engine() {
  printf("  testing core...\n");
  test_core();
  printf("  testing math...\n");
  test_math();


}

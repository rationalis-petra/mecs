#include <stdio.h>

#include "test/engine/math/test_vecmath.c"
#include "test/engine/math/test_matmath.c"

void test_math() {
  printf("    testing vecmath...\n");
  test_vecmath();
  printf("    testing matmath...\n");
  test_matmath();
}

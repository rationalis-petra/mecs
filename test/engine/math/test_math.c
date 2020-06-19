#include <stdio.h>

#include "test/engine/math/test_vecmath.c"

int num_tests;
int num_correct;

void test_math() {
  printf("    testing vecmath...\n");
  test_vecmath();
}

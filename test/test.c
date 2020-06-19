#include <stdio.h>

#include "test/engine/test_engine.c"

int num_tests = 0;
int knum_correct = 0;

int main(int arc, char** argv) {
  printf("testing engine...\n");
  test_engine();

  printf("%d out of %d passed\n", num_correct, num_tests);
}

#include <math.h>

extern int num_tests;
extern int num_correct;

#define assert_that(expression) \
  do  {				\
    if (!(expression)) {	\
      printf("failed!\n");	\
      return;			\
    }				\
  }				\
  while (0)

#define test_success		 \
  do {				 \
    num_correct++;		 \
    printf("success!\n");	 \
  } while(0)


#define run_test(fun_name)				\
  num_tests++;						\
  printf("      " #fun_name "... ");			\
  fun_name();

#define approx_eq(val1, val2) \
  (abs(val1 - val2) < 1e-6f)

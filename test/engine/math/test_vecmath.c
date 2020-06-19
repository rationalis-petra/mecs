#include "engine/math.h"
#include "test/tester.h"

int num_correct;
int num_tests;

void vec3f_equals_returns_true_for_equal_vals() {
  // arrange
  Vec3f x_1 = {{{3.0f, 4.0f, 5.0f}}};
  Vec3f x_2 = {{{3.0f, 4.0f, 5.0f}}};

  // assert
  assert_that(vec3f_equals(x_1, x_2));

  test_success;
}

void vec3f_equals_returns_false_for_inequal_vals() {
  // arrange
  Vec3f x = {{{1.0f, 2.0f, 3.0f}}};
  Vec3f y = {{{3.0f, 2.0f, 1.0f}}};

  // assert
  assert_that(!vec3f_equals(x, y));

  test_success;
}

void vec3f_magnitude_returns_zero_for_zero_vector() {
  // arrange
  Vec3f o = {{{0.0f, 0.0f, 0.0f}}};

  // act
  float mag = vec3f_magnitude(o);

  // assert
  assert_that(mag == 0);

  test_success;
}

void vec3f_magnitude_returns_correct_for_axis_aligned_vectors() {
  // arrange
  Vec3f xa = {{{4.0f, 0.0f, 0.0f}}};
  Vec3f ya = {{{0.0f, -4.0f, 0.0f}}};
  Vec3f za = {{{0.0f, 0.0f, 1.0f}}};

  // act
  float mxa = vec3f_magnitude(xa);
  float mya = vec3f_magnitude(ya);
  float mza = vec3f_magnitude(za);

  // assert
  assert_that(mxa == 4.0f);
  assert_that(mya == 4.0f);
  assert_that(mza == 1.0f);

  test_success;
}

void vec3f_magnitude_returns_correct_for_arbitrary_vectors() {
  // arrange
  Vec3f i1 = {{{3.0f, 4.0f, 0.0f}}};
  Vec3f i2 = {{{6.0f, 10.0f, 15.0f}}};
  Vec3f i3 = {{{8.0f, 0.0f, 15.0f}}};

  // act
  float l1 = vec3f_magnitude(i1);
  float l2 = vec3f_magnitude(i2);
  float l3 = vec3f_magnitude(i3);

  // assert
  assert_that(l1 == 5.0f);
  assert_that(l2 == 19.0f);
  assert_that(l3 == 17.0f);

  test_success;
}

void vec3f_normalize_returns_vectors_unit_magnitude() {
  // arrange
  Vec3f i1 = {{{3.0f, 2.0f, 2.0f}}};
  Vec3f i2 = {{{10.0f, 0.0f, 1.0f}}};
  Vec3f i3 = {{{-1.0f, 5.0f, 6.0f}}};

  // act
  Vec3f o1 = vec3f_normalize(i1);
  Vec3f o2 = vec3f_normalize(i2);
  Vec3f o3 = vec3f_normalize(i3);

  // assert
  assert_that(vec3f_magnitude(o1) == 1.0f);
  assert_that(vec3f_magnitude(o2) == 1.0f);
  assert_that(vec3f_magnitude(o3) == 1.0f);

  test_success;
}

void vec3f_cross_returns_correct_for_basis_vectors() {
  // arrange
  Vec3f x = {{{1.0f, 0.0f, 0.0f}}};
  Vec3f y = {{{0.0f, 1.0f, 0.0f}}};
  Vec3f z = {{{0.0f, 0.0f, 1.0f}}};

  Vec3f mx = {{{-1.0f, 0.0f, 0.0f}}};
  Vec3f my = {{{0.0f, -1.0f, 0.0f}}};
  Vec3f mz = {{{0.0f, 0.0f, -1.0f}}};

  // act
  Vec3f c1 = vec3f_cross(x, y);
  Vec3f c2 = vec3f_cross(y, z);
  Vec3f c3 = vec3f_cross(z, x);

  Vec3f a1 = vec3f_cross(y, x);
  Vec3f a2 = vec3f_cross(z, y);
  Vec3f a3 = vec3f_cross(x, z);

  // assert
  assert_that(vec3f_equals(c1, z));
  assert_that(vec3f_equals(c2, x));
  assert_that(vec3f_equals(c3, y));

  assert_that(vec3f_equals(a1, mz));
  assert_that(vec3f_equals(a2, mx));
  assert_that(vec3f_equals(a3, my));
  
  test_success;
}

void vec3f_cross_returns_correct_for_arbitrary_vectors() {
  // arrange
  Vec3f x1 = {{{3.0f, 1.0f, 3.0f}}};
  Vec3f x2 = {{{-3.0f, 2.0f, 1.0f}}};
  Vec3f x3 = {{{0.0f, 4.0f, -2.0f}}};

  // act
  Vec3f y1 = vec3f_cross(x1, x2);
  Vec3f y2 = vec3f_cross(x2, x3);
  Vec3f y3 = vec3f_cross(x2, x2);

  // assert
  Vec3f ans1 = {{{-5.0, -12.0, 9.0}}};
  Vec3f ans2 = {{{-8.0, -6.0, -12.0}}};
  Vec3f ans3 = {{{0.0, 0.0, 0.0}}};
  assert_that(vec3f_equals(y1, ans1));
  assert_that(vec3f_equals(y2, ans2));
  assert_that(vec3f_equals(y3, ans3));

  test_success;
}

void vec3f_dot_returns_correct_for_arbitrary_vectors() {
  // arrange
  Vec3f x1 = {{{3.0f, 1.0f, 3.0f}}};
  Vec3f x2 = {{{-3.0f, 2.0f, 1.0f}}};
  Vec3f x3 = {{{0.0f, 4.0f, -2.0f}}};

  // act
  float y1 = vec3f_dot(x1, x2);
  float y2 = vec3f_dot(x2, x3);
  float y3 = vec3f_dot(x2, x2);

  // assert
  assert_that(y1 == -4);
  assert_that(y2 == 6 );
  assert_that(y3 == 14);

  test_success;
}

void vec3f_diff_returns_correct_for_arbitrary_vectors() {
  // arrange
  Vec3f i1 = {{{1.0f, 2.0f, 3.0f}}};
  Vec3f i2 = {{{4.0f, 1.0f, 2.0f}}};
  Vec3f i3 = {{{-10.0f, -2.0f, 2.0f}}};

  // act
  Vec3f o1 = vec3f_difference(i1, i2);
  Vec3f o2 = vec3f_difference(i1, i3);
  Vec3f o3 = vec3f_difference(i3, i2);

  // assert
  Vec3f a1 = {{{-3.0f, 1.0f, 1.0f}}};
  Vec3f a2 = {{{11.0f, 4.0f, 1.0f}}};
  Vec3f a3 = {{{-14.0f, -3.0f, 0.0f}}};
  assert_that(vec3f_equals(o1, a1));
  assert_that(vec3f_equals(o2, a2));
  assert_that(vec3f_equals(o3, a3));

  test_success;
}

void test_vecmath() {
  run_test(vec3f_equals_returns_true_for_equal_vals);
  run_test(vec3f_equals_returns_false_for_inequal_vals);

  run_test(vec3f_magnitude_returns_zero_for_zero_vector);
  run_test(vec3f_magnitude_returns_correct_for_axis_aligned_vectors);
  run_test(vec3f_magnitude_returns_correct_for_arbitrary_vectors);

  run_test(vec3f_normalize_returns_vectors_unit_magnitude);
  
  run_test(vec3f_cross_returns_correct_for_basis_vectors);
  run_test(vec3f_cross_returns_correct_for_arbitrary_vectors);

  run_test(vec3f_dot_returns_correct_for_arbitrary_vectors)


}

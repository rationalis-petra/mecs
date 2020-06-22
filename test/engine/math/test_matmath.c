#include "engine/math.h"
#include "test/tester.h"

int num_tests;
int num_correct;

void mat4f_act_on_correct_for_identity_mat() {
  // arrange
  Vec4f i1 = {{{2.0f, -2.0f, 4.0f, 1.0f}}};
  Vec4f i2 = {{{-1.0f, 0.0f, 1.0f, 1.0f}}};
  Vec4f i3 = {{{4.0f, -2.0f, -4.0f, 1.0f}}};

  Mat4f id = mat4f_identity();

  // act
  Vec4f o1 = mat4f_act_on(id, i1);
  Vec4f o2 = mat4f_act_on(id, i2);
  Vec4f o3 = mat4f_act_on(id, i3);

  // assert
  assert_that(vec4f_equals (i1, o1));
  assert_that(vec4f_equals (i2, o2));
  assert_that(vec4f_equals (i3, o3));

  test_success;
}

void mat4f_translate_to_pos_0() {
  // arrange
  Vec3f camera_pos = {{{4.0f, -4.0f, 4.0f}}};
  Vec3f camera_target = {{{4.0f, -4.0f, 3.0f}}};
  Vec3f camera_up = {{{0.0f, 1.0f, 0.0f}}};

  // act
  Mat4f look = mat4f_look_at(camera_pos, camera_target, camera_up);
  Mat4f trans = mat4f_translate(-4.0f, -4.0f, -4.0f);

  // assert
  assert_that(mat4f_equals(look, trans));

  test_success;
}

void mat4f_rotates_front_to_correct_pos() {

}

void test_matmath() {
  // mat4f_eq
  // identity correct
  // scale correct
  // rotation correct
  // translation correct

  run_test(mat4f_translate_to_pos_0);

  run_test(mat4f_act_on_correct_for_identity_mat);
}

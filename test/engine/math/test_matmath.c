#include "engine/math.h"
#include "test/tester.h"

int num_tests;
int num_correct;

void mat4f_act_on_correct_for_identity_mat() {
  // arrange
  Vec4f i1 = {{{2.0f, -2.0f, 4.0f}}};
  Vec4f i2 = {{{-1.0f, 0.0f, 1.0f}}};
  Vec4f i3 = {{{4.0f, -2.0f, -4.0f}}};

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

void mat4f_look_at_translates_front_to_correct_coords() {
  // arrange
  Vec3f camera_pos1 = {{{3.0f, 0.0f, 4}}};
  Vec3f camera_pos2 = {{{1.0f, 0.0f, 2.0f}}};

  Vec3f camera_target = {{{2.0f, 0.0f, 3.0f}}};
  Vec3f camera_up = {{{0.0f, 1.0f, 0.0f}}};

  Mat4f view1 = mat4f_look_at(camera_pos1, camera_target, camera_up);
  Mat4f view2 = mat4f_look_at(camera_pos2, camera_target, camera_up);

  // act
  Vec4f point = {{{2.0f, 0.0f, 3.0f}}};
  Vec4f o1 = mat4f_act_on(view1, point);
  Vec4f o2 = mat4f_act_on(view2, point);

  // assert
  Vec4f res = {{{0.0f, 0.0f, -1.0f}}};
  assert_that(vec4f_equals (o1, res));
  assert_that(vec4f_equals (o2, res));

  test_success;
}

void test_matmath() {
  run_test(mat4f_act_on_correct_for_identity_mat);

  run_test(mat4f_look_at_translates_front_to_correct_coords);
}

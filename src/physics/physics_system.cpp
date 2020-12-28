#include <vector>

#include <math.h>

#include "physics/physics.hpp"
#include "test_app.hpp"


using std::vector;
using std::optional;

typedef Vec<3, float> Vec3f;

void PhysicsSystem::run(World& world, UpdateArgs args) {
  // the physics system works on objects with the RigidBody component
  // it is based on a contraint-equation solver, with three broad phases:
  // 1. Calculate all External forces
  // 2. Compute Constraint Forces
  //    (also make drift adjustments!)
  // 3. Update acceleration, velocity, position, etc.

  vector<Entity> physicals = world.predicate_mask([](Entity e) {
    return e.has_component<RigidBody>();
  });

  // there are currently only two external forces: gravity and drag
  for (Entity entity : physicals) {
    // we don't test whether the rigidbody is present: it is guaranteed to
    // be so based on how we generated the physicals vector
    RigidBody& rb = *entity.get_component<RigidBody>().value();
    rb.force += Vec3f(0.0, -9.8 * rb.mass, 0.0);

    optional<Input*> inp = entity.get_component<Input>();
    if (inp) {
      Input& input = *(inp.value());
      rb.force += input.input_force;
    }

    // model drag as a force which is simply a multiple of current speed:
    rb.force += -0.5f * rb.velocity;
  }

  // Contraint equation solving
  for (Entity entity : physicals) {
    auto& rb = *entity.get_component<RigidBody>().value();

    // currently, we just sloppily ensure that objects do not cross y = 0
    if (rb.position.y < 0)  {
      rb.velocity.y = rb.velocity.y < 0 ? 0 : rb.velocity.y;
      rb.position.y = 0;
    }
                             
  }

  // finally, do all updates:
  for (Entity entity : physicals) {
    RigidBody& rb = *entity.get_component<RigidBody>().value();
    rb.velocity += (1 / rb.mass) * rb.force * args.dt; 
    rb.position += (1 / rb.mass) * rb.velocity * args.dt; 
  }


  // TODO: use a universal transform
  // but, for now, we just update the model position to match the rigidbody one

  vector<Entity> rendered = world.predicate_mask([](Entity e) {
    return e.has_component<RigidBody>() && e.has_component<Model>();
  });
  for (Entity entity : rendered) {
    RigidBody& rigidbody = *entity.get_component<RigidBody>().value();
    Model& model = *entity.get_component<Model>().value();

    model.position = rigidbody.position;
    model.rotation = rigidbody.orientation;
  }


  // reset the force accumulators for all particles
  for (Entity e : physicals) {
    RigidBody& rb = *e.get_component<RigidBody>().value();
    rb.force = Vec3f();
  }
}


void PhysicsSystem::init(void) {
  friction_coefficient = 0.2f;
}

void PhysicsSystem::clean(void) {}

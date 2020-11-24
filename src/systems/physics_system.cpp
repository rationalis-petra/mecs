#include <vector>

#include <math.h>

#include "engine.hpp"
#include "components/components.hpp"

#include "systems/systems.hpp"
#include "systems/physics.hpp"
#include "systems/utils.hpp"

using std::vector;

void PhysicsSystem::run(World& world, UpdateArgs args) {
  // The physics system works on objects which has the component RigidBody
  // Physics - velocity, mass, etc.

  // Step 1: Calculate Force
  // Step 2: Calculate Velocity
  // Step 3: Calculate Contraints
  // Step 4: Apply constraints
  // Step 5: Update position

  // Step 1: Calculate Force
  vector<Entity> physicals = world.predicate_mask(&has_rigidbody);
  for (int i = 0; i < physicals.size(); i++) {
    Entity entity1 = physicals[i];
    RigidBody& rigidbody1 = *entity1.get_component<RigidBody>().value();

    // Collision (ground)
    if (rigidbody1.position.y < 0.0f) {
      rigidbody1.force = vec3f_sum(rigidbody1.force, new_vec3f(0.0f, -rigidbody1.position.y * 500, 0.0f));
    }
    else {
      rigidbody1.force = vec3f_sum(rigidbody1.force, new_vec3f(0.0f, -9.8f, 0.0f));
    }

    // Collision (other rigidbodies)
    for (int j = i+1; j < physicals.size(); j++) {
      Entity entity2 = physicals[j];
      RigidBody& rigidbody2 = *entity2.get_component<RigidBody>().value();

      Vec3f collision_force = sat_test(rigidbody1, rigidbody2);
      collision_force = vec3f_multiply(500.0f, collision_force);

      if (collision_force.x != 0 || collision_force.y != 0 || collision_force.z != 0) {
      
        rigidbody2.force = vec3f_sum(collision_force, rigidbody1.force);
        rigidbody1.force = vec3f_sum(vec3f_multiply(-1.0f, collision_force), rigidbody2.force);
      }
    }

    // apply damping
    Vec3f decel_force = vec3f_multiply(friction_coefficient, rigidbody1.velocity);
    rigidbody1.force = vec3f_sum(decel_force, rigidbody1.force);
  }

  for (Entity entity : physicals) {

    // Apply forces, then reset forces to 0
    RigidBody& rigidbody = *entity.get_component<RigidBody>().value();
    rigidbody.velocity = vec3f_sum(vec3f_multiply(args.dt, rigidbody.force), rigidbody.velocity);

    rigidbody.force.x = 0.0f;
    rigidbody.force.y = 0.0f;
    rigidbody.force.z = 0.0f;

    // Update position
    rigidbody.position = vec3f_sum(rigidbody.position, vec3f_multiply(args.dt, rigidbody.velocity));



  }

  // sync rigidbody & model positions
  vector<Entity> rendered = world.predicate_mask(&has_model_rigidbody);
  for (Entity entity : rendered) {
    RigidBody& rigidbody = *entity.get_component<RigidBody>().value();
    Model& model = *entity.get_component<Model>().value();

    model.position = rigidbody.position;
  }
}

void PhysicsSystem::init(void) {}

void PhysicsSystem::clean(void) {}

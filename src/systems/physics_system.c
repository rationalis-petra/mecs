#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/physics.h"
#include "systems/utils.h"

const float friction_coefficient = -0.01f;

void physics_system(void) {
    UpdateArgs args = get_update_args();
    // The physics system works on objects which has the component RigidBody
    // Physics - velocity, mass, etc.

    // Step 1: Calculate Force
    // Step 2: Calculate Velocity
    // Step 3: Calculate Contraints
    // Step 4: Apply constraints
    // Step 5: Update position

    // Step 1: Calculate Force
    EntityList physicals = component_mask(1, RigidBodyType);
    for (int i = 0; i < physicals.len; i++) {
      int id = physicals.entities[i];
      RigidBody *rigidbody = get_component(id, RigidBodyType);

      // Collision (ground)
      if (rigidbody->position.y < 0.0f) {
	rigidbody->force = vec3f_sum(
	    rigidbody->force, new_vec3f(0.0f, -rigidbody->position.y * 100, 0.0f));
      }
      else {
	rigidbody->force = vec3f_sum(
	    rigidbody->force, new_vec3f(0.0f, -9.8f, 0.0f));
      }

      // Collision (other rigidbodies)
      for (int j = 0; j < physicals.len; j++) {
	int id2 = physicals.entities[j];
	if (id == id2) continue;

	RigidBody *rigidbody2 = get_component(id2, RigidBodyType);

	Vec3f collision_force = sat_test(rigidbody, rigidbody2);
	collision_force = vec3f_multiply(500.0f, collision_force);

	if (collision_force.x != 0 || collision_force.y != 0 || collision_force.z != 0) {
	  
	rigidbody2->force = vec3f_sum(collision_force, rigidbody->force);
	rigidbody->force = vec3f_sum(vec3f_multiply(-1.0f, collision_force),
				      rigidbody2->force);
	}
      }

      // apply damping
      Vec3f decel_force = vec3f_multiply(friction_coefficient, rigidbody->velocity);
      rigidbody->force = vec3f_sum(decel_force, rigidbody->force);
    }

    for (int i = 0; i < physicals.len; i++) {
      int id = physicals.entities[i];

      // Apply forces, then reset forces to 0
      RigidBody *rigidbody = get_component(id, RigidBodyType);
      rigidbody->velocity = vec3f_sum(vec3f_multiply(args.dt, rigidbody->force),
				      rigidbody->velocity);

      rigidbody->force.x = 0.0f;
      rigidbody->force.y = 0.0f;
      rigidbody->force.z = 0.0f;

      // Update position
      rigidbody->position = vec3f_sum(
	  rigidbody->position, vec3f_multiply(args.dt, rigidbody->velocity));



    }

    // sync rigidbody & model positions
    EntityList rendered = component_mask(2, RigidBodyType, ModelType);
    for (int id = 0; id < rendered.len; id++) {
      RigidBody *rigidbody = get_component(id, RigidBodyType);
      Model *model = get_component(id, ModelType);

      model->position.x = rigidbody->position.x;
      model->position.y = rigidbody->position.y;
      model->position.z = rigidbody->position.z;

    }
}

void physics_init(void) {}

void physics_clean(void) {}

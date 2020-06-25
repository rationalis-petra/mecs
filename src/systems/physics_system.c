#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

const int friction_coefficient = 0.01f;


void physics_system() {
    UpdateArgs args = get_update_args();
    // The physics system works on objects which has the component RigidBody
    // Physics - velocity, mass, etc.
    EntityList physicals = component_mask(2, TransformType, RigidBodyType);
    for (int id = 0; id < physicals.len; id++) {
        Transform*  transform = get_component(id, TransformType);
        RigidBody* rigidbody = get_component(id, RigidBodyType);

        // things will decelerate due to friction
        Vec3f decel_force = vec3f_multiply(friction_coefficient, rigidbody->velocity);
        Vec3f total_force = vec3f_sum(decel_force, rigidbody->force);
        rigidbody->velocity = vec3f_sum(total_force, rigidbody->velocity);

        // gravity:
        if (transform->position.y > 0.1f) {
           rigidbody->velocity.y -= 9.8 * args.dt;
        }
        else {
            rigidbody->velocity.y = rigidbody->velocity.y > 0 ? rigidbody->velocity.y : 0;
        }

        transform->position = vec3f_sum(transform->position, vec3f_multiply(args.dt, rigidbody->velocity));
        if (transform->position.y < 0) { transform->position.y = 0; }

    }
}

void physics_init() {

}

void physics_clean() {
   
}

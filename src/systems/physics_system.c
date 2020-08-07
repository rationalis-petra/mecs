#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

const float friction_coefficient = 0.01f;
int frame = 0;

void physics_system(void) {
    UpdateArgs args = get_update_args();
    // The physics system works on objects which has the component RigidBody
    // Physics - velocity, mass, etc.

    // Step 1: Calculate Force
    // Step 2: Calculate Velocity
    // Step 3: Calculate Contraints
    // Step 4: Apply constraints
    // Step 5: Update position

    EntityList physicals = component_mask(2, TransformType, RigidBodyType);
    for (int id = 0; id < physicals.len; id++) {
        RigidBody* rigidbody = get_component(id, RigidBodyType);

        // step 1: Calculate Force
        Vec3f decel_force = vec3f_multiply(friction_coefficient, rigidbody->velocity);
        Vec3f total_force = vec3f_sum(decel_force, rigidbody->force);
        rigidbody->velocity = vec3f_sum(total_force, rigidbody->velocity);

        if (rigidbody->position.y > 0.01f) {
            rigidbody->velocity.y -= 9.8 * args.dt;
        }
        else {
            rigidbody->velocity.y = rigidbody->velocity.y > 0 ? rigidbody->velocity.y : 0;
        }

        rigidbody->position = vec3f_sum(rigidbody->position, vec3f_multiply(args.dt, rigidbody->velocity));
        if (rigidbody->position.y < 0) { rigidbody->position.y = 0; }


        Vec3f m_centre = rigidbody->position;
        for (int id2 = 0; id2 < physicals.len; id2++) {
            if (id == id2) continue;
            RigidBody* rigidbody2 = get_component(id2, RigidBodyType);
            Vec3f o_centre = rigidbody2->position;

            // we test each of the following for bounding box overlap
            // we consider them to be unit cubes
            Vec3f diff_vec = vec3f_difference(o_centre, m_centre);
            if (fabs(diff_vec.x) < 1.0f &&
                fabs(diff_vec.y) < 1.0f &&
                fabs(diff_vec.z) < 1.0f) {
                // we want to solve the equation for the intersectino of a line with
                // an axis-aligned plane - plane depends on sign of diff_vec
                float px = diff_vec.x < 0.0f ? 0.5f : -0.5f;
                float py = diff_vec.y < 0.0f ? 0.5f : -0.5f;
                float pz = diff_vec.z < 0.0f ? 0.5f : -0.5f;

                float lx = (o_centre.x + px - m_centre.x) / diff_vec.x;
                float ly = (o_centre.y + py - m_centre.y) / diff_vec.y;
                float lz = (o_centre.z + pz - m_centre.z) / diff_vec.z;

                float delta;
                if (lx > 0.0f && lx < 0.5f) {delta = 0.5f - lx;}
                else if (ly > 0.0f && ly < 0.5f) {delta = 0.5f - ly;}
                else if (lz > 0.0f && lz < 0.5f) {delta = 0.5f - lz;}

                rigidbody2->position = vec3f_sum(o_centre, vec3f_multiply(delta, diff_vec));
                rigidbody->position = vec3f_sum(m_centre, vec3f_multiply(-delta, diff_vec));
            }
        }
    }
}

void physics_init(void) {

}

void physics_clean(void) {
   
}

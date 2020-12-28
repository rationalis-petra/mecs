
add_library(physics OBJECT
                    # Dynamics is mainly concerned with constraints solving
                    # the constraint equation
                    dynamics/constraint_solver.cpp

                    # Detection and resolution of collisions
                    collision/aabb_test.cpp
                    collision/sat_test.cpp

                    # Stuff so it can interact with the ECS 
                    # Components in the ECS
                    collision_mesh.cpp
                    rigidbody.cpp

                    # System in the ECS
                    physics_system.cpp)
             

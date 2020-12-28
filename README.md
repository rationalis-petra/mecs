# Mecs
Mecs (Mechanics in ECS) is (or, more accurately, will be) a simple RigidBody physics system, based on a Force-Based approache to solving constraint equations. Currently Implemented, we have:
+ A functioning Entity Component System (ECS)
+ Basic Mesh Rendering
+ Input system
+ Collision detection for cuboids (note, not collision resolution!)


## TODO
Self-explanatory: documenting the progress of the project in four main areas: the ECS, Rendering, Physics & Documentation
+ ECS
  + [x] Ability to compose components into entities, which can be added into worlds 
  + [x] Generic system machinery
  + [x] Resource Management
  + [ ] Generational Indexing

+ Rendering 
  + [x] Basic Phong Shaders
  + [ ] Advanced Lighting
  + [ ] Custom model loader or use assimp

+ Physics
  + [x] SAT collision detection for non axis-aligned boxes
  + [ ] Constraint equation solver/system
  + [ ] Collision Resolution
  + [ ] Various Contraint Types
  + [ ] Actuators

+ Documentation
  + [ ] Extensive internal documentation
  + [ ] How to use the ECS
  + [ ] How to use the physics engine

# Mecs
Mecs (Mechanics in ECS) is (or, more accurately, will be) a simple RigidBody physics system, based on a Force-Based approache to solving constraint equations. Currently Implemented, we have:
+ A functioning Entity Component System (ECS)
+ Basic Mesh Rendering
+ Input system
+ Collision detection for cuboids (note, not collision resolution!)

## Running
When building, you have the option of whether or not you want to use [conan](https://conan.io/) for installing dependencies, or doing it manually:
### Conan
```sh
git clone https://github.com/rationalis-petra/mecs
mkdir mecs/build
cd mecs/build
conan install ..
```
Then, depending on whether you use linux (X11 only) or windows:
```sh
(win32)
cmake .. -G "Visual Studio 16"
cmake --build .
(linux)
cmake .. 
cmake --build .
```
This will produce an executable in `mecs/build/bin`. Run this file from the root (mecs) directory, as the program expects the `resources` directory to be located in the current working directory when it is called. If you don't do this, you'll get a bunch of "couldn't find resource" errors and a blank screen.

### Manual 
If you don't want to use conan make sure you have glfw installed and your compiler can link to it with `-lglfw`
```sh
git clone https://github.com/rationalis-petra/mecs
mkdir mecs/build
cd mecs/build
cmake ..
make
```

## TODO
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

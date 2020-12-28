#ifndef __SYSTEM_HPP
#define __SYSTEM_HPP

class UpdateArgs {
public:
  float dt;  ///< The time since the last frame was called
};

// The System is an abstract class for system objects to inherit from
class World;
class System {
public:
  virtual void init() = 0;
  virtual void clean() = 0;
  virtual void run(World& world, UpdateArgs args) = 0;
};

#endif

#ifndef __PHYSICS_SYSTEM_HPP
#define __PHYSICS_SYSTEM_HPP

class PhysicsSystem : public System {
private:
  float friction_coefficient = 0.0f;
public:
  void run(World&, UpdateArgs);
  void init(void);
  void clean(void);
};

#endif

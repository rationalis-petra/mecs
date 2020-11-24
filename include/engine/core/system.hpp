/**@bried An abstract class for systems to inherit from
 */

class World;
class System {
public:
  virtual void init() = 0;
  virtual void clean() = 0;
  virtual void run(World& world, UpdateArgs args) = 0;
};

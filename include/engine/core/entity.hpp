#include <optional>

class World;

class Entity {
  friend class World;

private:
  unsigned idx;
  World& world;

  Entity(World& world, unsigned int id);

public:
  template<typename T> Entity& add_component(T* component);
  template<typename T> std::optional<T*> get_component();
  template<typename T> void delete_component();
  template<typename T> bool has_component();

};


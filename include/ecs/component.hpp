class Component {
private:
  friend class Entity;
  unsigned type_idx;
public:
  virtual ~Component() = 0;
};

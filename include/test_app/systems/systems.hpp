#ifndef __SYSTEMS_H
#define __SYSTEMS_H

class InputSystem : public System {
private:
  Cursor cursor_pos;
  bool b_npressed = true;
public:
  void run(World&, UpdateArgs);
  void init(void);
  void clean(void);
};

#endif

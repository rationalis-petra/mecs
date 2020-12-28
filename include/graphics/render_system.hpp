#ifndef __RENDER_SYSTEM_HPP
#define __RENDER_SYSTEM_HPP

class RenderSystem : public System {
private:
  unsigned int shader_program;

  unsigned int model_uniform;
  unsigned int view_uniform;
  unsigned int projection_uniform;

  unsigned int light_colour;
  unsigned int object_colour;

  unsigned int light_pos;
  unsigned int view_pos;

public:
  void run(World&, UpdateArgs);
  void init(void);
  void clean(void);
};

#endif

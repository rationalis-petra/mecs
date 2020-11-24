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

class EnemySystem : public System {
private:
public:
  void run(World&, UpdateArgs);
  void init(void);
  void clean(void);
};

// class CombatSystem : public System {
// private:
// public:
//   void run(UpdateArgs);
//   void init(void);
//   void clean(void);
// };

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

class PhysicsSystem : public System {
private:
  const float friction_coefficient = -0.01f;
public:
  void run(World&, UpdateArgs);
  void init(void);
  void clean(void);
};

// class AiSystem : public System {
// private:
//   int mysocket;
//   int child_pid;

//   struct sockaddr_in dest;
//   struct sockaddr_in serv;

//   struct {
//     bool ready_read;
//     bool ready_send;
//     bool end;
//     char* msg;
//   } shared_state;

//   pthread_t ai_thread;
//   pthread_t killing_thread;

//   void communicate_with_ai();
//   void kill_thread();

// public:
//   void run(World&, UpdateArgs);
//   void init(void);
//   void clean(void);
// };
#endif

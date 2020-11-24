#ifndef __AGENT_H_
#define __AGENT_H_

#include "engine.hpp"

typedef enum {NetworkIntelligence, Adversary, Ally} TypeofAgent;

class Agent : public Component {
public:
  static unsigned type_idx;
  TypeofAgent agent_type;
  //socket intelligence;

  Agent();
  ~Agent();
};


#endif // __AGENT_H_

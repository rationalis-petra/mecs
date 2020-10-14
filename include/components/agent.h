#ifndef __AGENT_H_
#define __AGENT_H_

typedef enum {NetworkIntelligence, Adversary, Ally} TypeofAgent;

typedef struct {
    TypeofAgent agent_type;
    //socket intelligence;
} Agent;

void* new_agent(void);

void delete_agent(void* agent);


#endif // __AGENT_H_

#include <stdlib.h>

#include "components/agent.h"


void* new_agent(void) {
    return malloc(sizeof(Agent));
}

void delete_agent(void* agent) {
    free(agent);
}

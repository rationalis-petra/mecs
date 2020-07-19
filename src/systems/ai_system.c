#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

void ai_system(void) {
}

void ai_init(void) {


  char* programName = "resources/agents/basic_ai";
  switch (fork()) {
    case 0:
      execlp(programName, programName, NULL);
      break;
    case -1:
      // error??
      break;
  }
}

void ai_clean(void) {
  // delete/free scheme_environment
}

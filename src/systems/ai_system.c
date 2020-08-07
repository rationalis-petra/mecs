#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

#define PORTNUM 2300

int mysocket;
int child_pid;

struct sockaddr_in dest;
struct sockaddr_in serv;

struct {
  bool ready_read;
  bool ready_send;
  bool end;
  char* msg;
} shared_state;

pthread_t ai_thread;
pthread_t killing_thread;

void communicate_with_ai(void) {
  socklen_t socksize = sizeof(dest);
  int consocket = accept(mysocket, (struct sockaddr*) &dest, &socksize);

  while(!shared_state.end) {
    while (!(shared_state.ready_send || shared_state.end)) {
       sleep (0.1);
    }
    if (shared_state.end) {
      break;
    }
    shared_state.ready_send = false;

    // perform a blocking IO operation, sending the current simulation
    // state to the AI
    send(consocket, shared_state.msg, strlen(shared_state.msg), 0);
    free(shared_state.msg);

    shared_state.msg = calloc(sizeof(char), 500);

    // perform a blocking IO operation reading the AI response
    read(consocket, shared_state.msg, 500);

    shared_state.ready_read = true;
  }

  char* end_msg = "end\n";
  send(consocket, end_msg, strlen(end_msg), 0);
  char last_msg[100];
  //read(consocket, last_msg, 100);

  close(consocket);
  close(mysocket);

  pthread_exit(EXIT_SUCCESS);
}

void ai_system(void) {
  if(shared_state.ready_read) {
    shared_state.ready_read = false;

    // read the response and turn it into a player movement vector
    // the response will be a vector (x y z)
    int player = first_match(&is_player);
    RigidBody* rb = get_component(player, RigidBodyType);
    Vec3f* p_vel = &(rb->velocity);

    sscanf(shared_state.msg, "\n(%f %f %f)", &(p_vel->x), &(p_vel->y), &(p_vel->z));

    free(shared_state.msg);
    shared_state.msg = stringify_state();
    shared_state.ready_send = true;
  }
}

void ai_init(void) {
  shared_state.end = false;

 
  char* program_name = "resources/agents/basic-ai";

  switch ((child_pid = fork())) {
    case 0:
      execlp(program_name, program_name, NULL);
      break;
    case -1:
      // error??
      break;
  }

  memset(&serv, 0, sizeof(serv));

  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  serv.sin_port = htons(PORTNUM);

  mysocket = socket(AF_INET, SOCK_STREAM, 0);
  bind(mysocket, (struct sockaddr*) &serv, sizeof(struct sockaddr));

  listen(mysocket, 5);

  pthread_create(&ai_thread, NULL, (void*) &communicate_with_ai, NULL);
  shared_state.msg = stringify_state();
  shared_state.ready_send = true;
  shared_state.ready_read = false;
}

void kill_thread() {
  sleep(10);
  pthread_cancel(ai_thread);
  pthread_exit(EXIT_SUCCESS);
}

void ai_clean(void) {
  shared_state.end = true;
  pthread_create(&killing_thread, NULL, (void*) &kill_thread, NULL);
  // delete/free scheme_environment
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

void attack() {
  EntityList enemies = predicate_mask(&is_enemy);
  printf("Who would you like to attack?:\n");
  for (int i = 0; i < enemies.len; i++) {
    Info* info = (Info*) get_component(i, InfoType);
    printf("(%d), %s\n", i, info->name);
  }
  int ans = getchar();
    if(isdigit(ans) && ans < 48 + enemies.len) {
      ans = ans - 48;
      Creature* creature = (Creature*) get_component(ans, CreatureType);
      creature->health -= 5;
    }
    else {
      printf("sorry, that was not a valid enemy :(\n");
      attack();
    }
  
}

void input_system() {
  int player = first_match(&is_player);
  Transform* player_transform = (Transform*) get_component(player, TransformType);

  int c = getchar();

  switch(c) {
  case 'w':
    player_transform->position.y += 5;
    printf("you moved forwards, your position is now (%d, %d)\n", player_transform->position.x, player_transform->position.y);
    break;
  case 's':
    player_transform->position.y -= 5;
    printf("you moved backwards, your position is now (%d, %d)\n", player_transform->position.x, player_transform->position.y);
    break;
  case 'd':
    player_transform->position.x += 5;
    printf("you moved right, your position is now (%d, %d)\n", player_transform->position.x, player_transform->position.y);
    break;
  case 'a':
    player_transform->position.x -= 5;
    printf("you moved left, your position is now (%d, %d)\n", player_transform->position.x, player_transform->position.y);
    break;
  case 'k':
    printf("Goodbye\n");
    stop();
    break;
  case '\n':
    break;
  case ' ':
    attack();
    break;

  default:
    printf("Sorry, that is not a valid input\n");
  }
}

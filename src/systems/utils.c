#include <stdbool.h>

#include "engine.h"
#include "components/components.h"
#include "systems/utils.h"

bool is_player(int id) {
  Info* info = (Info*) get_component(id, InfoType);
  if (info) {
    if (info->tags | PlayerTag)
      return true;
  }
  return false;
}

bool is_enemy(int id) {
  Info* info = (Info*) get_component(id, InfoType);
  if (info) {
    if (info->tags | EnemyTag)
      return true;
  }
  return false;
}

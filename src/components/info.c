#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "components/info.h"

void* new_info() {
  return malloc(sizeof(Info));
}

void delete_info(void* _info) {
  Info* info = (Info*) _info;

  #ifndef NDEBUG
  if (!info) {
    perror( "error in delete_info in component Info: attemt to delete null Info");
  }
  #endif

  free(info->name);
  free(info);
}

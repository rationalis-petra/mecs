#include "components/attachment.h"

void* new_attachment(void) {
   return new_genlist();
}

void delete_attachment(void* attachment) {
  delete_genlist(attachment);
}

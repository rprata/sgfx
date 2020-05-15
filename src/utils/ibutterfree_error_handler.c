#include "ibutterfree_log.h"

static char ibutterfree_message_error[1024] = {0};

const char *ibutterfree_get_message_error() {
  return ibutterfree_message_error;
}

void ibutterfree_set_message_error(const char *msg) {
  memset((void *)ibutterfree_message_error, 0, 1024);
  strcpy(ibutterfree_message_error, msg);
}
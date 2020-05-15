#include "sgfx_log.h"

static char sgfx_message_error[1024] = {0};

const char *sgfx_get_message_error() { return sgfx_message_error; }

void sgfx_set_message_error(const char *msg) {
  memset((void *)sgfx_message_error, 0, 1024);
  strcpy(sgfx_message_error, msg);
}
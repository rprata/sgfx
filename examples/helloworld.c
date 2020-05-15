#include <sgfx.h>
#include <sgfx_config.h>
#include <sgfx_log.h>

int main(int argc, char **argv) {
  SGFX_LOG_TRACK("Initializing helloworld application");
  SGFX_RET ret = sgfx_init(argc, argv);

  if (ret == SGFX_OK)
    SGFX_LOG_TRACK("SGFX Library can be initialized");
  else
    SGFX_LOG_ERROR("SGFX Library cannot be initialized");
  SGFX_LOG_TRACK("Closing helloworld application");
  sgfx_close();
  return 0;
}
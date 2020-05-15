#include "sgfx_config.h"

void sgfx_config_read(void) {
  FILE *fp;
  char buff[1024];

  if (!m_bfcs) {
    m_bfcs = (SGFXConfigStruct *)malloc(sizeof(SGFXConfigStruct));
    memcpy(m_bfcs->fdfb, FB, strlen(FB));
    memcpy(m_bfcs->fdev, INPUT, strlen(INPUT));
  }

  fp = fopen(CONFIG, "r");
  if (fp != NULL) {
    while (!feof(fp)) {
      if (fgets(buff, 1024, fp) != NULL) {
        if (strstr(buff, "FDFB") != NULL) {
          memcpy(m_bfcs->fdfb, buff + 5, strlen(buff + 5) - 1);
          *(m_bfcs->fdfb + strlen(buff + 5) - 1) = '\0';
          SGFX_LOG_TRACK("fdfb: %s", m_bfcs->fdfb);
        } else if (strstr(buff, "FDEV") != NULL) {
          memcpy(m_bfcs->fdev, buff + 5, strlen(buff + 5) - 1);
          *(m_bfcs->fdev + strlen(buff + 5) - 1) = '\0';
          SGFX_LOG_TRACK("fdev: %s", m_bfcs->fdev);
        }
      }
    }
  } else {
    SGFX_LOG_ERROR("Couldn't open file");
    sgfx_set_message_error("Couldn't open file");
  }
}

const char *sgfx_get_fdfb(void) {
  if (m_bfcs)
    return m_bfcs->fdfb;
  else
    return NULL;
}

const char *sgfx_get_fdev(void) {
  if (m_bfcs)
    return m_bfcs->fdev;
  else
    return NULL;
}
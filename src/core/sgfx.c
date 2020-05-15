#include "sgfx.h"

SGFX_RET sgfx_init(int argc, char **argv) {
  if (!m_sgfs) {
    m_sgfs = (SGFXStruct *)malloc(sizeof(SGFXStruct));
    m_sgfs->fbfd = 0;
    m_sgfs->screensize = 0;
    m_sgfs->fbp = NULL;

    sgfx_config_read();

    m_sgfs->fbfd = open(sgfx_get_fdfb(), O_RDWR);
    if (m_sgfs->fbfd == -1) {
      SGFX_LOG_ERROR("Cannot open framebuffer device");
      sgfx_set_message_error("Cannot open framebuffer device");
      free(m_sgfs);
      m_sgfs = NULL;
      return SGFX_ERROR;
    }

    if (ioctl(m_sgfs->fbfd, FBIOGET_FSCREENINFO, &m_sgfs->finfo) == -1) {
      SGFX_LOG_ERROR("Reading FBIOGET_FSCREENINFO information");
      sgfx_set_message_error("Reading FBIOGET_FSCREENINFO information");
      free(m_sgfs);
      m_sgfs = NULL;
      return SGFX_ERROR;
    }

    if (ioctl(m_sgfs->fbfd, FBIOGET_VSCREENINFO, &m_sgfs->vinfo) == -1) {
      SGFX_LOG_ERROR("Reading FBIOGET_VSCREENINFO information");
      sgfx_set_message_error("Reading FBIOGET_VSCREENINFO information");
      free(m_sgfs);
      m_sgfs = NULL;
      return SGFX_ERROR;
    }

    m_sgfs->screensize = m_sgfs->vinfo.xres_virtual *
                         m_sgfs->vinfo.yres_virtual *
                         (m_sgfs->vinfo.bits_per_pixel / 8);

    m_sgfs->fbp = (char *)mmap(0, m_sgfs->screensize, PROT_READ | PROT_WRITE,
                               MAP_SHARED, m_sgfs->fbfd, (off_t)0);
    m_sgfs->bbp = (char *)mmap(0, m_sgfs->screensize, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);

    if (!m_sgfs->fbp && !m_sgfs->bbp) {
      SGFX_LOG_ERROR("Failed to map framebuffer device to memory");
      sgfx_set_message_error("Failed to map framebuffer device to memory");
      free(m_sgfs);
      m_sgfs = NULL;
      return SGFX_ERROR;
    }

    memset(m_sgfs->fbp, 0x00, m_sgfs->screensize);
    memset(m_sgfs->bbp, 0x00, m_sgfs->screensize);
  }

  return SGFX_OK;
}

void sgfx_close(void) {
  if (m_sgfs) {
    munmap(m_sgfs->fbp, m_sgfs->screensize);
    munmap(m_sgfs->bbp, m_sgfs->screensize);
    close(m_sgfs->fbfd);
    free(m_sgfs);
    m_sgfs = NULL;
  }
}
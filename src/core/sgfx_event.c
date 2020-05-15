#include "sgfx_event.h"

#ifdef __POSIX__
static bool event_th_running = true;
static pthread_t event_th;
void *event_func_th(void *args) {
  while (event_th_running) {
    SGFXTouchStruct bfts;
    if (sgfx_event_read(&bfts) == SGFX_OK) {
      m_sgevs->cb(bfts);
    }
  }
  event_th_running = false;
  return NULL;
}
#endif

static int x_factor = 1, y_factor = 1;

SGFX_RET sgfx_event_init(SGFXSurface *surface) {
  if (!m_sgevs) {
    int xres, yres;
    sgfx_get_resolution(surface, &xres, &yres);
    x_factor = (X_MAX - X_MIN) / xres;
    y_factor = (Y_MAX - Y_MIN) / yres;

    m_sgevs =
        (SGFXEventInternalStruct *)malloc(sizeof(SGFXEventInternalStruct));
    m_sgevs->evfd = open(sgfx_get_fdev(), O_RDONLY);
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("sgfx_event_init already initialized");
    sgfx_set_message_error("sgfx_event_init already initialized");
    return SGFX_ERROR;
  }
}

void sgfx_event_callback_register(SGFXSurface *surface, event_cb_t event_cb) {
  if (m_sgevs) {
    m_sgevs->cb = event_cb;
#ifdef __POSIX__
    event_th_running = true;
    if (pthread_create(&event_th, NULL, event_func_th, NULL)) {
      event_th_running = false;
      SGFX_LOG_ERROR("Cannot create pthread");
      sgfx_set_message_error("Cannot create pthread");
    }
#endif
  } else {
    SGFX_LOG_ERROR("Cannot register event callback");
    sgfx_set_message_error("Cannot register event callback");
  }
}

SGFX_RET sgfx_event_read(SGFXTouchStruct *bfts) {
  int counter_x = 0, counter_y = 0, counter_pressure = 0;
  int sum_x = 0, sum_y = 0, sum_pressure = 0;
  if (m_sgevs) {
    bfts->pressure = -1;
    while (true) {
      if (read(m_sgevs->evfd, &m_sgevs->ev, sizeof(struct input_event)) != -1) {
        if (m_sgevs->ev.type == EV_ABS) {
          if (m_sgevs->ev.code == ABS_X) {
            sum_x += m_sgevs->ev.value / x_factor;
            counter_x++;
          }
          if (m_sgevs->ev.code == ABS_Y) {
            sum_y += m_sgevs->ev.value / y_factor;
            counter_y++;
          }
          if (m_sgevs->ev.code == ABS_PRESSURE) {
            if (m_sgevs->ev.value == 0)
              break;
            sum_pressure += m_sgevs->ev.value;
            counter_pressure++;
          }
        }
        bfts->pressed = 1;
      }
    }
    bfts->x_abs = sum_x / counter_x;
    bfts->y_abs = sum_y / counter_y;
    bfts->pressure = sum_pressure / counter_pressure;
    bfts->pressed = 0;
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("Cannot use sgfx_event_read()");
    sgfx_set_message_error("Cannot use sgfx_event_read()");
    return SGFX_ERROR;
  }
}

void sgfx_event_destroy(void) {
  if (m_sgevs) {
    close(m_sgevs->evfd);
#ifdef __POSIX__
    if (m_sgevs->cb && event_th_running) {
      event_th_running = false;
      pthread_join(event_th, NULL);
    }
#endif
    free(m_sgevs);
    m_sgevs = NULL;
  }
}
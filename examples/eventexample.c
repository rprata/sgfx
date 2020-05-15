#include <sgfx.h>
#include <sgfx_draw.h>
#include <sgfx_event.h>
#include <sgfx_log.h>
#include <sgfx_surface.h>

int main(int argc, char **argv) {
  if (sgfx_init(argc, argv) == SGFX_OK) {
    SGFXSurface surface;
    SGFXSurfaceDescription desc;
    desc.width = -1;
    desc.height = -1;
    desc.color = (int32_t)0x000000FF;
    desc.type = PRIMARY;
    desc.buffer = DOUBLE;
    if (sgfx_create_surface(&surface, &desc) == SGFX_OK) {
      int xres, yres;
      sgfx_get_resolution(&surface, &xres, &yres);
      int r = xres / 4;
      sgfx_clear_surface(&surface, (int32_t)0x000000FF);
      sgfx_event_init(&surface);
      sgfx_set_color(&surface, (int32_t)0x00FF00FF);
      sgfx_fill_circle(&surface, xres / 2, yres / 2, r);
      sgfx_flip(&surface, NULL);
      SGFXTouchStruct bfts;
      while (1) {
        sgfx_event_read(&bfts);
        SGFX_LOG_TRACK("x: %d y: %d  pressure: %d", bfts.x_abs, bfts.y_abs,
                       bfts.pressure);
        sgfx_clear_surface(&surface, (int32_t)0x000000FF);
        if ((bfts.x_abs - xres / 2) * (bfts.x_abs - xres / 2) +
                (bfts.y_abs - yres / 2) * (bfts.y_abs - yres / 2) <=
            (r - xres / 2) * (r - yres / 2)) {
          sgfx_set_color(&surface, (int32_t)0xFF0000FF);
        } else {
          sgfx_set_color(&surface, (int32_t)0x00FF00FF);
        }
        sgfx_fill_circle(&surface, xres / 2, yres / 2, r);
        sgfx_flip(&surface, NULL);
      }
      sgfx_event_destroy();
      sgfx_destroy_surface(&surface);
    }
  }
  sgfx_close();

  return 0;
}
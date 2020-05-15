#include <ibutterfree.h>
#include <ibutterfree_draw.h>
#include <ibutterfree_event.h>
#include <ibutterfree_log.h>
#include <ibutterfree_surface.h>

int main(int argc, char **argv) {
  if (ibutterfree_init(argc, argv) == IBUTTERFREE_OK) {
    IButterFreeSurface surface;
    IButterFreeSurfaceDescription desc;
    desc.width = -1;
    desc.height = -1;
    desc.color = (int32_t)0x000000FF;
    desc.type = PRIMARY;
    desc.buffer = DOUBLE;
    if (ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK) {
      int xres, yres;
      ibutterfree_get_resolution(&surface, &xres, &yres);
      int r = xres / 4;
      ibutterfree_clear_surface(&surface, (int32_t)0x000000FF);
      ibutterfree_event_init(&surface);
      ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
      ibutterfree_fill_circle(&surface, xres / 2, yres / 2, r);
      ibutterfree_flip(&surface, NULL);
      IButterFreeTouchStruct bfts;
      while (1) {
        ibutterfree_event_read(&bfts);
        IBUTTERFREE_LOG_TRACK("x: %d y: %d  pressure: %d", bfts.x_abs,
                              bfts.y_abs, bfts.pressure);
        ibutterfree_clear_surface(&surface, (int32_t)0x000000FF);
        if ((bfts.x_abs - xres / 2) * (bfts.x_abs - xres / 2) +
                (bfts.y_abs - yres / 2) * (bfts.y_abs - yres / 2) <=
            (r - xres / 2) * (r - yres / 2)) {
          ibutterfree_set_color(&surface, (int32_t)0xFF0000FF);
        } else {
          ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
        }
        ibutterfree_fill_circle(&surface, xres / 2, yres / 2, r);
        ibutterfree_flip(&surface, NULL);
      }
      ibutterfree_event_destroy();
      ibutterfree_destroy_surface(&surface);
    }
  }
  ibutterfree_close();

  return 0;
}
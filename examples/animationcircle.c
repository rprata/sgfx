#include <sgfx.h>
#include <sgfx_draw.h>
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
      int xres = 0;
      int yres = 0;
      sgfx_get_resolution(&surface, &xres, &yres);
      sgfx_clear_surface(&surface, (int32_t)0x000000FF);
      sgfx_set_color(&surface, (int32_t)0x00FF00FF);
      int i = 0;
      while (1) {
        for (i = xres / 2; i >= 0; i -= 1) {
          sgfx_fill_circle(&surface, xres / 2, yres / 2, i);
          sgfx_flip(&surface, NULL);
          usleep(10);
          sgfx_clear_surface(&surface, (int32_t)0x000000FF);
        }
      }
      sgfx_destroy_surface(&surface);
    }
  }
  sgfx_close();

  return 0;
}
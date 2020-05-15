#include <sgfx.h>
#include <sgfx_draw.h>
#include <sgfx_font.h>
#include <sgfx_image.h>
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
      int xres = 0, yres = 0;
      sgfx_get_resolution(&surface, &xres, &yres);
      sgfx_clear_surface(&surface, (int32_t)0x000000FF);
      sgfx_draw_text(&surface, "Hello World", xres / 7, yres / 7, xres / 40,
                     yres / 40, 0xFF0000FF, 0x000000FF);
      sgfx_draw_text(&surface, "Hello World", xres / 7, yres / 3, xres / 20,
                     yres / 20, 0x00FF00FF, 0x000000FF);
      sgfx_draw_text(&surface, "Hello World", xres / 7, yres / 2, xres / 16,
                     yres / 16, 0x0000FFFF, 0x000000FF);
      sgfx_draw_text(&surface, "Hello World", xres / 7, yres / 1.5, xres / 13,
                     yres / 13, 0xFFFFFFFF, 0x000000FF);
      sgfx_flip(&surface, NULL);
      sgfx_destroy_surface(&surface);
    }
  }
  sgfx_close();

  return 0;
}
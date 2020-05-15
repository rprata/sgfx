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
    desc.buffer = SINGLE;
    if (sgfx_create_surface(&surface, &desc) == SGFX_OK) {
      int xres, yres;
      sgfx_get_resolution(&surface, &xres, &yres);
      sgfx_clear_surface(&surface, (int32_t)0x000000FF);
      sgfx_set_color(&surface, (int32_t)0x00FF00FF);

      sgfx_draw_line(&surface, 0, yres, xres, 0);
      sgfx_set_color(&surface, (int32_t)0x0000FFFF);
      sgfx_draw_line(&surface, 0, 0, xres, yres);
      sgfx_set_color(&surface, (int32_t)0xFF0000FF);
      sgfx_draw_line(&surface, xres / 2, 0, xres / 2, yres);
      sgfx_set_color(&surface, (int32_t)0x00FF00FF);
      sgfx_draw_line(&surface, 0, yres / 2, xres, yres / 2);
      sgfx_set_color(&surface, (int32_t)0xAA12FFFF);
      sgfx_fill_rect(&surface, xres / 7, yres / 4, xres / 3, yres / 4);
      sgfx_set_color(&surface, (int32_t)0x0000FFAF);

      sgfx_draw_rect(&surface, xres / 14, xres / 14, xres / 3, yres / 2);

      sgfx_set_color(&surface, (int32_t)0x00AAFFFF);
      sgfx_draw_circle(&surface, xres / 2, yres / 2, yres / 4);
      sgfx_set_color(&surface, (int32_t)0xFF000037);
      sgfx_fill_circle(&surface, xres / 2, yres / 2, yres / 6);

      sgfx_dump_surface(&surface, "image-output.ppm");

      sgfx_flip(&surface, NULL);
      sgfx_destroy_surface(&surface);
    }
  }
  sgfx_close();

  return 0;
}
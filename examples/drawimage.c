#include <sgfx.h>
#include <sgfx_draw.h>
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
      int xres, yres;
      sgfx_get_resolution(&surface, &xres, &yres);
      sgfx_clear_surface(&surface, (int32_t)0x000000FF);
      sgfx_draw_image(&surface, "../examples/resources/images/SGFX.bmp",
                      xres / 7, yres / 4, xres / 7, xres / 7,
                      SGFX_IMAGE_TYPE_BMP);
      sgfx_draw_image(&surface, "../examples/resources/images/SGFX.ppm",
                      xres / 4, yres / 2, xres / 7, xres / 7,
                      SGFX_IMAGE_TYPE_PPM);
      sgfx_draw_image(&surface, "../examples/resources/images/SGFX.png",
                      xres / 7, yres / 2, xres / 7, xres / 7,
                      SGFX_IMAGE_TYPE_PNG);
      sgfx_draw_image(&surface, "../examples/resources/images/SGFX.png",
                      xres / 4, yres / 4, xres / 7, xres / 7,
                      SGFX_IMAGE_TYPE_PNG);
      sgfx_flip(&surface, NULL);
      sgfx_destroy_surface(&surface);
    }
  }
  sgfx_close();

  return 0;
}
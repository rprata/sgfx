#include "sgfx_font.h"

extern int32_t *__resize_bilinear(int32_t *input, int sourceWidth,
                                  int sourceHeight, int targetWidth,
                                  int targetHeight);

SGFX_RET __sgfx_render(SGFXSurface *surface, char *bitmap, int x, int y,
                       int width, int height, int32_t background,
                       int32_t foreground) {
  int i, j, color;
  int32_t input_image[SIZE];

  if (!surface) {
    SGFX_LOG_ERROR("Invalid SGFXSurface");
    sgfx_set_message_error("Invalid SGFXSurface");
    return SGFX_ERROR;
  }

  for (i = 0; i < WIDTH; i++) {
    for (j = 0; j < HEIGHT; j++) {
      if (bitmap[i] & 1 << j)
        color = background;
      else
        color = foreground;

      input_image[i * WIDTH + j] = color;
    }
  }

  int32_t *resized_image =
      __resize_bilinear(input_image, WIDTH, HEIGHT, width, height);

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      long absPosition = j + width * i;
      sgfx_set_color(surface, resized_image[absPosition]);
      sgfx_draw_point(surface, x + j, y + i);
    }
  }
  return SGFX_OK;
}

SGFX_RET sgfx_draw_text(SGFXSurface *surface, const char *text, int x, int y,
                        int width, int height, int32_t background,
                        int32_t foreground) {
  int i;
  for (i = 0; i < strlen(text); i++) {
    if (__sgfx_render(surface, sgfx_font8x8_basic[(int)text[i]],
                      x + i * (width + SPACE), y, width, height, background,
                      foreground) == SGFX_ERROR) {
      return SGFX_ERROR;
    }
  }
  return SGFX_OK;
}

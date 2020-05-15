#include "sgfx_draw.h"
#include "sgfx_definitions.h"

inline void __sgfx_swap_buffers(void) {
  memcpy(m_sgfs->fbp, m_sgfs->bbp, m_sgfs->screensize);
}

unsigned int __blendPreMulAlpha(unsigned int colora, unsigned int colorb,
                                unsigned int alpha) {
  unsigned int rb = (colora & 0xFF00FF) + (alpha * ((colorb & 0xFF00FF)) >> 8);
  unsigned int g = (colora & 0x00FF00) + (alpha * ((colorb & 0x00FF00)) >> 8);
  return (rb & 0xFF00FF) + (g & 0x00FF00);
}

unsigned int __blendAlpha(unsigned int colora, unsigned int colorb,
                          unsigned int alpha) {
  unsigned int rb1 = ((0x100 - alpha) * (colora & 0xFF00FF)) >> 8;
  unsigned int rb2 = (alpha * (colorb & 0xFF00FF)) >> 8;
  unsigned int g1 = ((0x100 - alpha) * (colora & 0x00FF00)) >> 8;
  unsigned int g2 = (alpha * (colorb & 0x00FF00)) >> 8;
  return ((rb1 | rb2) & 0xFF00FF) + ((g1 | g2) & 0x00FF00);
}

SGFX_RET __sgfx_draw_pixel(SGFXSurface *surface, int px, int py, int32_t rgba) {
  if (m_sgfs) {
    struct fb_var_screeninfo vinfo = m_sgfs->vinfo;
    struct fb_fix_screeninfo finfo = m_sgfs->finfo;
    char *bp;
    if (surface->desc->buffer == DOUBLE) {
      bp = m_sgfs->bbp;
    } else {
      bp = m_sgfs->fbp;
    }

    long location = (px + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                    (py + vinfo.yoffset) * finfo.line_length;

    if (location < m_sgfs->screensize && location >= 0) {
      if (vinfo.bits_per_pixel == 32) {
        *(bp + location) = (rgba & 0xFF000000) >> 24;     // red
        *(bp + location + 1) = (rgba & 0x00FF0000) >> 16; // green
        *(bp + location + 2) = (rgba & 0x0000FF00) >> 8;  // blue
        *(bp + location + 3) = (rgba & 0x000000FF);       // transparency
      } else                                              // assume 16bpp
      {
        int b = (rgba & 0xFF000000) >> 24; // blue
        int g = (rgba & 0x00FF0000) >> 16; // green
        int r = (rgba & 0x0000FF00) >> 8;  // red
        unsigned short int t = (r >> 3 << 11) | (g >> 2 << 5) | (b >> 3);
        *((unsigned short int *)(bp + location)) = t;
      }
    } else {
      SGFX_LOG_ERROR("This pixel does not exist.");
      sgfx_set_message_error("This pixel does not exist.");
      return SGFX_ERROR;
    }

    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("__sgfx_draw_pixel has failed");
    sgfx_set_message_error("__sgfx_draw_pixel has failed");
    return SGFX_ERROR;
  }
}
SGFX_RET __sgfx_draw_screenbuffer(SGFXSurface *surface, int px, int py,
                                  int32_t rgba) {

  if (surface) {
    rgba = (((rgba & 0x0000FF00) >> 8) << 24) +
           (((rgba & 0x00FF0000) >> 16) << 16) +
           (((rgba & 0xFF000000) >> 24) << 8) + (((rgba & 0x000000FF)));

    long position = px + py * surface->desc->width;
    if (position < surface->desc->screensize && position >= 0) {
      unsigned char alpha = rgba & 0x000000FF;
      uint32_t backpixel = surface->screenbuffer[position];
      if (alpha <= 0) {
        return SGFX_OK;
      }

      uint32_t rgba_f = rgba;

      if (alpha < 0xFF) {
        alpha = 0x00000FF - alpha;
        rgba_f =
            (__blendAlpha((unsigned int)((rgba & 0xFFFFFF00) >> 8),
                          (unsigned int)((backpixel & 0xFFFFFF00) >> 8), alpha)
             << 8) +
            alpha;
      }

      surface->screenbuffer[position] = rgba_f;
      return SGFX_OK;
    } else {
      SGFX_LOG_ERROR("This pixel position is invalid");
      sgfx_set_message_error("This pixel position is invalid");
      return SGFX_ERROR;
    }
  } else {
    SGFX_LOG_ERROR("Invalid SGFXSurface");
    sgfx_set_message_error("This pixel position is invalid");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_draw_point(SGFXSurface *surface, int px, int py) {
  if (surface) {
    __sgfx_draw_screenbuffer(surface, px, py, surface->desc->color);
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("sgfx_draw_point has failed");
    sgfx_set_message_error("sgfx_draw_point has failed");
    return SGFX_ERROR;
  }
}

inline void __draw_horizontal_line(SGFXSurface *surface, int x0, int x1, int y,
                                   uint32_t rgba) {
  if (surface) {
    int i;
    if (x0 > x1) {
      int tmp = x0;
      x0 = x1;
      x1 = tmp;
    }
    for (i = x0; i <= x1; i++) {
      if (i >= 0 && i <= surface->desc->width) {
        __sgfx_draw_screenbuffer(surface, i, y, rgba);
      }
    }
  }
}

inline void __draw_vertical_line(SGFXSurface *surface, int x, int y0, int y1,
                                 uint32_t rgba) {
  if (surface) {
    int i;
    if (y0 > y1) {
      int tmp = y0;
      y0 = y1;
      y1 = tmp;
    }
    for (i = y0; i <= y1; i++) {
      if (i >= 0 && i <= surface->desc->height) {
        __sgfx_draw_screenbuffer(surface, x, i, rgba);
      }
    }
  }
}

SGFX_RET sgfx_draw_line(SGFXSurface *surface, int x0, int y0, int x1, int y1) {
  if (surface) {
    if (x0 == x1) {
      if (x0 >= 0 && x0 <= surface->desc->width) {
        __draw_vertical_line(surface, x0, y0, y1, surface->desc->color);
        return SGFX_OK;
      } else {
        SGFX_LOG_ERROR("Invalid value for x.");
        sgfx_set_message_error("Invalid value for x.");
        return SGFX_ERROR;
      }
    }

    if (y0 == y1) {
      if (y0 >= 0 && y0 <= surface->desc->height) {
        __draw_horizontal_line(surface, x0, x1, y0, surface->desc->color);
        return SGFX_OK;
      } else {
        SGFX_LOG_ERROR("Invalid value for y.");
        sgfx_set_message_error("Invalid value for y.");
        return SGFX_ERROR;
      }
    }

    // Using Generalized Bresenham's Line Drawing Algorithm
    int i = 0;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int dxabs = abs(dx);
    int dyabs = abs(dy);
    int sdx = sign(dx);
    int sdy = sign(dy);
    int x = dyabs >> 1;
    int y = dxabs >> 1;
    int px = x0;
    int py = y0;

    if (dxabs >= dyabs) {
      for (i = 0; i < dxabs; i++) {
        y += dyabs;
        if (y >= dxabs) {
          y -= dxabs;
          py += sdy;
        }
        px += sdx;
        if (px >= 0 && px <= surface->desc->width && py >= 0 &&
            py <= surface->desc->height) {
          __sgfx_draw_screenbuffer(surface, px, py, surface->desc->color);
        }
      }
    } else {
      for (i = 0; i < dyabs; i++) {
        x += dxabs;
        if (x >= dyabs) {
          x -= dyabs;
          px += sdx;
        }
        py += sdy;
        if (px >= 0 && px <= surface->desc->width && py >= 0 &&
            py <= surface->desc->height) {
          __sgfx_draw_screenbuffer(surface, px, py, surface->desc->color);
        }
      }
    }

    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("sgfx_draw_line has failed");
    sgfx_set_message_error("sgfx_draw_line has failed");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_draw_circle(SGFXSurface *surface, double cx, double cy,
                          int radius) {
  if (surface) {
    // Using Midpoint Circle Algorithm
    inline void plot4points(SGFXSurface * surface, double cx, double cy,
                            double x, double y, uint32_t rgba) {
      if (cx + x >= 0 && cx + x <= surface->desc->width && cy + y >= 0 &&
          cy + y <= surface->desc->height) {
        __sgfx_draw_screenbuffer(surface, cx + x, cy + y, surface->desc->color);
      }
      if (cx - x >= 0 && cx - x <= surface->desc->width && cy + y >= 0 &&
          cy + y <= surface->desc->height) {
        __sgfx_draw_screenbuffer(surface, cx - x, cy + y, surface->desc->color);
      }
      if (cx + x >= 0 && cx + x <= surface->desc->width && cy - y >= 0 &&
          cy - y <= surface->desc->height) {
        __sgfx_draw_screenbuffer(surface, cx + x, cy - y, surface->desc->color);
      }
      if (cx - x >= 0 && cx - x <= surface->desc->width && cy - y >= 0 &&
          cy - y <= surface->desc->height) {
        __sgfx_draw_screenbuffer(surface, cx - x, cy - y, surface->desc->color);
      }
    }

    inline void plot8points(SGFXSurface * surface, double cx, double cy,
                            double x, double y, uint32_t rgba) {
      plot4points(surface, cx, cy, x, y, rgba);
      plot4points(surface, cx, cy, y, x, rgba);
    }

    int error = -radius;
    double x = radius;
    double y = 0;

    while (x >= y) {
      plot8points(surface, cx, cy, x, y, surface->desc->color);

      error += y;
      y++;
      error += y;

      if (error >= 0) {
        error += -x;
        x--;
        error += -x;
      }
    }
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("sgfx_draw_circle has failed");
    sgfx_set_message_error("sgfx_draw_circle has failed");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_fill_circle(SGFXSurface *surface, double cx, double cy,
                          int radius) {
  if (surface) {
    sgfx_draw_circle(surface, cx, cy, radius);
    double x0, x1, y0, y1;
    if (2 * radius < surface->desc->width) {
      x0 = abs(cx - radius);
      x1 = abs(cx + radius);
    } else {
      x0 = 0;
      x1 = surface->desc->width;
    }
    if (2 * radius < surface->desc->height) {
      y0 = abs(cy - radius);
      y1 = abs(cy + radius);
    } else {
      y0 = 0;
      y1 = surface->desc->height;
    }
    int i = 0;
    int j = 0;
    double dx;
    double dy;

    for (i = x0; i < x1; i++) {
      for (j = y0; j < y1; j++) {
        dx = abs(i - cx);
        if (dx > radius) {
          continue;
        }
        dy = abs(j - cy);
        if (dy > radius) {
          continue;
        }
        if (dx + dy <= radius) {
          __sgfx_draw_screenbuffer(surface, i, j, surface->desc->color);
          continue;
        }
        if (dx * dx + dy * dy <= radius * radius) {
          __sgfx_draw_screenbuffer(surface, i, j, surface->desc->color);
        }
      }
    }
    return SGFX_OK;
    ;
  } else {
    SGFX_LOG_ERROR("sgfx_fill_circle has failed");
    sgfx_set_message_error("sgfx_fill_circle has failed");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_draw_rect(SGFXSurface *surface, int x0, int y0, int w, int h) {
  if (surface) {
    if (h <= 0 && w <= 0) {
      SGFX_LOG_ERROR("Wrong values for width and height");
      sgfx_set_message_error("Wrong values for width and height");
      return SGFX_ERROR;
    }
    int x1 = x0 + w;
    int y1 = y0 + h;
    __draw_horizontal_line(surface, x0, x1, y0, surface->desc->color);
    __draw_horizontal_line(surface, x0, x1, y1, surface->desc->color);
    __draw_vertical_line(surface, x0, y0, y1, surface->desc->color);
    __draw_vertical_line(surface, x1, y0, y1, surface->desc->color);
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("sgfx_draw_rect has failed")
    sgfx_set_message_error("sgfx_draw_rect has failed");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_fill_rect(SGFXSurface *surface, int x0, int y0, int w, int h) {
  if (surface) {
    if (h <= 0 && w <= 0) {
      SGFX_LOG_ERROR("Wrong values for width and height");
      sgfx_set_message_error("Wrong values for width and height");
      return SGFX_ERROR;
    }
    int x1 = x0 + w;
    int y1 = y0 + h;
    int i = 0;
    for (i = x0; i <= x1; i++) {
      __draw_vertical_line(surface, i, y0, y1, surface->desc->color);
    }
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("sgfx_fill_rect has failed");
    sgfx_set_message_error("sgfx_fill_rect has failed");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_set_color(SGFXSurface *surface, int32_t color) {
  surface->desc->color = color;
  return SGFX_OK;
}

SGFX_RET sgfx_flip(SGFXSurface *surface, SGFXRect *rect) {
  if (surface && m_sgfs) {
    int i = 0;

    if (surface->desc->type == PRIMARY) {
      if (!rect) {
        for (i = 0; i < surface->desc->screensize; i += 1) {
          __sgfx_draw_pixel(surface, i % surface->desc->width,
                            i / surface->desc->width, surface->screenbuffer[i]);
        }
      } else {
        for (i = rect->x; i < (rect->w * rect->h); i += 1) {
          __sgfx_draw_pixel(surface, i % surface->desc->width + rect->y,
                            i / surface->desc->width + rect->y,
                            surface->screenbuffer[i]);
        }
      }
    }

    if (surface->desc->buffer == DOUBLE) {
      __sgfx_swap_buffers();
    }

    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("Invalid SGFXSurface or SGFXStruct");
    sgfx_set_message_error("Invalid SGFXSurface or SGFXStruct");
    return SGFX_ERROR;
  }
}
#ifndef __IBUTTERFREE_DRAW_H__
#define __IBUTTERFREE_DRAW_H__

#include "ibutterfree_surface.h"

IBUTTERFREE_RET ibutterfree_draw_line(IButterFreeSurface * surface, int x0, int y0, int x1, int y1);
IBUTTERFREE_RET ibutterfree_draw_circle(IButterFreeSurface * surface, double cx, double cy, int radius);
IBUTTERFREE_RET ibutterfree_fill_circle(IButterFreeSurface * surface, double cx, double cy, int radius);
IBUTTERFREE_RET ibutterfree_draw_rect(IButterFreeSurface * surface, int x0, int y0, int w, int h);
IBUTTERFREE_RET ibutterfree_fill_rect(IButterFreeSurface * surface, int x0, int y0, int w, int h);
IBUTTERFREE_RET ibutterfree_set_color(IButterFreeSurface * surface, int32_t color);
IBUTTERFREE_RET ibutterfree_flip(IButterFreeSurface * surface);

#endif
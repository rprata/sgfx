#ifndef __IBUTTERFREE_FONT_H__
#define __IBUTTERFREE_FONT_H__

#include "ibutterfree_image.h"
#include "ibutterfree_font8x8_basic.h"
#include "string.h"

#define WIDTH 	8
#define HEIGHT 	8
#define SIZE	64
#define SPACE	3

IBUTTERFREE_RET ibutterfree_draw_text(IButterFreeSurface * surface, const char * text, int x, int y, int width, int height, int32_t background, int32_t foreground);

#endif
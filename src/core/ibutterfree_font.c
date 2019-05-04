#include "ibutterfree_font.h"

extern int32_t * __resize_bilinear(int32_t * input, int sourceWidth, int sourceHeight, int targetWidth, int targetHeight);

IBUTTERFREE_RET __ibutterfree_render(IButterFreeSurface * surface, char * bitmap, int x, int y, int width, int height, int32_t background, int32_t foreground)
{
	int i, j, color;
	int32_t input_image[SIZE];

	if (!surface) 
	{
		IBUTTERFREE_LOG_ERROR("Invalid IButterFreeSurface");
		ibutterfree_set_message_error("Invalid IButterFreeSurface");
		return IBUTTERFREE_ERROR;
	}

	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			if(bitmap[i] & 1 << j)
				color = background;
			else
				color = foreground;

			input_image[i*WIDTH + j] = color;
		}
	}

	int32_t * resized_image = __resize_bilinear(input_image, WIDTH, HEIGHT, width, height);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			long absPosition = j + width * i;
			ibutterfree_set_color(surface, resized_image[absPosition]);
			ibutterfree_draw_point(surface, x + j, y + i);
		}
	}
	return IBUTTERFREE_OK;
}


IBUTTERFREE_RET ibutterfree_draw_text(IButterFreeSurface * surface, const char * text, int x, int y, int width, int height, int32_t background, int32_t foreground)
{
	int i;
	for (i = 0; i < strlen(text); i++)
	{
		if(__ibutterfree_render(surface, ibutterfree_font8x8_basic[(int)text[i]], x + i*(width + SPACE), y, width, height,background, foreground)) 
		{
			return IBUTTERFREE_ERROR;
		}
	}
	return IBUTTERFREE_OK;
}

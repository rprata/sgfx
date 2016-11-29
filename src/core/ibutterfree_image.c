#include "ibutterfree_image.h"

IBUTTERFREE_RET ibutterfree_draw_image(IButterFreeSurface * surface, const char * filename, int x, int y, int width, int height)
{
	if (surface)
	{
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Error to create image.");
		return IBUTTERFREE_ERROR;
	}
}
#include "ibutterfree_surface.h"

static long ibutterfree_surface_counter = 0;

IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc)
{
	if (!m_bfs) 
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Invalid IButterFreeStruct");
		return IBUTTERFREE_ERROR;
	}

	if (!surface)
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "IButterFreeSurface cannot be created");
		return IBUTTERFREE_ERROR;		
	}

	surface->id = ibutterfree_surface_counter;
	ibutterfree_surface_counter++;

	surface->desc = (IButterFreeSurfaceDescription *) malloc(sizeof(IButterFreeSurfaceDescription));
	memcpy(surface->desc, desc, sizeof(IButterFreeSurfaceDescription));

	if (!surface->desc) 
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Invalid IButterFreeSurfaceDescription");
		return IBUTTERFREE_ERROR;		
	}

	long screenbuffersize =  sizeof(int32_t) * surface->desc->width * surface->desc->height;

	surface->frontscreenbuffer = (int32_t *) malloc(screenbuffersize);
	if (!surface->frontscreenbuffer)
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "MainScreeBuffer cannot be created");
		return IBUTTERFREE_ERROR;
	}

	memset(surface->frontscreenbuffer, (int32_t) 0xFFFFFFFF, screenbuffersize);

	if (surface->desc->buffer == DOUBLE)
	{
		surface->backscreenbuffer = (int32_t *)malloc(screenbuffersize);
		if (!surface->backscreenbuffer)
		{
			ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "backscreenbuffer cannot be created");
			return IBUTTERFREE_ERROR;
		}
		memset(surface->backscreenbuffer, (int32_t)0xFFFFFFFF, screenbuffersize);
	}

	surface->desc->color = 0x000000FF;

	return IBUTTERFREE_OK;
}

void ibutterfree_destroy_surface(IButterFreeSurface * surface)
{
	if (surface)
	{
		ibutterfree_surface_counter--;
		if (surface->frontscreenbuffer)
		{
			free(surface->frontscreenbuffer);
			surface->frontscreenbuffer = NULL;
		}
		if (surface->desc->buffer == DOUBLE)
		{
			if (surface->backscreenbuffer)
			{
				free(surface->backscreenbuffer);
				surface->backscreenbuffer = NULL;
			}
		}
		if (surface->desc) 
		{
			free(surface->desc);
			surface->desc = NULL;
		}
	}
}

IBUTTERFREE_RET ibutterfree_surface_set_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc)
{
	if (surface)
	{
		free(surface->desc);
		surface->desc = NULL;
		memcpy(surface->desc, desc, sizeof(IButterFreeSurfaceDescription));
		return IBUTTERFREE_OK;
	}
	else
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Error to set surface description");
		return IBUTTERFREE_ERROR;				
	}
}

IBUTTERFREE_RET ibutterfree_surface_get_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc)
{
	if (surface)
	{
		if (surface->desc) 
		{
			memcpy(desc, surface->desc, sizeof(IButterFreeSurfaceDescription));
			return IBUTTERFREE_OK;
		}
		else
		{
			ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Error to get surface description [description is NULL]");
			return IBUTTERFREE_ERROR;
		}
	}
	else
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Error to get surface description [surface is NULL]");
		return IBUTTERFREE_ERROR;				
	}
}

IBUTTERFREE_RET ibutterfree_surface_get_id(IButterFreeSurface * surface, int * id)
{
	if (surface)
	{
		*id = surface->id;
	}
	else
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Error to get surface id [surface is NULL]");		
	}
	return IBUTTERFREE_OK;
}

IBUTTERFREE_RET ibutterfree_clear_surface(IButterFreeSurface * surface, int32_t color)
{
	if (surface)
	{
		wmemset(surface->frontscreenbuffer, color, surface->desc->width * surface->desc->height);
		return IBUTTERFREE_OK;
	}
	else
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Failed to clear surface");
		return IBUTTERFREE_ERROR;
	}
}
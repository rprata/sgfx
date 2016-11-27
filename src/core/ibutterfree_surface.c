#include "ibutterfree_surface.h"

static long ibutterfree_surface_counter = 0;

IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc)
{
	if (!m_bfs) 
	{
		IBUTTERFREE_LOG_ERROR("Invalid IButterFreeStruct");
		return IBUTTERFREE_ERROR;
	}

	if (!surface)
	{
		IBUTTERFREE_LOG_ERROR("IButterFreeSurface cannot be created");
		return IBUTTERFREE_ERROR;		
	}

	surface->id = ibutterfree_surface_counter;
	ibutterfree_surface_counter++;

	surface->desc = (IButterFreeSurfaceDescription *) malloc(sizeof(IButterFreeSurfaceDescription));
	memcpy(surface->desc, desc, sizeof(IButterFreeSurfaceDescription));

	if (!surface->desc)
	{
		IBUTTERFREE_LOG_ERROR("Invalid IButterFreeSurfaceDescription");
		return IBUTTERFREE_ERROR;		
	}

	if (surface->desc->width < -1 || surface->desc->height < -1)
	{
		IBUTTERFREE_LOG_ERROR("Invalid IButterFreeSurfaceDescription");
		return IBUTTERFREE_ERROR;		
	}

	if (surface->desc->width == -1)
	{
		surface->desc->width = m_bfs->vinfo.xres_virtual;
	}

	if (surface->desc->height == -1)
	{
		surface->desc->height = m_bfs->vinfo.yres_virtual;
	}

	surface->desc->screensize = surface->desc->width * surface->desc->height;
	long screenbuffersize =  sizeof(int32_t) * surface->desc->screensize;

	surface->screenbuffer = (int32_t *) malloc(screenbuffersize);
	if (!surface->screenbuffer)
	{
		IBUTTERFREE_LOG_ERROR("ScreenBuffer cannot be created");
		return IBUTTERFREE_ERROR;
	}

	memset(surface->screenbuffer, (int32_t) 0xFFFFFFFF, screenbuffersize);

	surface->desc->color = 0x000000FF;

	return IBUTTERFREE_OK;
}

void ibutterfree_destroy_surface(IButterFreeSurface * surface)
{
	if (surface)
	{
		ibutterfree_surface_counter--;
		if (surface->screenbuffer)
		{
			free(surface->screenbuffer);
			surface->screenbuffer = NULL;
		}
		if (surface->desc) 
		{
			free(surface->desc);
			surface->desc = NULL;
		}
	}
}


IBUTTERFREE_RET ibutterfree_get_resolution(IButterFreeSurface * surface, int * xres, int * yres)
{
    if (surface)
    {
        *xres = surface->desc->width;
        *yres = surface->desc->height;
        return IBUTTERFREE_OK;
    }
    else
    {
    	IBUTTERFREE_LOG_ERROR("Failed to get resolution");
    	return IBUTTERFREE_ERROR;
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
		IBUTTERFREE_LOG_ERROR("Error to set surface description");
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
			IBUTTERFREE_LOG_ERROR("Error to get surface description [description is NULL]");
			return IBUTTERFREE_ERROR;
		}
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Error to get surface description [surface is NULL]");
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
		IBUTTERFREE_LOG_ERROR("Error to get surface id [surface is NULL]");		
	}
	return IBUTTERFREE_OK;
}

IBUTTERFREE_RET ibutterfree_clear_surface(IButterFreeSurface * surface, int32_t color)
{
	if (surface)
	{
		wmemset(surface->screenbuffer, color, surface->desc->screensize);
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Failed to clear surface");
		return IBUTTERFREE_ERROR;
	}
}
#include "ibutterfree_surface.h"

static long ibutterfree_surface_counter = 0;

IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeStruct * bfs, IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc)
{
	if (!surface)
	{
		if (!bfs) 
		{
			ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Invalid IButterFreeStruct");
			return IBUTTERFREE_ERROR;
		}

		surface = (IButterFreeSurface *)malloc(sizeof(IButterFreeSurface));
		if (!surface)
		{
			ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "IButterFreeSurface cannot be created");
			return IBUTTERFREE_ERROR;		
		}

		surface->id = ibutterfree_surface_counter;
		ibutterfree_surface_counter++;

		memcpy(surface->desc, desc, sizeof(IButterFreeSurfaceDescription));

		if (!surface->desc) 
		{
			ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "Invalid IButterFreeSurfaceDescription");
			return IBUTTERFREE_ERROR;		
		}
	}
	return IBUTTERFREE_OK;
}

void ibutterfree_destroy_surface(IButterFreeSurface * surface)
{
	if (surface)
	{
		ibutterfree_surface_counter--;
		if (surface->desc) 
		{
			free(surface->desc);
			surface->desc = NULL;
		}
		free(surface);
		surface = NULL;
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
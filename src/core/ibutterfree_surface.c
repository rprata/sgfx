#include "ibutterfree_surface.h"


IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeStruct * bfs, IButterFreeSurface * surface)
{
	if (!bfs) 
	{
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "bfs is invalid");
		return IBUTTERFREE_ERROR;
	}
	
	return IBUTTERFREE_OK;
}



#ifndef __IBUTTERFREE_SURFACE_H__
#define __IBUTTERFREE_SURFACE_H__

#include "ibutterfree.h"

typedef enum IButterFreeSurfaceBuffer {
	SINGLE, 
	DOUBLE
} IButterFreeSurfaceBuffer;

typedef enum IButterFreeSurfaceType {
	PRIMARY, 
	NORMAL
} IButterFreeSurfaceType;

typedef struct IButterFreeSurfaceDescription {
	int width;
	int height;
	IButterFreeSurfaceType type;
	IButterFreeSurfaceBuffer buffer;
} IButterFreeSurfaceDescription;

typedef struct IButterFreeSurface {
	int id;
	IButterFreeSurfaceDescription * desc;
} IButterFreeSurface;

IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeStruct * bfs, IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);
void ibutterfree_destroy_surface(IButterFreeSurface * surface);
IBUTTERFREE_RET ibutterfree_surface_set_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);
IBUTTERFREE_RET ibutterfree_surface_get_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);
IBUTTERFREE_RET ibutterfree_surface_get_id(IButterFreeSurface * surface, int * id);

#endif
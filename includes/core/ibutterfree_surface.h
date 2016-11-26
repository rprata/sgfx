#ifndef __IBUTTERFREE_SURFACE_H__
#define __IBUTTERFREE_SURFACE_H__

#include "ibutterfree.h"
#include <stdint.h>
#include <wchar.h>

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
	int32_t color;
	IButterFreeSurfaceType type;
	IButterFreeSurfaceBuffer buffer;
} IButterFreeSurfaceDescription;

typedef struct IButterFreeSurface {
	int id;
	IButterFreeSurfaceDescription * desc;
	int32_t * screenbuffer;
} IButterFreeSurface;

IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);
void ibutterfree_destroy_surface(IButterFreeSurface * surface);
IBUTTERFREE_RET ibutterfree_surface_set_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);
IBUTTERFREE_RET ibutterfree_surface_get_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);
IBUTTERFREE_RET ibutterfree_surface_get_id(IButterFreeSurface * surface, int * id);
IBUTTERFREE_RET ibutterfree_clear_surface(IButterFreeSurface * surface, int32_t color);

#endif
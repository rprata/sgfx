#ifndef __IBUTTERFREE_SURFACE_H__
#define __IBUTTERFREE_SURFACE_H__

#include "ibutterfree.h"

typedef struct IButterFreeSurface {
	int fbfd;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize;
	char *fbp;
} IButterFreeSurface;

IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeStruct * bfs, IButterFreeSurface * surface);

#endif
#include "ibutterfree_draw.h"
#include "ibutterfree_definitions.h"

IBUTTERFREE_RET __ibutterfree_swap_buffers(void)
{
	// char * tmp = (char *)malloc(m_bfs->screensize);
	// memcpy(tmp, m_bfs->fbp, m_bfs->screensize);
	memcpy(m_bfs->fbp, m_bfs->bbp, m_bfs->screensize);
	// memcpy(m_bfs->bbp, tmp, m_bfs->screensize);
	// free(tmp);
	// tmp = NULL;
	return IBUTTERFREE_OK;
}

IBUTTERFREE_RET __ibutterfree_draw_pixel(IButterFreeSurface * surface, int px, int py, int32_t rgba)
{
	if (m_bfs)
	{
		struct fb_var_screeninfo vinfo = m_bfs->vinfo;
		struct fb_fix_screeninfo finfo = m_bfs->finfo;
		char * bp;
		if (surface->desc->buffer == DOUBLE)
		{
			bp = m_bfs->bbp;
		}
		else
		{
			bp = m_bfs->fbp;
		}

		long location = (px+vinfo.xoffset) * (vinfo.bits_per_pixel / 8) + (py+vinfo.yoffset) * finfo.line_length;

		if (vinfo.bits_per_pixel == 32)
		{
            *(bp + location) = (rgba & 0xFF000000) >> 24;       // blue
            *(bp + location + 1) = (rgba & 0x00FF0000) >> 16;   // green
            *(bp + location + 2) = (rgba & 0x0000FF00) >> 8;    // red
            *(bp + location + 3) = (rgba & 0x000000FF);      	 // transparency
        } 
        else //assume 16bpp
        { 
            int b = (rgba & 0xFF000000) >> 24;  				 //blue
            int g = (rgba & 0x00FF0000) >> 16; 					 // green
            int r = (rgba & 0x0000FF00) >> 8; 					 // red
            unsigned short int t = r << 11 | g << 5 | b;
            *((unsigned short int *)(bp + location)) = t;
		}

		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_ERROR("__ibutterfree_draw_pixel has failed");
		return IBUTTERFREE_ERROR;
	}
}
IBUTTERFREE_RET __ibutterfree_draw_screenbuffer(IButterFreeSurface * surface, int px, int py, int32_t rgba)
{

	if (surface) 
	{
		surface->screenbuffer[px + py * surface->desc->width] = rgba;
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_ERROR("Invalid IButterFreeSurface");
		return IBUTTERFREE_ERROR;
	}
	
}

inline void __draw_horizontal_line(IButterFreeSurface * surface, int x0, int x1, int y, uint32_t rgba)
{
	int i;
	for (i = x0;i <= x1; i++)
		__ibutterfree_draw_screenbuffer(surface, i, y, rgba);
}

inline void __draw_vertical_line(IButterFreeSurface * surface, int x, int y0, int y1, uint32_t rgba)
{
	int i;
	for (i = y0; i <= y1; i++)
		__ibutterfree_draw_screenbuffer(surface, x, i, rgba);
}

IBUTTERFREE_RET ibutterfree_draw_line(IButterFreeSurface * surface, int x0, int y0, int x1, int y1)
{
	if (surface)
	{
		if (x0 == x1)
		{
			__draw_vertical_line(surface, x0, y0, y1, surface->desc->color);
			return IBUTTERFREE_OK;
		}

		if (y0 == y1)
		{
			__draw_horizontal_line(surface, x0, x1, y0, surface->desc->color);
			return IBUTTERFREE_OK;
		}

		// Using Generalized Bresenham's Line Drawing Algorithm 
		int i = 0;
		int dx = x1 - x0;
		int dy = y1 - y0;		
		int dxabs = abs(dx);
		int dyabs = abs(dy);		
		int sdx = sign(dx);		    
		int sdy = sign(dy);
		int x = dyabs >> 1;
		int y = dxabs >> 1;
		int px = x0;
		int py = y0;

		if (dxabs >= dyabs)
		{
			for (i = 0; i< dxabs; i++)
			{
				y += dyabs;
				if (y >= dxabs)
				{
					y -= dxabs;
					py += sdy;
				}
				px+=sdx;
				__ibutterfree_draw_screenbuffer(surface, px, py, surface->desc->color);
			}
		}
		else
		{
			for(i = 0; i < dyabs; i++)
			{
				x += dxabs;
				if ( x>= dyabs)
				{
					x -= dyabs;
					px+=sdx;
				}
				py += sdy;
				__ibutterfree_draw_screenbuffer(surface, px, py, surface->desc->color);
			}
		}
		
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_ERROR("ibutterfree_draw_line has failed");
		return IBUTTERFREE_ERROR;
	}
}

IBUTTERFREE_RET ibutterfree_draw_circle(IButterFreeSurface * surface, double cx, double cy, int radius)
{
	// Using Midpoint Circle Algorithm
	inline void plot4points(IButterFreeSurface * surface, double cx, double cy, double x, double y, uint32_t rgba)
	{
		__ibutterfree_draw_screenbuffer(surface, cx + x, cy + y, surface->desc->color);		
		__ibutterfree_draw_screenbuffer(surface, cx - x, cy + y, surface->desc->color);		
		__ibutterfree_draw_screenbuffer(surface, cx + x, cy - y, surface->desc->color);		
		__ibutterfree_draw_screenbuffer(surface, cx - x, cy - y, surface->desc->color);		
	}

	inline void plot8points(IButterFreeSurface * surface, double cx, double cy, double x, double y, uint32_t rgba)
	{
		plot4points(surface, cx, cy, x, y, rgba);
		plot4points(surface, cx, cy, y, x, rgba);
	}

	int error = -radius;
	double x = radius;
	double y = 0;

	while (x >= y)
	{
		plot8points(surface, cx, cy, x, y, surface->desc->color);

		error += y;
		y++;
		error += y;

		if (error >= 0)
		{
			error += -x;
			x--;
			error += -x;
		}
	}
	return IBUTTERFREE_OK;
}

IBUTTERFREE_RET ibutterfree_set_color(IButterFreeSurface * surface, int32_t color)
{
	surface->desc->color = color;
	return IBUTTERFREE_OK;
}

IBUTTERFREE_RET ibutterfree_flip(IButterFreeSurface * surface)
{
	if (surface && m_bfs)
	{
		int i = 0;
		
		for (i = 0; i < surface->desc->width * surface->desc->height; i += 1)
		{
			__ibutterfree_draw_pixel(surface, i % surface->desc->width, i / surface->desc->width, surface->screenbuffer[i]);
		}

		if (surface->desc->buffer == DOUBLE)
		{
			__ibutterfree_swap_buffers();
		}

		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_ERROR("Invalid IButterFreeSurface or IButterFreeStruct");
		return IBUTTERFREE_ERROR;
	}

}
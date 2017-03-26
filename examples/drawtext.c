#include <ibutterfree.h>
#include <ibutterfree_log.h>
#include <ibutterfree_surface.h>
#include <ibutterfree_draw.h>
#include <ibutterfree_image.h>
#include <ibutterfree_font.h>


int main (int argc, char ** argv)
{
	if (ibutterfree_init(argc, argv) == IBUTTERFREE_OK)
	{
		IButterFreeSurface surface;
		IButterFreeSurfaceDescription desc;
		desc.width = -1;
		desc.height = -1;
		desc.color = (int32_t) 0x000000FF;
		desc.type = PRIMARY;
		desc.buffer = DOUBLE; 
		if(ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK)
		{
			int xres, yres;
			ibutterfree_get_resolution(&surface, &xres, &yres);
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/4, yres/40, yres/40,  0xFF0000FF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/3, yres/20, yres/20,  0x00FF00FF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/2, yres/13, yres/13,  0x0000FFFF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/1.5, yres/11, yres/11,  0xFFFFFFFF, 0x000000FF);
			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
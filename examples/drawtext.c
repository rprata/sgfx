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
			int xres = 0, yres = 0;
			ibutterfree_get_resolution(&surface, &xres, &yres);
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/7, xres/40, yres/40,  0xFF0000FF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/3, xres/20, yres/20,  0x00FF00FF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/2, xres/16, yres/16,  0x0000FFFF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", xres/7, yres/1.5, xres/13, yres/13,  0xFFFFFFFF, 0x000000FF);
			ibutterfree_flip(&surface, NULL);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
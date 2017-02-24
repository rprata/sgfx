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
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", 200, 200, 20, 20,  0xFF0000FF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", 200, 280, 40, 40,  0x00FF00FF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", 200, 360, 60, 60,  0x0000FFFF, 0x000000FF);
			ibutterfree_draw_text(&surface, "Hello World", 200, 480, 80, 80,  0xFFFFFFFF, 0x000000FF);
			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
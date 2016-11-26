#include <ibutterfree.h>
#include <ibutterfree_log.h>
#include <ibutterfree_surface.h>
#include <ibutterfree_draw.h>

int main (int argc, char ** argv)
{
	ibutterfree_set_msg_level(IBUTTERFREE_MSG_LEVEL_ALL);
	if (ibutterfree_init(argc, argv) == IBUTTERFREE_OK)
	{
		IButterFreeSurface surface;
		IButterFreeSurfaceDescription desc;
		desc.width = 1280;
		desc.height = 720;
		desc.color = 0x000000FF;
		desc.type = PRIMARY;
		desc.buffer = SINGLE;
		if(ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK)
		{
			ibutterfree_draw_line(&surface, 0, 720, 1280, 0);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);
			ibutterfree_draw_line(&surface, 0, 0, 1280, 720);
			ibutterfree_set_color(&surface, (int32_t)0xFF0000FF);
			ibutterfree_draw_line(&surface, 640, 0, 640, 720);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
			ibutterfree_draw_line(&surface, 0, 360, 1280, 360);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);
			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
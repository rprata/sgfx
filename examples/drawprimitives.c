#include <ibutterfree.h>
#include <ibutterfree_log.h>
#include <ibutterfree_surface.h>
#include <ibutterfree_draw.h>

int main (int argc, char ** argv)
{
	if (ibutterfree_init(argc, argv) == IBUTTERFREE_OK)
	{
		IButterFreeSurface surface;
		IButterFreeSurfaceDescription desc;
		desc.width = 1280;
		desc.height = 720;
		desc.color = (int32_t) 0x000000FF;
		desc.type = PRIMARY;
		desc.buffer = DOUBLE;
		if(ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK)
		{
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);

			ibutterfree_draw_line(&surface, 0, 720, 1280, 0);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);
			ibutterfree_draw_line(&surface, 0, 0, 1280, 720);
			ibutterfree_set_color(&surface, (int32_t)0xFF0000FF);
			ibutterfree_draw_line(&surface, 640, 0, 640, 720);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
			ibutterfree_draw_line(&surface, 0, 360, 1280, 360);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);

			ibutterfree_fill_rect(&surface, 200, 200, 500, 200);
			ibutterfree_draw_rect(&surface, 100, 100, 700, 400);

			ibutterfree_set_color(&surface, (int32_t)0x00AAFFFF);
			ibutterfree_draw_circle(&surface, 700, 500, 200);
			ibutterfree_fill_circle(&surface, 700, 500, 100);

			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
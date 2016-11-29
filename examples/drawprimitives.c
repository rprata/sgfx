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
		desc.width = -1;
		desc.height = -1;
		desc.color = (int32_t) 0x000000FF;
		desc.type = PRIMARY;
		desc.buffer = SINGLE; 
		if(ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK)
		{
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);

			ibutterfree_draw_line(&surface, 0, 768, 1366, 0);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);
			ibutterfree_draw_line(&surface, 0, 0, 1366, 768);
			ibutterfree_set_color(&surface, (int32_t)0xFF0000FF);
			ibutterfree_draw_line(&surface, 683, 0, 683, 768);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
			ibutterfree_draw_line(&surface, 0, 384, 1366, 384);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);
			ibutterfree_fill_rect(&surface, 200, 200, 500, 200);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFAF);

			ibutterfree_draw_rect(&surface, 100, 100, 700, 400);

			ibutterfree_set_color(&surface, (int32_t)0x00AAFFFF);
			ibutterfree_draw_circle(&surface, 700, 500, 200);
			ibutterfree_set_color(&surface, (int32_t)0xFF000037);
			ibutterfree_fill_circle(&surface, 700, 500, 100);

			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
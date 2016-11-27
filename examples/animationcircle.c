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
			int i = 1000;
			while(1)
			{
				for (i = 300; i >= 0; i -= 1)
				{
					ibutterfree_draw_circle(&surface, 640, 360, i);
					ibutterfree_flip(&surface);
					usleep(10);
					ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
				}
			}
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
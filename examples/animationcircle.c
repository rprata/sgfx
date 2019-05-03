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
		desc.buffer = DOUBLE;
		if(ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK)
		{
			int xres = 0;
			int yres = 0;
			ibutterfree_get_resolution(&surface, &xres, &yres);
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
			int i = 0;
			while(1)
			{
				for (i = xres/2; i >= 0; i -= 1)
				{
					ibutterfree_fill_circle(&surface, xres/2, yres/2, i);
					ibutterfree_flip(&surface, NULL);
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
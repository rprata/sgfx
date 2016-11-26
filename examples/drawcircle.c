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
		desc.color = (int32_t) 0x000000FF;
		desc.type = PRIMARY;
		desc.buffer = SINGLE;
		if(ibutterfree_create_surface(&surface, &desc) == IBUTTERFREE_OK)
		{
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
			int i = 1000;
			for (i = 300; i >= 0; i -= 40)
			{
				ibutterfree_draw_circle(&surface, 640, 360, i);
			}

			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
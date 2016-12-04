#include <ibutterfree.h>
#include <ibutterfree_log.h>
#include <ibutterfree_surface.h>
#include <ibutterfree_draw.h>
#include <ibutterfree_image.h>

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
			ibutterfree_draw_image(&surface, "../examples/resources/images/IButterFree.bmp", 200, 200, -1, -1, IBUTTERFREE_IMAGE_TYPE_BMP);
			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
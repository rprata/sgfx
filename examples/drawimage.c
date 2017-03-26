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
			int xres, yres;
			ibutterfree_get_resolution(&surface, &xres, &yres);
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_draw_image(&surface, "../examples/resources/images/IButterFree.bmp", xres/7, yres/4, xres/7, xres/7, IBUTTERFREE_IMAGE_TYPE_BMP);
			ibutterfree_draw_image(&surface, "../examples/resources/images/IButterFree.ppm", xres/4, yres/2, xres/7, xres/7, IBUTTERFREE_IMAGE_TYPE_PPM);
			ibutterfree_draw_image(&surface, "../examples/resources/images/IButterFree.png", xres/7, yres/2, xres/7, xres/7, IBUTTERFREE_IMAGE_TYPE_PNG);
			ibutterfree_draw_image(&surface, "../examples/resources/images/IButterFree.png", xres/4, yres/4, xres/7, xres/7, IBUTTERFREE_IMAGE_TYPE_PNG);
			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
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
			int xres, yres;
			ibutterfree_get_resolution(&surface, &xres, &yres);
			ibutterfree_clear_surface(&surface, (int32_t) 0x000000FF);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);


			ibutterfree_draw_line(&surface, 0, yres, xres, 0);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFFF);
			ibutterfree_draw_line(&surface, 0, 0, xres, yres);
			ibutterfree_set_color(&surface, (int32_t)0xFF0000FF);
			ibutterfree_draw_line(&surface, xres/2, 0, xres/2, yres);
			ibutterfree_set_color(&surface, (int32_t)0x00FF00FF);
			ibutterfree_draw_line(&surface, 0, yres/2, xres, yres/2);
			ibutterfree_set_color(&surface, (int32_t)0xAA12FFFF);
			ibutterfree_fill_rect(&surface, xres/7, yres/4, xres/3, yres/4);
			ibutterfree_set_color(&surface, (int32_t)0x0000FFAF);

			ibutterfree_draw_rect(&surface, xres/14, xres/14, xres/3, yres/2);

			ibutterfree_set_color(&surface, (int32_t)0x00AAFFFF);
			ibutterfree_draw_circle(&surface, xres/2,yres/2, yres/4);
			ibutterfree_set_color(&surface, (int32_t)0xFF000037);
			ibutterfree_fill_circle(&surface, xres/2, yres/2, yres/6);

			ibutterfree_dump_surface(&surface, "image-output.ppm");

			ibutterfree_flip(&surface);
			ibutterfree_destroy_surface(&surface);
		}		
	}
	ibutterfree_close();

	return 0;
}
#include "ibutterfree_image.h"

unsigned char * __loadPPMImage(const char *filename, int * w, int * h)
{
	int width, height, num, size;

	FILE  *fp = fopen(filename, "r");

	if (!fp)
	{
		return NULL;
	}

	/* reading ppm header */
	char ch;
	int  maxval;

	if (fscanf(fp, "P%c\n", &ch) != 1 || ch != '6') 
	{
		return NULL;
	}

	ch = getc(fp);
	while (ch == '#')
	{
		do {
			ch = getc(fp);
	  	} while (ch != '\n');
	  	ch = getc(fp);
	}

	if (!isdigit(ch))
	{
		return NULL;
	}

	ungetc(ch, fp);

	if(fscanf(fp, "%d%d%d\n", &width, &height, &maxval) < 0)
	{
		return NULL;
	}

	if (maxval != 255) 
	{
		return NULL;
	}
	/* end reading ppm reader */

	*w = width;
	*h =height;
	size = width * height * 3;

	unsigned char * data   = (unsigned char *) malloc(size);

	if (!data)
	{
		return NULL;
	}

	num = fread((void *) data, 1, (size_t) size, fp);

	if (num != size)
	{
		return NULL;
	}

	fclose(fp);

	return data;
}

unsigned char * __loadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE * filePtr; 
    BITMAPFILEHEADER bitmapFileHeader; 
    unsigned char * bitmapImage;
    int imageIdx = 0;
    unsigned char tempRGB;
	size_t res = 0;

    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    res = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    if (res != 1)
    {
    	return NULL;
    }
    if (bitmapFileHeader.bfType != 0x4D42)
    {
        return NULL;
    }

    res = fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1,filePtr); // small edit. forgot to add the closing bracket at sizeof
    if (res != 1)
    {
    	return NULL;
    }

    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);

    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    res = fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
    if (res != bitmapInfoHeader->biSizeImage)
    {
    	return NULL;
    }

    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    if (bitmapInfoHeader->biBitCount == 24)
    {
	    for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	    {
	        tempRGB = bitmapImage[imageIdx];
	        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
	        bitmapImage[imageIdx + 2] = tempRGB;
	    }
	}

    if (bitmapInfoHeader->biBitCount == 32)
    {
	    for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 4)
	    {
	        tempRGB = bitmapImage[imageIdx];
	        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
	        bitmapImage[imageIdx + 2] = tempRGB;
	    }
    }

    fclose(filePtr);
    return bitmapImage;
}

void __flip_vertically(unsigned char *pixels, const size_t width, const size_t height, const size_t bytes_per_pixel)
{
    const size_t stride = width * bytes_per_pixel;
    unsigned char *row = malloc(stride);
    unsigned char *low = pixels;
    unsigned char *high = &pixels[(height - 1) * stride];

    for (; low < high; low += stride, high -= stride) {
        memcpy(row, low, stride);
        memcpy(low, high, stride);
        memcpy(high, row, stride);
    }
    free(row);
}

void __flip_horizontally(unsigned char *pixels, const size_t width, const size_t height, const size_t bytes_per_pixel)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < height * bytes_per_pixel; i += bytes_per_pixel)
	{
		for (j = 0; j < width * bytes_per_pixel / 2; j += bytes_per_pixel)
		{
			for (k = 0; k < bytes_per_pixel; k++)
			{
				int location = i*width + j + k;
				int newlocation = i*width + width*bytes_per_pixel - j + k;
				unsigned char temp = pixels[location];
				pixels[location] = pixels[newlocation];
				pixels[newlocation] = temp;
			}
		}
	}
}

int32_t * __resize_bilinear(int32_t * input, int sourceWidth, int sourceHeight, int targetWidth, int targetHeight)
{
	int32_t * temp = (int32_t *) malloc(targetWidth * targetHeight * sizeof(int32_t));
	int a, b, c, d, x, y, index, i, j;
    float x_ratio = ((float)(sourceWidth - 1)) / targetWidth;
    float y_ratio = ((float)(sourceHeight - 1)) / targetHeight;
    float x_diff, y_diff, blue, red, green ;
    int offset = 0 ;

    for (i = 0; i < targetHeight; i++) 
    {
        for (j = 0; j < targetWidth; j++) 
        {
            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            x_diff = (x_ratio * j) - x ;
            y_diff = (y_ratio * i) - y ;
            index = (y * sourceWidth + x) ;                
            a = input[index] ;
            b = input[index + 1] ;
            c = input[index + sourceWidth] ;
            d = input[index + sourceWidth + 1] ;

            // blue element
            blue = ((a >> 8) & 0xff) * (1 - x_diff) * (1 - y_diff) + ((b >> 8) & 0xff) * (x_diff) * (1 - y_diff) +
                   ((c >> 8) & 0xff) * (y_diff) * (1 - x_diff)   + ((d >> 8) & 0xff) * (x_diff * y_diff);

            // green element
            green = ((a >> 16) & 0xff) * (1 - x_diff) * (1 - y_diff) + ((b >> 16) & 0xff) * (x_diff) * (1 - y_diff) +
                    ((c >> 16) & 0xff) * (y_diff) * (1 - x_diff)   + ((d >> 16) & 0xff) * (x_diff * y_diff);

            // red element
            red = ((a >> 24) & 0xff) * (1-x_diff) * (1 - y_diff) + ((b >> 24) & 0xff) * (x_diff) * (1 - y_diff) +
                  ((c >> 24) & 0xff) * (y_diff) * (1 - x_diff)   + ((d >> 24) & 0xff) * (x_diff * y_diff);

            temp [offset++] = 
                    (int32_t) (0x000000ff + // alpha
                    ((((unsigned char)red)   << 24)&0xff000000) +
                    ((((unsigned char)green) << 16)&0x00ff0000) +
                    ((((unsigned char)blue)  << 8)&0x0000ff00));
        }
    }
    return temp;
}

IBUTTERFREE_RET ibutterfree_draw_image(IButterFreeSurface * surface, const char * filename, int x, int y, int width, int height, IButterFreeImageType type)
{
	if (surface)
	{
		if (type == IBUTTERFREE_IMAGE_TYPE_BMP)
		{
			BITMAPINFOHEADER bitmapInfoHeader;
			unsigned char * bitmapData = __loadBitmapFile(filename, &bitmapInfoHeader);
			if (bitmapData == NULL)
			{
				IBUTTERFREE_LOG_ERROR("Error to create bmp image.");
				ibutterfree_set_message_error("Error to create bmp image");
				return IBUTTERFREE_ERROR;
			}
			int i, j;
			int bpp = bitmapInfoHeader.biBitCount / 8;

			if ((width != bitmapInfoHeader.biWidth && width != -1) || (height != bitmapInfoHeader.biHeight && height != -1))
			{
				__flip_vertically(bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, bpp);
				int32_t * original_image = (int32_t *) malloc(bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * sizeof(int32_t));
				for (i = 0; i < bpp * bitmapInfoHeader.biHeight; i += bpp)
				{
					for (j = 0; j < bpp * bitmapInfoHeader.biWidth; j += bpp)
					{
						long absPosition = j + bitmapInfoHeader.biWidth * i;
						int32_t color = ((bitmapData[absPosition] << 24) & 0xFF000000) |
										((bitmapData[absPosition + 1] << 16) & 0x00FF0000) |
										((bitmapData[absPosition + 2] << 8) & 0x0000FF00) |
										((bpp == 4) ? ((bitmapData[absPosition + 3]) & 0x000000FF) : 0x000000FF);										

						if (absPosition / bpp < bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight)
							original_image[absPosition / bpp] = color;
					}
				}
				
				int32_t * resized_image = __resize_bilinear(original_image, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, width, height);

				free(original_image);
				original_image = NULL;

				for (i = 0; i < height; i += 1)
				{
					for (j = 0; j < width; j += 1)
					{
						long absPosition = j + width * i;
						ibutterfree_set_color(surface, resized_image[absPosition]);
						ibutterfree_draw_point(surface, x + j, y + i);
					}
				}
			}
			else
			{
				__flip_horizontally(bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, bpp);
				for (i = 0; i < bpp * bitmapInfoHeader.biHeight; i += bpp)
				{
					for (j = 0; j < bpp * bitmapInfoHeader.biWidth; j += bpp)
					{
						long absPosition = j + bitmapInfoHeader.biWidth * i;
						int32_t color = ((bitmapData[absPosition] << 24) & 0xFF000000) +
										((bitmapData[absPosition + 1] << 16) & 0x00FF0000) +
										((bitmapData[absPosition + 2] << 8) & 0x0000FF00) +
										((bpp == 4) ? ((bitmapData[absPosition + 3]) & 0x000000FF) : 0x000000FF);

						ibutterfree_set_color(surface, color);
						ibutterfree_draw_point(surface, x + abs(j / bpp - bitmapInfoHeader.biWidth), y + abs(i / bpp - bitmapInfoHeader.biHeight));
					}
				}
			}

		}
		else if (type == IBUTTERFREE_IMAGE_TYPE_PPM)
		{
			int i, j;
			int w = 0; 
			int h = 0;
			unsigned char * ppmData = __loadPPMImage(filename, &w, &h);
			
			if (ppmData == NULL)
			{
				IBUTTERFREE_LOG_ERROR("Error to create ppm image.");
				ibutterfree_set_message_error("Error to create ppm image");
				return IBUTTERFREE_ERROR;
			}

			if ((width != w && width != -1) || (height != h && height != -1))
			{
				int32_t * original_image = (int32_t *) malloc(h * w * sizeof(int32_t));
				for (i = 0; i < 3 * h; i += 3)
				{
					for (j = 0; j < 3 * w; j += 3)
					{
						long absPosition = j + w * i;
						int32_t color = ((ppmData[absPosition] << 24) & 0xFF000000) +
										((ppmData[absPosition + 1] << 16) & 0x00FF0000) +
										((ppmData[absPosition + 2] << 8) & 0x0000FF00) +
										0x000000FF;

						if (absPosition / 3 < w * h)
							original_image[absPosition / 3] = color;

					}
				}
				
				int32_t * resized_image = __resize_bilinear(original_image, w, h, width, height);

				free(original_image);
				original_image = NULL;

				for (i = 0; i < height; i += 1)
				{
					for (j = 0; j < width; j += 1)
					{
						long absPosition = j + width * i;
						ibutterfree_set_color(surface, resized_image[absPosition]);
						ibutterfree_draw_point(surface, x + j, y + i);
					}
				}

			}
			else
			{
				for (i = 0; i < 3 * h; i += 3)
				{
					for (j = 0; j < 3 * w; j += 3)
					{
						long absPosition = j + w * i;
						int32_t color = ((ppmData[absPosition] << 24) & 0xFF000000) +
										((ppmData[absPosition + 1] << 16) & 0x00FF0000) +
										((ppmData[absPosition + 2] << 8) & 0x0000FF00) +
										0x000000FF;

						ibutterfree_set_color(surface, color);
						ibutterfree_draw_point(surface, x + j / 3, y + i / 3);
					}
				}
			}
		}
		else if(type == IBUTTERFREE_IMAGE_TYPE_PNG)
		{
			ibutterfree_upng_t * ibutterfree_upng = ibutterfree_upng_new_from_file(filename);
			ibutterfree_upng_decode(ibutterfree_upng);
			if (ibutterfree_upng_get_error(ibutterfree_upng) != UPNG_EOK) {
				IBUTTERFREE_LOG_ERROR("Error to create png image.");
				ibutterfree_set_message_error("Error to create png image.");
				return IBUTTERFREE_ERROR;
			}

			const unsigned char * pngData = ibutterfree_upng_get_buffer(ibutterfree_upng);
			unsigned w = ibutterfree_upng_get_width(ibutterfree_upng);
			unsigned h = ibutterfree_upng_get_height(ibutterfree_upng);
			unsigned bpp = ibutterfree_upng_get_bpp(ibutterfree_upng) / 8;

			int i, j;

			if ((width != w && width != -1) || (height != h && height != -1))
			{
				int32_t * original_image = (int32_t *) malloc(h * w * sizeof(int32_t));

				for (i = 0; i < bpp * h; i += bpp)
				{
					for (j = 0; j < bpp * w; j += bpp)
					{
						long absPosition = j + w * i;
						int32_t color = ((pngData[absPosition] << 24) & 0xFF000000) +
										((pngData[absPosition + 1] << 16) & 0x00FF0000) +
										((pngData[absPosition + 2] << 8) & 0x0000FF00) +
										((bpp == 4) ? ((pngData[absPosition + 3]) & 0x000000FF) : 0x000000FF);


						if (absPosition / bpp < w * h)
							original_image[absPosition / bpp] = color;
					}
				}
				
				int32_t * resized_image =  __resize_bilinear(original_image, w, h, width, height);

				free(original_image);
				original_image = NULL;
				
				for (i = 0; i < height; i += 1)
				{
					for (j = 0; j < width; j += 1)
					{
						long absPosition = j + width * i;
						ibutterfree_set_color(surface, resized_image[absPosition]);
						ibutterfree_draw_point(surface, x + j, y + i);
					}
				}

			}
			else
			{
				for (i = 0; i < bpp * h; i += bpp)
				{
					for (j = 0; j < bpp * w; j += bpp)
					{
						long absPosition = j + w * i;
						int32_t color = ((pngData[absPosition] << 24) & 0xFF000000) +
										((pngData[absPosition + 1] << 16) & 0x00FF0000) +
										((pngData[absPosition + 2] << 8) & 0x0000FF00) +
										((bpp == 4) ? ((pngData[absPosition + 3]) & 0x000000FF) : 0x000000FF);

						ibutterfree_set_color(surface, color);
						ibutterfree_draw_point(surface, x + j / bpp, y + i / bpp);
					}
				}
			}
		}
		else if(type == IBUTTERFREE_IMAGE_TYPE_JPEG)
		{
			return IBUTTERFREE_NOT_IMPLEMENTED;
		}

		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Error to create image.");
		ibutterfree_set_message_error("Error to create image.");
		return IBUTTERFREE_ERROR;
	}
}

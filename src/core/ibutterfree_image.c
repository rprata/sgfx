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
	for (i = 0; i < height * bytes_per_pixel; i += bytes_per_pixel)
	{
		for (j = 0; j < width * bytes_per_pixel / 2; j += bytes_per_pixel)
		{
			for (int k = 0; k < bytes_per_pixel; k++)
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
				return IBUTTERFREE_ERROR;
			}
			int i, j;
			int bpp = bitmapInfoHeader.biBitCount / 8;

			__flip_horizontally(bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, bpp);

			for (i = 0; i <= bpp * bitmapInfoHeader.biHeight; i += bpp)
			{
				for (j = 0; j <= bpp * bitmapInfoHeader.biWidth; j += bpp)
				{
					long absPosition = j + bitmapInfoHeader.biWidth * i;
					int32_t color = ((bitmapData[absPosition] << 24) & 0xFF000000) +
									((bitmapData[absPosition + 1] << 16) & 0x00FF0000) +
									((bitmapData[absPosition + 2] << 8) & 0x0000FF00) +
									((bpp == 4) ? ((bitmapData[absPosition + 4]) & 0x000000FF) : 0x000000FF);

					ibutterfree_set_color(surface, color);
					ibutterfree_draw_point(surface, x + abs(j / bpp - bitmapInfoHeader.biWidth), y + abs(i / bpp - bitmapInfoHeader.biHeight));
				}
			}
		}
		else if (type == IBUTTERFREE_IMAGE_TYPE_PPM)
		{
			int w = 0; 
			int h = 0;
			unsigned char * ppmData = __loadPPMImage(filename, &w, &h);
			
			if (ppmData == NULL)
			{
				IBUTTERFREE_LOG_ERROR("Error to create ppm image.");
				return IBUTTERFREE_ERROR;
			}

			int i, j;

			for (i = 0; i <= 3 * h; i += 3)
			{
				for (j = 0; j <= 3 * w; j += 3)
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
		else if(type == IBUTTERFREE_IMAGE_TYPE_PNG)
		{
			ibutterfree_upng_t * ibutterfree_upng = ibutterfree_upng_new_from_file(filename);
			ibutterfree_upng_decode(ibutterfree_upng);
			if (ibutterfree_upng_get_error(ibutterfree_upng) != UPNG_EOK) {
				IBUTTERFREE_LOG_ERROR("Error to create png image.");
				return IBUTTERFREE_ERROR;
			}
			
			const unsigned char * pngData = ibutterfree_upng_get_buffer(ibutterfree_upng);
			unsigned w = ibutterfree_upng_get_width(ibutterfree_upng);
			unsigned h = ibutterfree_upng_get_height(ibutterfree_upng);
			unsigned bpp = ibutterfree_upng_get_bpp(ibutterfree_upng) / 8;

			int i, j;

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
		return IBUTTERFREE_OK;
	}
	else
	{
		IBUTTERFREE_LOG_ERROR("Error to create image.");
		return IBUTTERFREE_ERROR;
	}
}
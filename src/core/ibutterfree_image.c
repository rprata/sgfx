#include "ibutterfree_image.h"


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
				IBUTTERFREE_LOG_ERROR("Error to create  bmp image.");
				return IBUTTERFREE_ERROR;
			}
			int i, j;
			int bitcount = bitmapInfoHeader.biBitCount / 8;

			for (i = 0; i <= bitcount * bitmapInfoHeader.biHeight; i += bitcount)
			{
				for (j = 0; j <= bitcount * bitmapInfoHeader.biWidth; j += bitcount)
				{
					long absPosition = j + bitmapInfoHeader.biWidth * i;
					int32_t color = ((bitmapData[absPosition] << 24) & 0xFF000000) +
									((bitmapData[absPosition + 1] << 16) & 0x00FF0000) +
									((bitmapData[absPosition + 2] << 8) & 0x0000FF00) +
									((bitcount == 4) ? ((bitmapData[absPosition + 4]) & 0x000000FF) : 0x000000FF);

					ibutterfree_set_color(surface, color);
					ibutterfree_draw_point(surface, x + abs(j / bitcount - bitmapInfoHeader.biWidth), y + abs(i / bitcount - bitmapInfoHeader.biHeight));
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
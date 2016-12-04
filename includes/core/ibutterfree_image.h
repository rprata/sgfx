#ifndef __IBUTTERFREE_IMAGE_H__
#define __IBUTTERFREE_IMAGE_H__

#include "ibutterfree_draw.h"

#pragma pack(push, 1)

typedef struct BITMAPFILEHEADER
{
    int16_t bfType;
    int32_t bfSize;
    int16_t bfReserved1;
    int16_t bfReserved2;
    int32_t bOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER
{
    int32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    int16_t biPlanes;
    int16_t biBitCount;
    int32_t biCompression;
    int32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    int32_t biClrUsed;
    int32_t biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef enum IButterFreeImageType
{
	IBUTTERFREE_IMAGE_TYPE_BMP = 0,
	IBUTTERFREE_IMAGE_TYPE_PPM,
	IBUTTERFREE_IMAGE_TYPE_PNG,
	IBUTTERFREE_IMAGE_TYPE_JPEG,
} IButterFreeImageType;

IBUTTERFREE_RET ibutterfree_draw_image(IButterFreeSurface * surface, const char * filename, int x, int y, int width, int height, IButterFreeImageType type);

#endif
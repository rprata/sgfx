/****************************************************************************
 * Copyright (C) 2017 by Renan Prata                                        *
 *                                                                          *
 * This file is part of IButterFree.                                        *
 *                                                                          *
 *   IButterFree is free library: you can redistribute it and/or modify it  *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   IButterFree is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with IButterFree.                                        *
 *   If not, see <http://www.gnu.org/licenses/>.                            *
 ****************************************************************************/

/**
 * @file ibutterfree_image.h
 * @author Renan Prata
 * @date 07 Jan 2016
 * @brief File containing image functions of IButterFree Library.
 *
 * File containing image functions of IButterFree Library.
 * IButterFree has the possibility to render PNG, PPM and BMP images.
 * Requirements of PNG image: 8-bit/color RGBA, non-interlaced. In this case, 
 * we must use images with 32bit (with alpha). So, if you want to convert online, 
 * open the target image in https://pixlr.com/editor/ and save with full quality.
 */

#ifndef __IBUTTERFREE_IMAGE_H__
#define __IBUTTERFREE_IMAGE_H__

#include "ibutterfree_upng.h"
#include "ibutterfree_draw.h"

#pragma pack(push, 1)

typedef struct
{
    int16_t bfType;
    int32_t bfSize;
    int16_t bfReserved1;
    int16_t bfReserved2;
    int32_t bOffBits;
} BITMAPFILEHEADER;

typedef struct
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

/**
 * @brief The type of image.
 */
typedef enum
{
	IBUTTERFREE_IMAGE_TYPE_BMP = 0,    /**< BMP type. */
	IBUTTERFREE_IMAGE_TYPE_PPM,        /**< PPM type. */
	IBUTTERFREE_IMAGE_TYPE_PNG,        /**< PNG type. */
	IBUTTERFREE_IMAGE_TYPE_JPEG,       /**< JPEG type. */
} IButterFreeImageType;

/**
 * @brief Draw a image on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param filanme Path of image.
 * @param x Begin position in x-axis.
 * @param y Begin position in y-axis.
 * @param width Width of image.
 * @param heigh Height of image.
 * @param type Type of image.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_draw_image(IButterFreeSurface * surface, const char * filename, int x, int y, int width, int height, IButterFreeImageType type);

#endif
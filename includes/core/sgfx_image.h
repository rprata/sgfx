/****************************************************************************
 * Copyright (C) 2017 by Renan Prata                                        *
 *                                                                          *
 * This file is part of SGFX.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms            *
 * of the MIT license. See the LICENSE file for details.                    *
 ****************************************************************************/

/**
 * @file sgfx_image.h
 * @author Renan Prata
 * @date 07 Jan 2016
 * @brief File containing image functions of SGFX Library.
 *
 * File containing image functions of SGFX Library.
 * SGFX has the possibility to render PNG, PPM and BMP images.
 * Requirements of PNG image: 8-bit/color RGBA, non-interlaced. In this case,
 * we must use images with 32bit (with alpha). So, if you want to convert
 * online, open the target image in https://pixlr.com/editor/ and save with full
 * quality.
 */

#ifndef __SGFX_IMAGE_H__
#define __SGFX_IMAGE_H__

#include "sgfx_draw.h"
#include "sgfx_upng.h"

#pragma pack(push, 1)

typedef struct {
  int16_t bfType;
  int32_t bfSize;
  int16_t bfReserved1;
  int16_t bfReserved2;
  int32_t bOffBits;
} BITMAPFILEHEADER;

typedef struct {
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
typedef enum {
  SGFX_IMAGE_TYPE_BMP = 0, /**< BMP type. */
  SGFX_IMAGE_TYPE_PPM,     /**< PPM type. */
  SGFX_IMAGE_TYPE_PNG,     /**< PNG type. */
  SGFX_IMAGE_TYPE_JPEG,    /**< JPEG type. */
} SGFXImageType;

/**
 * @brief Draw a image on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param filename Path of image.
 * @param x Begin position in x-axis.
 * @param y Begin position in y-axis.
 * @param width Width of image.
 * @param height Height of image.
 * @param type Type of image.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_draw_image(SGFXSurface *surface, const char *filename, int x,
                         int y, int width, int height, SGFXImageType type);

#endif
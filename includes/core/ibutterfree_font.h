/****************************************************************************
 * Copyright (C) 2017 by Renan Prata                                        *
 *                                                                          *
 * This file is part of IButterFree.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms
 ** of the MIT license. See the LICENSE file for details.
 **
 ****************************************************************************/

/**
 * @file ibutterfree_font.h
 * @author Renan Prata
 * @date 07 Jan 2016
 * @brief File containing text functions of IButterFree Library.
 *
 * File containing text functions of IButterFree Library.
 * IButterFree has the possibility to render texts with different background
 * color and foreground color.
 */

#ifndef __IBUTTERFREE_FONT_H__
#define __IBUTTERFREE_FONT_H__

#include "ibutterfree_font8x8_basic.h"
#include "ibutterfree_image.h"
#include "string.h"

#define WIDTH 8
#define HEIGHT 8
#define SIZE 64
#define SPACE 3

/**
 * @brief Draw a text on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param filanme String of text.
 * @param x Begin position in x-axis.
 * @param y Begin position in y-axis.
 * @param width Width of text.
 * @param heigh Height of text.
 * @param background Background color.
 * @param foreground Foreground color.
 * @return IBUTTERFREE_RET is returned. In case of success, returns
 * IBUTTERFREE_OK, else, it returns IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_draw_text(IButterFreeSurface *surface,
                                      const char *text, int x, int y, int width,
                                      int height, int32_t background,
                                      int32_t foreground);

#endif
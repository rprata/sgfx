/****************************************************************************
 * Copyright (C) 2017 by Renan Prata                                        *
 *                                                                          *
 * This file is part of SGFX.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms
 ** of the MIT license. See the LICENSE file for details.
 **
 ****************************************************************************/

/**
 * @file sgfx_font.h
 * @author Renan Prata
 * @date 07 Jan 2016
 * @brief File containing text functions of SGFX Library.
 *
 * File containing text functions of SGFX Library.
 * SGFX has the possibility to render texts with different background
 * color and foreground color.
 */

#ifndef __SGFX_FONT_H__
#define __SGFX_FONT_H__

#include "sgfx_font8x8_basic.h"
#include "sgfx_image.h"
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
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_draw_text(SGFXSurface *surface, const char *text, int x, int y,
                        int width, int height, int32_t background,
                        int32_t foreground);

#endif
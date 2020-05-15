/****************************************************************************
 * Copyright (C) 2016 by Renan Prata                                        *
 *                                                                          *
 * This file is part of SGFX.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms
 ** of the MIT license. See the LICENSE file for details.
 **
 ****************************************************************************/

/**
 * @file sgfx_draw.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing primitive operation functions of SGFX Library.
 *
 * File containing primitive operation functions of SGFX Library.
 * SGFX has the possibility to draw a circle, a rectangle, a point,
 * and other primitive operations.
 * And also, you can update the screen using the flip function.
 */

#ifndef __SGFX_DRAW_H__
#define __SGFX_DRAW_H__

#include "sgfx_surface.h"

/**
 * @brief Structure relative of point.
 */
typedef struct {
  int x; /**< Position in x-axis. */
  int y; /**< Position in y-axis. */
} SGFXPoint;

/**
 * @brief Structure relative of rectangle.
 */
typedef struct {
  int x; /**< Position in x-axis. */
  int y; /**< Position in y-axis. */
  int w; /**< Width of rectangle. */
  int h; /**< Height of rectangle. */
} SGFXRect;

/**
 * @brief Draw a point on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param px Position in x-axis.
 * @param yx Position in y-axis.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_draw_point(SGFXSurface *surface, int px, int py);

/**
 * @brief Draw a line on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param x0 Begin position in x-axis.
 * @param y0 Begin position in y-axis.
 * @param x1 End position in x-axis.
 * @param y1 End position in y-axis.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_draw_line(SGFXSurface *surface, int x0, int y0, int x1, int y1);

/**
 * @brief Draw a circle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param cx Center position in x-axis.
 * @param cy Center position in y-axis.
 * @param radius Radius of circle.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_draw_circle(SGFXSurface *surface, double cx, double cy,
                          int radius);

/**
 * @brief Draw a fill circle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param cx Center position in x-axis.
 * @param cy Center position in y-axis.
 * @param radius Radius of circle.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_fill_circle(SGFXSurface *surface, double cx, double cy,
                          int radius);

/**
 * @brief Draw a rectangle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param x0 Begin position in x-axis.
 * @param y0 Begin position in y-axis.
 * @param w Width of rectangle.
 * @param h Height of rectangle.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_draw_rect(SGFXSurface *surface, int x0, int y0, int w, int h);

/**
 * @brief Draw a fill rectangle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param x0 Begin position in x-axis.
 * @param y0 Begin position in y-axis.
 * @param w Width of rectangle.
 * @param h Height of rectangle.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_fill_rect(SGFXSurface *surface, int x0, int y0, int w, int h);

/**
 * @brief Change color to next primitive drawing.
 *
 * @param surface Surface that is used to draw.
 * @param color Color used to draw in hexa value.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_set_color(SGFXSurface *surface, int32_t color);

/**
 * @brief Flip the surface to update screen.
 *
 * @param surface Surface that is used to draw.
 * @param rect Rectangle area that is used to draw. If value is NULL, screensize
 * is updated.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_flip(SGFXSurface *surface, SGFXRect *rect);

#endif
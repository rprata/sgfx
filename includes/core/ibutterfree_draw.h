/****************************************************************************
 * Copyright (C) 2016 by Renan Prata                                        *
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
 * @file ibutterfree_draw.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing primitive operation functions of IButterFree Library.
 *
 * File containing primitive operation functions of IButterFree Library.
 * IButterFree has the possibility to draw a circle, a rectangle, a point,
 * and other primitive operations.
 * And also, you can update the screen using the flip function.
 */

#ifndef __IBUTTERFREE_DRAW_H__
#define __IBUTTERFREE_DRAW_H__

#include "ibutterfree_surface.h"

/**
 * @brief Draw a point on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param px Position in x-axis.
 * @param yx Position in y-axis. 
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_draw_point(IButterFreeSurface * surface, int px, int py);

/**
 * @brief Draw a line on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param x0 Begin position in x-axis.
 * @param y0 Begin position in y-axis.
 * @param x1 End position in x-axis.
 * @param y1 End position in y-axis.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_draw_line(IButterFreeSurface * surface, int x0, int y0, int x1, int y1);

/**
 * @brief Draw a circle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param cx Center position in x-axis.
 * @param cy Center position in y-axis.
 * @param radius Radius of circle.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_draw_circle(IButterFreeSurface * surface, double cx, double cy, int radius);

/**
 * @brief Draw a fill circle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param cx Center position in x-axis.
 * @param cy Center position in y-axis.
 * @param radius Radius of circle.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_fill_circle(IButterFreeSurface * surface, double cx, double cy, int radius);

/**
 * @brief Draw a rectangle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param x0 Begin position in x-axis.
 * @param y0 Begin position in y-axis.
 * @param w Width of rectangle.
 * @param h Height of rectangle.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_draw_rect(IButterFreeSurface * surface, int x0, int y0, int w, int h);

/**
 * @brief Draw a fill rectangle on screenbuffer.
 *
 * @param surface Surface that is used to draw.
 * @param x0 Begin position in x-axis.
 * @param y0 Begin position in y-axis.
 * @param w Width of rectangle.
 * @param h Height of rectangle.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_fill_rect(IButterFreeSurface * surface, int x0, int y0, int w, int h);

/**
 * @brief Change color to next primitive drawing.
 *
 * @param surface Surface that is used to draw.
 * @param color Color used to draw in hexa value.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_set_color(IButterFreeSurface * surface, int32_t color);

/**
 * @brief Flip the surface to update screen.
 *
 * @param surface Surface that is used to draw.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_flip(IButterFreeSurface * surface);

#endif
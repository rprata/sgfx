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
 * @file ibutterfree_surface.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing surface functions of IButterFree Library.
 *
 * File containing surface functions of IButterFree Library.
 * IButterFree has the possibility to create many surfaces with
 * differents description.
 * And also, you can change color screen using the clear function.
 */

#ifndef __IBUTTERFREE_SURFACE_H__
#define __IBUTTERFREE_SURFACE_H__

#include "ibutterfree.h"
#include <stdint.h>

/**
 * @brief Structure relative of screenbuffer type used by surface.
 */
typedef enum {
	SINGLE, /**< Single-Buffer. */
	DOUBLE  /**< Double-Buffer */
} IButterFreeSurfaceBuffer;

/**
 * @brief Structure relative of surface type.
 */
typedef enum {
	PRIMARY, /**< Primary surface is the main surface used to draw. */
	NORMAL   /**< Auxiliary surface. */
} IButterFreeSurfaceType;

/**
 * @brief Structure relative of surface description.
 */
typedef struct {
	int width;  						/**< Width of surface */
	int height; 						/**< Height of surface */
	long screensize;					/**< Screen size of surface */
	int32_t color;						/**< Color of surface */
	IButterFreeSurfaceType type;		/**< Type of surface */
	IButterFreeSurfaceBuffer buffer;	/**< Screenbuffer type of surface */
} IButterFreeSurfaceDescription;

/**
 * @brief Structure relative of surface.
 */
typedef struct {
	int id;									/**< Id of surface */
	IButterFreeSurfaceDescription * desc;	/**< Description of surface */
	int32_t * screenbuffer;					/**< Screenbuffer of surface */
} IButterFreeSurface;

/**
 * @brief Creates a surface.
 *
 * @param surface Pointer of surface.
 * @param surface Description of surface.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_create_surface(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);

/**
 * @brief Destroys a surface.
 *
 * @param surface Pointer of surface.
 */
void ibutterfree_destroy_surface(IButterFreeSurface * surface);

/**
 * @brief Returns the screen resolution.
 *
 * @param surface Pointer of surface.
 * @param xres Pointer of width resolution.
 * @param yres Pointer of height resolution.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_get_resolution(IButterFreeSurface * surface, int * xres, int * yres);

/**
 * @brief Sets surface description.
 *
 * @param surface Pointer of surface.
 * @param desc Description of surface.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_surface_set_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);

/**
 * @brief Returns surface description.
 *
 * @param surface Pointer of surface.
 * @param desc Description of surface.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_surface_get_description(IButterFreeSurface * surface, IButterFreeSurfaceDescription * desc);

/**
 * @brief Returns surface id.
 *
 * @param surface Pointer of surface.
 * @param id Pointer of id surface.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_surface_get_id(IButterFreeSurface * surface, int * id);

/**
 * @brief Clears surface using a color.
 *
 * @param surface Pointer of surface.
 * @param color Color used to clear.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_clear_surface(IButterFreeSurface * surface, int32_t color);

/**
 * @brief Dump surface in a PPM File.
 *
 * @param surface Pointer of surface.
 * @param filename File PPM with dump surface.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_dump_surface(IButterFreeSurface * surface, const char * filename);

#endif
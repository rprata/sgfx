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
 * @file sgfx_surface.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing surface functions of SGFX Library.
 *
 * File containing surface functions of SGFX Library.
 * SGFX has the possibility to create many surfaces with
 * differents description.
 * And also, you can change color screen using the clear function.
 */

#ifndef __SGFX_SURFACE_H__
#define __SGFX_SURFACE_H__

#include "sgfx.h"
#include <stdint.h>

/**
 * @brief Structure relative of screenbuffer type used by surface.
 */
typedef enum {
  SINGLE, /**< Single-Buffer. */
  DOUBLE  /**< Double-Buffer */
} SGFXSurfaceBuffer;

/**
 * @brief Structure relative of surface type.
 */
typedef enum {
  PRIMARY, /**< Primary surface is the main surface used to draw. */
  NORMAL   /**< Auxiliary surface. */
} SGFXSurfaceType;

/**
 * @brief Structure relative of surface description.
 */
typedef struct {
  int width;                /**< Width of surface */
  int height;               /**< Height of surface */
  long screensize;          /**< Screen size of surface */
  int32_t color;            /**< Color of surface */
  SGFXSurfaceType type;     /**< Type of surface */
  SGFXSurfaceBuffer buffer; /**< Screenbuffer type of surface */
} SGFXSurfaceDescription;

/**
 * @brief Structure relative of surface.
 */
typedef struct {
  int id;                       /**< Id of surface */
  SGFXSurfaceDescription *desc; /**< Description of surface */
  int32_t *screenbuffer;        /**< Screenbuffer of surface */
} SGFXSurface;

/**
 * @brief Creates a surface.
 *
 * @param surface Pointer of surface.
 * @param surface Description of surface.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_create_surface(SGFXSurface *surface,
                             SGFXSurfaceDescription *desc);

/**
 * @brief Destroys a surface.
 *
 * @param surface Pointer of surface.
 */
void sgfx_destroy_surface(SGFXSurface *surface);

/**
 * @brief Returns the screen resolution.
 *
 * @param surface Pointer of surface.
 * @param xres Pointer of width resolution.
 * @param yres Pointer of height resolution.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_get_resolution(SGFXSurface *surface, int *xres, int *yres);

/**
 * @brief Sets surface description.
 *
 * @param surface Pointer of surface.
 * @param desc Description of surface.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET
sgfx_surface_set_description(SGFXSurface *surface,
                             SGFXSurfaceDescription *desc);

/**
 * @brief Returns surface description.
 *
 * @param surface Pointer of surface.
 * @param desc Description of surface.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET
sgfx_surface_get_description(SGFXSurface *surface,
                             SGFXSurfaceDescription *desc);

/**
 * @brief Returns surface id.
 *
 * @param surface Pointer of surface.
 * @param id Pointer of id surface.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_surface_get_id(SGFXSurface *surface, int *id);

/**
 * @brief Clears surface using a color.
 *
 * @param surface Pointer of surface.
 * @param color Color used to clear.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_clear_surface(SGFXSurface *surface, int32_t color);

/**
 * @brief Dump surface in a PPM File.
 *
 * @param surface Pointer of surface.
 * @param filename File PPM with dump surface.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_dump_surface(SGFXSurface *surface, const char *filename);

#endif
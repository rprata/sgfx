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
 * @file sgfx_event.h
 * @author Renan Prata
 * @date 26 Mar 2017
 * @brief File containing event functions of SGFX Library.
 *
 * File containing event functions of SGFX Library.
 * SGFX has the possibility to get event from touchscreen
 */

#ifndef __SGFX_EVENT_H__
#define __SGFX_EVENT_H__

#include "sgfx_surface.h"
#include <linux/input.h>
#ifdef __POSIX__
#include <pthread.h>
#endif

#define X_MAX 4096
#define Y_MAX 4096
#define X_MIN 0
#define Y_MIN 0

#define EV_ABS 0x03
#define ABS_X 0x00
#define ABS_Y 0x01
#define ABS_PRESSURE 0x18

/**
 * @brief Structure relative of touchscreen event.
 */
typedef struct {
  int pressed;  /**< If 1, it is pressed. Else, it is not pressed. */
  int x_abs;    /**< Absolute position in x-axys. */
  int y_abs;    /**< Absolute position in y-axys. */
  int pressure; /**< Pressure value (0 - 65555). */
} SGFXTouchStruct;

/**
 * @brief Structure of event callback.
 */
typedef void (*event_cb_t)(SGFXTouchStruct bfts);

/**
 * @brief Register event callback.
 *
 * @param surface Surface that is used to draw.
 * @param event_cb Callback registered.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
void sgfx_event_callback_register(SGFXSurface *surface, event_cb_t event_cb);

typedef struct {
  int evfd;
  struct input_event ev;
  event_cb_t cb;
} SGFXEventInternalStruct;

SGFXEventInternalStruct *m_sgevs;

/**
 * @brief Initializes event module.
 *
 * @param surface Surface that is used to draw.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_event_init(SGFXSurface *surface);

/**
 * @brief Finishes event module.
 *
 */
void sgfx_event_destroy(void);

/**
 * @brief  Reads event from touchscreen.
 *
 * @param bfts SGFXTouchStruct used to read.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_event_read(SGFXTouchStruct *bfts);

#endif
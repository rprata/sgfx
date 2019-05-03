/****************************************************************************
 * Copyright (C) 2016 by Renan Prata                                        *
 *                                                                          *
 * This file is part of IButterFree.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms			*
 * of the MIT license. See the LICENSE file for details.					*
 ****************************************************************************/

/**
 * @file ibutterfree_event.h
 * @author Renan Prata
 * @date 26 Mar 2017
 * @brief File containing event functions of IButterFree Library.
 *
 * File containing event functions of IButterFree Library.
 * IButterFree has the possibility to get event from touchscreen
 */

#ifndef __IBUTTERFREE_EVENT_H__
#define __IBUTTERFREE_EVENT_H__

#include "ibutterfree_surface.h"
#include <linux/input.h>
#ifdef __POSIX__
#include <pthread.h>
#endif

#define X_MAX 	4096
#define Y_MAX	4096
#define X_MIN 	0
#define Y_MIN 	0

#define EV_ABS			0x03
#define ABS_X			0x00
#define ABS_Y			0x01
#define ABS_PRESSURE	0x18


/**
 * @brief Structure relative of touchscreen event.
 */
typedef struct {
	int pressed;	/**< If 1, it is pressed. Else, it is not pressed. */
	int x_abs; 		/**< Absolute position in x-axys. */
	int y_abs; 		/**< Absolute position in y-axys. */
	int pressure; 	/**< Pressure value (0 - 65555). */
} IButterFreeTouchStruct;

/**
 * @brief Structure of event callback.
 */
typedef void (*event_cb_t) (IButterFreeTouchStruct bfts);

/**
 * @brief Register event callback.
 *
 * @param surface Surface that is used to draw.
 * @param event_cb Callback registered.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
void ibutterfree_event_callback_register(IButterFreeSurface * surface, event_cb_t event_cb);

typedef struct {
	int evfd;
	struct input_event ev;
	event_cb_t cb;
} IButterFreeEventInternalStruct;

IButterFreeEventInternalStruct * m_bfevs;

/**
 * @brief Initializes event module.
 *
 * @param surface Surface that is used to draw.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_event_init(IButterFreeSurface * surface);

/**
 * @brief Finishes event module.
 *
 */
void ibutterfree_event_destroy(void);

/**
 * @brief  Reads event from touchscreen.
 *
 * @param bfts IButterFreeTouchStruct used to read.
 * @return IBUTTERFREE_RET is returned. In case of success, returns IBUTTERFREE_OK, else, it returns 
 * IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_event_read(IButterFreeTouchStruct * bfts);

#endif
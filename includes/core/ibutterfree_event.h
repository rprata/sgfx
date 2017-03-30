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
 * @file ibutterfree_event.h
 * @author Renan Prata
 * @date 26 Mar 2017
 * @brief File containing event functions/callbacks of IButterFree Library.
 *
 * File containing event functions/callbacs of IButterFree Library.
 * IButterFree has the possibility to getevent from touchscreen or
 * from another device.
 */

#ifndef __IBUTTERFREE_EVENT_H__
#define __IBUTTERFREE_EVENT_H__

#include "ibutterfree_surface.h"
#include <linux/input.h>

#define INPUT "/dev/input/event3"

#define X_MAX 	4096
#define Y_MAX	4096
#define X_MIN 	0
#define Y_MIN 	0


#define EV_ABS			0x03
#define ABS_X			0x00
#define ABS_Y			0x01
#define ABS_PRESSURE	0x18


typedef struct {
	int evfd; /**< Handler of IButterFreeEventStruct. */
	struct input_event ev; /**< Handler of Input Event */
} IButterFreeEventStruct;


typedef struct {
	int pressed; /**< If 1, it is pressed. Else, it is not pressed. */
	int x_abs; /**< Absolute position in x-axys. */
	int y_abs; /**< Absolute position in y-axys. */
	int pressure; /**< Pressure value (0 - 65555). */
} IButterFreeTouchStruct;

// struct IButterFreeEventCB;

// typedef void (*event_cb_t) (const struct IButterFreeEventCB * evt, void * data);

// typedef struct {
//     event_cb_t cb;
//     void *data;
// } IButterFreeEventCB;

// static IButterFreeEventCB saved = { 0, 0 };

// void ibutterfree_event_callback_register(event_cb_t cb, void * data);

IButterFreeEventStruct * m_bfevs;

IBUTTERFREE_RET ibutterfree_event_init(IButterFreeSurface * surface);
void ibutterfree_event_destroy(void);
IBUTTERFREE_RET ibutterfree_event_read(IButterFreeTouchStruct * bfts);

#endif
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
 * @file ibutterfree_config.h
 * @author Renan Prata
 * @date 1 April 2017
 * @brief File containing functions for configure software in runtime.
 *
 * File File containing functions for configure software in 
 * runtime. You can specify outputs framebuffer file descriptor,
 * touchscreen filedescriptor, screen resolution and others. 
 * For more informations, see . file
 */

#ifndef __IBUTTERFREE_CONFIG_H__
#define __IBUTTERFREE_CONFIG_H__

#include "ibutterfree_log.h"

#define CONFIG 	".ibutterfreeconfig"
#define FB 	  	"/dev/fb0"
#define INPUT 	"/dev/input/event3"

/**
 * @brief Structure relative of configure.
 */
typedef struct {
	char fdfb[50];	/**< String related to framebuffer filedescriptor. */
	char fdev[50]; 	/**< String related to touchscreen filedescriptor */
} IButterFreeConfigStruct;

IButterFreeConfigStruct * m_bfcs;

/**
 * @brief Reads IButterFree configuration file.
 *
 * It's necessary if you want to setup graphic configuration in runtime.
 */
void ibutterfree_config_read(void);

/**
 * @brief get fdfb information (default is /dev/fb0).
 *
 * @return returns a const char * with fdfb information
 */
const char * ibutterfree_get_fdfb(void);

/**
 * @brief get fdev information (default is /dev/input/event3).
 *
 * @return returns a const char * with fdev information 
 */
const char * ibutterfree_get_fdev(void);

#endif

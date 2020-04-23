/****************************************************************************
 * Copyright (C) 2017 by Renan Prata                                        *
 *                                                                          *
 * This file is part of IButterFree.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms			*
 * of the MIT license. See the LICENSE file for details.					*
 ****************************************************************************/

#ifndef __IBUTTERFREE_DEFINITIONS_H__
#define __IBUTTERFREE_DEFINITIONS_H__

#define sign(x) ((x > 0)? 1 : ((x < 0)? -1: 0))

typedef enum _bool {
	false = 0, 
	true = 1
} bool;

#define NON_NULL(x) ((x)?(x):"")

#endif
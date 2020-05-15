/****************************************************************************
 * Copyright (C) 2016 by Renan Prata                                        *
 *                                                                          *
 * This file is part of IButterFree.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms
 ** of the MIT license. See the LICENSE file for details.
 **
 ****************************************************************************/

/**
 * @file ibutterfree.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing main functions of IButterFree Library main structures
 * used by library implementation.
 *
 * File containing initialization functions of library and
 * main structures used by library implementation.
 * IButterFree has different implemantions for different
 * architectures. Before initializing the library, make
 * sure that the architecture configuration is correct
 * in CMakeLists.txt file.
 */

#ifndef __IBUTTERFREE_H__
#define __IBUTTERFREE_H__

#include <ctype.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ibutterfree_config.h"
#include "ibutterfree_definitions.h"
#include "ibutterfree_log.h"

/**
 * @brief The kind of value that is returned by IButterFree library.
 */
typedef enum {
  IBUTTERFREE_ERROR,           /**< Error. */
  IBUTTERFREE_OK,              /**< Success. */
  IBUTTERFREE_NOT_IMPLEMENTED, /**< In case of not implemented yet. */
} IBUTTERFREE_RET;

/**
 * @brief Structure relative of screen characteristics.
 */
typedef struct {
  int fbfd; /**< Handler of IButterFreeStruct. */
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  long int screensize; /**< Screen Size. */
  char *fbp;           /**< Front-Buffer. */
  char *bbp;           /**< Back-Buffer. */
} IButterFreeStruct;

IButterFreeStruct *m_bfs;

/**
 * @brief Initializes IButterFree Graphic Module.
 *
 * @param argc Non-negative value representing the number of arguments passed to
 * the program from the environment in which the library is run.
 * @param argv  Pointer to the first element of an array of pointers to
 * null-terminated multibyte strings that represent the arguments passed to the
 * program from the execution environment.
 * @return IBUTTERFREE_RET is returned. In case of success, returns
 * IBUTTERFREE_OK, else, it returns IBUTTERFREE_ERROR.
 */
IBUTTERFREE_RET ibutterfree_init(int argc, char **argv);

/**
 * @brief Finishes IButterFree Graphic Module.
 *
 * It's necessary to finalize your application and free memory allocated.
 */
void ibutterfree_close(void);

#endif
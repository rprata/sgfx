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
 * @file sgfx.h
 * @author Renan Prata
 * @date 24 Nov 2016
 * @brief File containing main functions of SGFX Library main structures
 * used by library implementation.
 *
 * File containing initialization functions of library and
 * main structures used by library implementation.
 * SGFX has different implemantions for different
 * architectures. Before initializing the library, make
 * sure that the architecture configuration is correct
 * in CMakeLists.txt file.
 */

#ifndef __SGFX_H__
#define __SGFX_H__

#include <ctype.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "sgfx_config.h"
#include "sgfx_definitions.h"
#include "sgfx_log.h"

/**
 * @brief The kind of value that is returned by SGFX library.
 */
typedef enum {
  SGFX_ERROR,           /**< Error. */
  SGFX_OK,              /**< Success. */
  SGFX_NOT_IMPLEMENTED, /**< In case of not implemented yet. */
} SGFX_RET;

/**
 * @brief Structure relative of screen characteristics.
 */
typedef struct {
  int fbfd; /**< Handler of SGFXStruct. */
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  long int screensize; /**< Screen Size. */
  char *fbp;           /**< Front-Buffer. */
  char *bbp;           /**< Back-Buffer. */
} SGFXStruct;

SGFXStruct *m_sgfs;

/**
 * @brief Initializes SGFX Graphic Module.
 *
 * @param argc Non-negative value representing the number of arguments passed to
 * the program from the environment in which the library is run.
 * @param argv  Pointer to the first element of an array of pointers to
 * null-terminated multibyte strings that represent the arguments passed to the
 * program from the execution environment.
 * @return SGFX_RET is returned. In case of success, returns
 * SGFX_OK, else, it returns SGFX_ERROR.
 */
SGFX_RET sgfx_init(int argc, char **argv);

/**
 * @brief Finishes SGFX Graphic Module.
 *
 * It's necessary to finalize your application and free memory allocated.
 */
void sgfx_close(void);

#endif
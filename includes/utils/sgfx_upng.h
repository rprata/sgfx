/****************************************************************************
 * Copyright (C) 2016 by Renan Prata                                        *
 *                                                                          *
 * This file is part of SGFX.                                        *
 *                                                                          *
 * This software may be modified and distributed under the terms
 ** of the MIT license. See the LICENSE file for details.
 **
 ****************************************************************************/

#ifndef SGFX_UPNG_H
#define SGFX_UPNG_H

typedef enum sgfx_upng_error {
  UPNG_EOK = 0,           /* success (no error) */
  UPNG_ENOMEM = 1,        /* memory allocation failed */
  UPNG_ENOTFOUND = 2,     /* resource not found (file missing) */
  UPNG_ENOTPNG = 3,       /* image data does not have a PNG header */
  UPNG_EMALFORMED = 4,    /* image data is not a valid PNG image */
  UPNG_EUNSUPPORTED = 5,  /* critical PNG chunk type is not supported */
  UPNG_EUNINTERLACED = 6, /* image interlacing is not supported */
  UPNG_EUNFORMAT = 7,     /* image color format is not supported */
  UPNG_EPARAM = 8         /* invalid parameter to method call */
} sgfx_upng_error;

typedef enum sgfx_upng_format {
  UPNG_BADFORMAT,
  UPNG_RGB8,
  UPNG_RGB16,
  UPNG_RGBA8,
  UPNG_RGBA16,
  UPNG_LUMINANCE1,
  UPNG_LUMINANCE2,
  UPNG_LUMINANCE4,
  UPNG_LUMINANCE8,
  UPNG_LUMINANCE_ALPHA1,
  UPNG_LUMINANCE_ALPHA2,
  UPNG_LUMINANCE_ALPHA4,
  UPNG_LUMINANCE_ALPHA8
} sgfx_upng_format;

typedef struct sgfx_upng_t sgfx_upng_t;

sgfx_upng_t *sgfx_upng_new_from_bytes(const unsigned char *buffer,
                                      unsigned long size);
sgfx_upng_t *sgfx_upng_new_from_file(const char *path);
void sgfx_upng_free(sgfx_upng_t *sgfx_upng);

sgfx_upng_error sgfx_upng_header(sgfx_upng_t *sgfx_upng);
sgfx_upng_error sgfx_upng_decode(sgfx_upng_t *sgfx_upng);

sgfx_upng_error sgfx_upng_get_error(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_error_line(const sgfx_upng_t *sgfx_upng);

unsigned sgfx_upng_get_width(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_height(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_bpp(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_bitdepth(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_components(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_pixelsize(const sgfx_upng_t *sgfx_upng);
sgfx_upng_format sgfx_upng_get_format(const sgfx_upng_t *sgfx_upng);

const unsigned char *sgfx_upng_get_buffer(const sgfx_upng_t *sgfx_upng);
unsigned sgfx_upng_get_size(const sgfx_upng_t *sgfx_upng);

#endif /*defined(UPNG_H)*/

#include "sgfx_surface.h"

static long sgfx_surface_counter = 0;

SGFX_RET
sgfx_create_surface(SGFXSurface *surface, SGFXSurfaceDescription *desc) {
  if (!m_sgfs) {
    SGFX_LOG_ERROR("Invalid SGFXStruct");
    sgfx_set_message_error("Invalid SGFXStruct");
    return SGFX_ERROR;
  }

  if (!surface) {
    SGFX_LOG_ERROR("SGFXSurface cannot be created");
    sgfx_set_message_error("SGFXSurface cannot be created");
    return SGFX_ERROR;
  }

  surface->id = sgfx_surface_counter;
  sgfx_surface_counter++;

  surface->desc =
      (SGFXSurfaceDescription *)malloc(sizeof(SGFXSurfaceDescription));
  memcpy(surface->desc, desc, sizeof(SGFXSurfaceDescription));

  if (!surface->desc) {
    SGFX_LOG_ERROR("Invalid SGFXSurfaceDescription");
    sgfx_set_message_error("Invalid SGFXSurfaceDescription");
    return SGFX_ERROR;
  }

  if (surface->desc->width < -1 || surface->desc->height < -1) {
    SGFX_LOG_ERROR("Invalid SGFXSurfaceDescription");
    sgfx_set_message_error("Invalid SGFXSurfaceDescription");
    return SGFX_ERROR;
  }

  if (surface->desc->width == -1) {
    surface->desc->width = m_sgfs->vinfo.xres_virtual;
  }

  if (surface->desc->height == -1) {
    surface->desc->height = m_sgfs->vinfo.yres_virtual;
  }

  surface->desc->screensize = surface->desc->width * surface->desc->height;
  long screenbuffersize = sizeof(int32_t) * surface->desc->screensize;

  surface->screenbuffer = (int32_t *)malloc(screenbuffersize);
  if (!surface->screenbuffer) {
    SGFX_LOG_ERROR("ScreenBuffer cannot be created");
    sgfx_set_message_error("ScreenBuffer cannot be created");
    return SGFX_ERROR;
  }

  memset(surface->screenbuffer, (int32_t)0xFFFFFFFF, screenbuffersize);

  surface->desc->color = 0x000000FF;

  return SGFX_OK;
}

void sgfx_destroy_surface(SGFXSurface *surface) {
  if (surface) {
    sgfx_surface_counter--;
    if (surface->screenbuffer) {
      free(surface->screenbuffer);
      surface->screenbuffer = NULL;
    }
    if (surface->desc) {
      free(surface->desc);
      surface->desc = NULL;
    }
  }
}

SGFX_RET sgfx_get_resolution(SGFXSurface *surface, int *xres, int *yres) {
  if (surface) {
    *xres = surface->desc->width;
    *yres = surface->desc->height;
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("Failed to get resolution");
    sgfx_set_message_error("Failed to get resolution");
    return SGFX_ERROR;
  }
}

SGFX_RET
sgfx_surface_set_description(SGFXSurface *surface,
                             SGFXSurfaceDescription *desc) {
  if (surface) {
    free(surface->desc);
    memcpy(surface->desc, desc, sizeof(SGFXSurfaceDescription));
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("Error to set surface description");
    sgfx_set_message_error("Error to set surface description");
    return SGFX_ERROR;
  }
}

SGFX_RET
sgfx_surface_get_description(SGFXSurface *surface,
                             SGFXSurfaceDescription *desc) {
  if (surface) {
    if (surface->desc) {
      memcpy(desc, surface->desc, sizeof(SGFXSurfaceDescription));
      return SGFX_OK;
    } else {
      SGFX_LOG_ERROR("Error to get surface description [description is NULL]");
      sgfx_set_message_error(
          "Error to get surface description [description is NULL]");
      return SGFX_ERROR;
    }
  } else {
    SGFX_LOG_ERROR("Error to get surface description [surface is NULL]");
    sgfx_set_message_error(
        "Error to get surface description [surface is NULL]");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_surface_get_id(SGFXSurface *surface, int *id) {
  if (surface) {
    *id = surface->id;
  } else {
    SGFX_LOG_ERROR("Error to get surface id [surface is NULL]");
    sgfx_set_message_error("Error to get surface id [surface is NULL]");
  }
  return SGFX_OK;
}

SGFX_RET sgfx_clear_surface(SGFXSurface *surface, int32_t color) {
  if (surface) {
    uint32_t i;
    for (i = 0; i < surface->desc->screensize; i++) {
      (surface->screenbuffer)[i] = color;
    }
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("Failed to clear surface");
    sgfx_set_message_error("Failed to clear surface");
    return SGFX_ERROR;
  }
}

SGFX_RET sgfx_dump_surface(SGFXSurface *surface, const char *filename) {
  if (surface) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
      char msg[256];
      sprintf(msg, "Could not open output file %s", filename);
      SGFX_LOG_ERROR(msg);
      sgfx_set_message_error(msg);
      return SGFX_ERROR;
    }
    (void)fprintf(f, "P6\n%d %d\n255\n", surface->desc->width,
                  surface->desc->height);
    int i;
    for (i = 0; i < surface->desc->screensize; i++) {
      static unsigned char color[3];
      color[0] =
          (unsigned char)(((surface->screenbuffer[i] & 0x0000FF00) >> 8));
      color[1] =
          (unsigned char)(((surface->screenbuffer[i] & 0x00FF0000) >> 16));
      color[2] =
          (unsigned char)(((surface->screenbuffer[i] & 0xFF000000) >> 24));
      (void)fwrite(color, 1, 3, f);
    }
    (void)fclose(f);
    return SGFX_OK;
  } else {
    SGFX_LOG_ERROR("Failed to dump surface");
    sgfx_set_message_error("Failed to dump surface");
    return SGFX_ERROR;
  }
}
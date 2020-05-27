#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "sgfx.h"
#include "sgfx_draw.h"
#include "sgfx_log.h"
#include "sgfx_surface.h"
// https://gist.github.com/bloodstalker/91261e541666f16c3b8315d3ff1085d6

static SGFXRect *__checkSGFXRect(lua_State *L, int index) {
  SGFXRect *rect = NULL;

  if (!lua_isnil(L, index)) {
    rect = (SGFXRect *)malloc(sizeof(SGFXRect));
    lua_getfield(L, index, "x");
    rect->x = (int)lua_tonumber(L, index);
    lua_getfield(L, index - 1, "y");
    rect->y = (int)lua_tonumber(L, index);
    lua_getfield(L, index - 2, "w");
    rect->w = (int32_t)lua_tonumber(L, index);
    lua_getfield(L, index - 3, "h");
    rect->h = (SGFXSurfaceType)lua_tonumber(L, index);
  }

  return rect;
}

static SGFXSurfaceDescription __checkSGFXSurfaceDescription(lua_State *L,
                                                            int index) {
  SGFXSurfaceDescription desc;

  lua_getfield(L, index, "width");
  desc.width = (int)lua_tonumber(L, index);
  lua_getfield(L, index - 1, "height");
  desc.height = (int)lua_tonumber(L, index);
  lua_getfield(L, index - 2, "color");
  desc.color = (int32_t)lua_tonumber(L, index);
  lua_getfield(L, index - 3, "type");
  desc.type = (SGFXSurfaceType)lua_tonumber(L, index);
  lua_getfield(L, index - 4, "buffer");
  desc.buffer = (SGFXSurfaceBuffer)lua_tonumber(L, index);

  return desc;
}

static SGFXSurface *__checkSGFXSurface(lua_State *L, int index) {
  SGFXSurface *surface;
  luaL_checktype(L, index, LUA_TUSERDATA);
  surface = (SGFXSurface *)luaL_checkudata(L, index, "SGFXSurface");
  if (surface == NULL)
    luaL_error(L, "SGFXSurface cannot be created");
  return surface;
}

static SGFXSurface *__pushSGFXSurface(lua_State *L, SGFXSurface *surface) {
  SGFXSurface *l_surface =
      (SGFXSurface *)lua_newuserdata(L, sizeof(SGFXSurface));
  luaL_getmetatable(L, "SGFXSurface");
  lua_setmetatable(L, -2);
  memcpy(l_surface, surface, sizeof(SGFXSurface));
  lua_pushlightuserdata(L, l_surface);
  lua_pushvalue(L, -2);
  lua_settable(L, LUA_REGISTRYINDEX);
  return l_surface;
}

static int _lua_sgfx_init(lua_State *L) {
  if (sgfx_init(0, NULL) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_close(lua_State *L) {
  sgfx_close();
  return 1;
}

static int _lua_sgfx_create_surface(lua_State *L) {
  SGFXSurface surface;
  SGFXSurfaceDescription desc = __checkSGFXSurfaceDescription(L, -1);
  if (sgfx_create_surface(&surface, &desc) == SGFX_OK) {
    __pushSGFXSurface(L, &surface);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_set_description(lua_State *L) {
  SGFXSurfaceDescription desc = __checkSGFXSurfaceDescription(L, -1);
  SGFXSurface *surface = __checkSGFXSurface(L, -2);
  if (sgfx_surface_set_description(surface, &desc) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_get_resolution(lua_State *L) {
  SGFXSurface *surface = __checkSGFXSurface(L, -1);
  int xres = 0;
  int yres = 0;
  if (sgfx_get_resolution(surface, &xres, &yres) == SGFX_OK) {
    lua_pushboolean(L, true);
    lua_pushnumber(L, xres);
    lua_pushnumber(L, yres);
    return 3;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_surface_get_id(lua_State *L) {
  SGFXSurface *surface = __checkSGFXSurface(L, -1);
  int id = 0;
  if (sgfx_surface_get_id(surface, &id) == SGFX_OK) {
    lua_pushboolean(L, true);
    lua_pushnumber(L, id);
    return 2;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_clear_surface(lua_State *L) {
  int32_t color = (int32_t)lua_tonumber(L, -1);
  SGFXSurface *surface = __checkSGFXSurface(L, -2);
  if (sgfx_clear_surface(surface, color) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_dump_surface(lua_State *L) {
  const char *filename = lua_tostring(L, -1);
  SGFXSurface *surface = __checkSGFXSurface(L, -2);
  if (sgfx_dump_surface(surface, filename) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_draw_point(lua_State *L) {
  int py = (int)lua_tonumber(L, -1);
  int px = (int)lua_tonumber(L, -2);
  SGFXSurface *surface = __checkSGFXSurface(L, -3);
  if (sgfx_draw_point(surface, px, py) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_draw_rect(lua_State *L) {
  int y1 = (int)lua_tonumber(L, -1);
  int x1 = (int)lua_tonumber(L, -2);
  int y0 = (int)lua_tonumber(L, -3);
  int x0 = (int)lua_tonumber(L, -4);
  SGFXSurface *surface = __checkSGFXSurface(L, -5);
  if (sgfx_draw_rect(surface, x0, y0, x1, y1) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_flip(lua_State *L) {
  SGFXRect *rect = __checkSGFXRect(L, -1);
  SGFXSurface *surface = __checkSGFXSurface(L, -2);
  if (sgfx_flip(surface, rect) == SGFX_OK) {
    if (rect)
      free(rect);
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL) {
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
      return 2;
    }
    return 1;
  }
}

static int _lua_sgfx_destroy_surface(lua_State *L) {
  SGFXSurface *surface = __checkSGFXSurface(L, -1);
  sgfx_destroy_surface(surface);
  return 0;
}

static const struct luaL_Reg sgfx[] = {
    {"init", _lua_sgfx_init},
    {"close", _lua_sgfx_close},
    {"create_surface", _lua_sgfx_create_surface},
    {"set_description", _lua_sgfx_set_description},
    {"get_resolution", _lua_sgfx_get_resolution},
    {"get_surface_id", _lua_sgfx_surface_get_id},
    {"clear_surface", _lua_sgfx_clear_surface},
    {"dump_surface", _lua_sgfx_dump_surface},
    {"draw_point", _lua_sgfx_draw_point},
    {"draw_rect", _lua_sgfx_draw_rect},
    {"flip", _lua_sgfx_flip},
    {"destroy_surface", _lua_sgfx_destroy_surface},
    {NULL, NULL}};

int luaopen_sgfx(lua_State *L) {
  luaL_newmetatable(L, "SGFXSurface");
#if defined(LUA_5_2) || defined(LUA_5_3)
  luaL_newlib(L, sgfx);
#endif
#if defined(LUA_5_1)
  luaL_register(L, "sgfx", sgfx);
#endif
  return 1;
}
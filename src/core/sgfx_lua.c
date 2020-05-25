#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "sgfx.h"
#include "sgfx_log.h"
#include "sgfx_surface.h"
// https://gist.github.com/bloodstalker/91261e541666f16c3b8315d3ff1085d6

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

static const struct luaL_Reg sgfx[] = {
    {"init", _lua_sgfx_init},
    {"close", _lua_sgfx_close},
    {"create_surface", _lua_sgfx_create_surface},
    {"get_resolution", _lua_sgfx_get_resolution},
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
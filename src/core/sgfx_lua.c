#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "sgfx.h"
#include "sgfx_log.h"
#include "sgfx_surface.h"
// https://gist.github.com/bloodstalker/91261e541666f16c3b8315d3ff1085d6

static SGFXSurfaceDescription *__pop_sgfx_surface_description(lua_State *L,
                                                              int index) {
  SGFXSurfaceDescription *desc;
  desc = (SGFXSurfaceDescription *)luaL_checkudata(L, index,
                                                   "SGFXSurfaceDescription");
  if (!desc) {
    printf("Bad type error: SGFXSurfaceDescription struct expected\n");
  }

  return desc;
}

static SGFXSurface *__push_sgfx_surface(lua_State *L, SGFXSurface *surface) {
  if (!lua_checkstack(L, 1)) {
    printf("o woe is me. no more room in hell...I mean stack...\n");
    return NULL;
  }
  luaL_getmetatable(L, "SGFXSurface");
  lua_setmetatable(L, -2);
  lua_pushlightuserdata(L, surface);
  lua_pushvalue(L, -2);
  lua_settable(L, LUA_REGISTRYINDEX);
  return surface;
}

static int _lua_sgfx_init(lua_State *L) {
  if (sgfx_init(0, NULL) == SGFX_OK) {
    lua_pushboolean(L, true);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL)
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
    return 2;
  }
}

static int _lua_sgfx_close(lua_State *L) {
  sgfx_close();
  return 1;
}

static int _lua_sgfx_create_surface(lua_State *L) {
  SGFXSurface surface;
  SGFXSurfaceDescription *desc = __pop_sgfx_surface_description(L, -1);
  if (sgfx_create_surface(&surface, desc) == SGFX_OK) {
    __push_sgfx_surface(L, &surface);
    return 1;
  } else {
    lua_pushboolean(L, false);
    if (sgfx_get_message_error() != NULL)
      lua_pushlstring(L, sgfx_get_message_error(),
                      strlen(sgfx_get_message_error()));
    return 2;
  }
}

static const struct luaL_Reg sgfx[] = {
    {"init", _lua_sgfx_init},
    {"close", _lua_sgfx_close},
    {"create_surface", _lua_sgfx_create_surface},
    {NULL, NULL}};

int luaopen_sgfx(lua_State *L) {
#if defined(LUA_5_2) || defined(LUA_5_3)
  luaL_newlib(L, sgfx);
#endif
#if defined(LUA_5_1)
  luaL_register(L, "sgfx", sgfx);
#endif
  return 1;
}
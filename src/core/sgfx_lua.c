#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "sgfx.h"
#include "sgfx_log.h"

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

static const struct luaL_Reg sgfx[] = {
    {"init", _lua_sgfx_init}, {"close", _lua_sgfx_close}, {NULL, NULL}};

int luaopen_sgfx(lua_State *L) {
#if defined(LUA_5_2) || defined(LUA_5_3)
  luaL_newlib(L, sgfx);
#endif
#if defined(LUA_5_1)
  luaL_register(L, "sgfx", sgfx);
#endif
  return 1;
}
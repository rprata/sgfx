#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "ibutterfree.h"
#include "ibutterfree_log.h"

static int init(lua_State *L) 
{
	int argc = luaL_checkint(L, 1);
	if (ibutterfree_init(argc, NULL) == IBUTTERFREE_OK)
	{
	    lua_pushboolean(L, true);
	    return 1;
	}
	else
	{
	    lua_pushboolean(L, false);
	    if (ibutterfree_get_message_error() != NULL)
    		lua_pushlstring(L, ibutterfree_get_message_error(), strlen(ibutterfree_get_message_error()));
	    return 2;
	}
}

static const struct luaL_Reg ibutterfree [] = {
	{"init", init},
	{NULL, NULL}
};

int luaopen_ibutterfree (lua_State *L)
{
#ifdef LUA_5_2
	luaL_newlib(L, ibutterfree);
#endif
#ifdef LUA_5_1
	luaL_register(L, "ibutterfree", ibutterfree);
#endif
	return 1;
}
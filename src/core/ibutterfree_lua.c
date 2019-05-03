#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

static int ibutterfree_init(lua_State *L) 
{
	return 0;
}

static const struct luaL_Reg ibutterfree [] = {
	{"init", ibutterfree_init},
	{NULL, NULL}
};

int luaopen_ibutterfree (lua_State *L)
{
	luaL_register(L, "libibutterfree", ibutterfree);
	return 1;
}
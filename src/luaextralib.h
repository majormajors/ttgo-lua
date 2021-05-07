#pragma once

#include <lprefix.h>
#include <lua.h>

// EPD interface
#define LUA_EPDLIBNAME "epd"
LUAMOD_API int (luaopen_epd) (lua_State *L);

LUAMOD_API void (luaL_openextralibs) (lua_State *L);
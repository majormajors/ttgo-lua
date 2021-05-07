#include <lauxlib.h>
#include "luaextralib.h"

static const luaL_Reg extralibs[] = {
        {LUA_EPDLIBNAME, luaopen_epd},
        {NULL, NULL}
};

LUALIB_API void luaL_openextralibs(lua_State *L) {
    const luaL_Reg *lib;
    for (lib = extralibs; lib->func; lib++) {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1);  /* remove lib */
    }
}
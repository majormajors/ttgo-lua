#include <Arduino.h>
#include <SPIFFS.h>

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
    #include "luaextralib.h"
}

lua_State *L;

__unused void setup() {
    Serial.begin(115200);

    SPIFFS.begin();

    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_openextralibs(L);

    luaL_dofile(L, "/spiffs/test.lua");

    lua_close(L);
}

void loop() {
}
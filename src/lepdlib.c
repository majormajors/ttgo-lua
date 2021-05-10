#include <lprefix.h>
#include <lua.h>
#include <lauxlib.h>
#include <epd_driver.h>
#include <string.h>
#include <stdlib.h>
#include "firasans.h"

#ifdef BOARD_HAS_PSRAM
#include <esp32-hal.h>
#define CALLOC(n, size) (ps_calloc(n, size))
#else
#define CALLOC(n, size) (calloc(n, size))
#endif

#ifndef MIN
#define MIN(A,B) (A > B ? B : A)
#endif

#ifndef MAX
#define MAX(A,B) (A > B ? A : B)
#endif

const size_t EPD_AREA = EPD_HEIGHT * EPD_WIDTH;

GFXfont *defaultFont = (GFXfont *)&FiraSans;

uint8_t *lepd_framebuffer = NULL;

void lepd_framebuffer_init() {
    if (lepd_framebuffer != NULL) return;
    lepd_framebuffer = (uint8_t *) CALLOC(sizeof(uint8_t), EPD_AREA);
    memset(lepd_framebuffer, 0xFF, EPD_AREA);
}

uint8_t lepd_clamp_color(lua_Integer color) {
    return MIN(MAX(color, 0), 0xFF);
}

static int lepd_poweron(lua_State *L) {
    epd_poweron();
    return 0;
}

static int lepd_poweroff(lua_State *L) {
    epd_poweroff();
    return 0;
}

static int lepd_clear(lua_State *L) {
    epd_clear();
    memset(lepd_framebuffer, 0xFF, EPD_AREA);
    return 0;
}

static int lepd_getwidth(lua_State *L) {
    lua_pushinteger(L, EPD_WIDTH);
    return 1;
}

static int lepd_getheight(lua_State *L) {
    lua_pushinteger(L, EPD_HEIGHT);
    return 1;
}

static int lepd_write_string(lua_State *L) {
    const char *str = luaL_checkstring(L, 1);
    lua_Integer x = luaL_checkinteger(L, 2);
    lua_Integer y = luaL_checkinteger(L, 3);
    write_string(defaultFont, str, &x, &y, lepd_framebuffer);
    return 0;
}

static int lepd_draw_hline(lua_State *L) {
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_Integer y = luaL_checkinteger(L, 2);
    lua_Integer length = luaL_checkinteger(L, 3);
    uint8_t  color = lepd_clamp_color(luaL_checkinteger(L, 4));
    epd_draw_hline(x, y, length, color, lepd_framebuffer);
    return 0;
}

static int lepd_draw_vline(lua_State *L) {
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_Integer y = luaL_checkinteger(L, 2);
    lua_Integer length = luaL_checkinteger(L, 3);
    uint8_t  color = lepd_clamp_color(luaL_checkinteger(L, 4));
    epd_draw_vline(x, y, length, color, lepd_framebuffer);
    return 0;
}

static int lepd_draw_circle(lua_State *L) {
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_Integer y = luaL_checkinteger(L, 2);
    lua_Integer r = luaL_checkinteger(L, 3);
    uint8_t color = lepd_clamp_color(luaL_checkinteger(L, 4));
    epd_draw_circle(x, y, r, color, lepd_framebuffer);
    return 0;
}

static int lepd_fill_circle(lua_State *L) {
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_Integer y = luaL_checkinteger(L, 2);
    lua_Integer r = luaL_checkinteger(L, 3);
    uint8_t color = lepd_clamp_color(luaL_checkinteger(L, 4));
    epd_fill_circle(x, y, r, color, lepd_framebuffer);
    return 0;
}

static int lepd_draw_rect(lua_State *L) {
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_Integer y = luaL_checkinteger(L, 2);
    lua_Integer w = luaL_checkinteger(L, 3);
    lua_Integer h = luaL_checkinteger(L, 4);
    uint8_t color = lepd_clamp_color(luaL_checkinteger(L, 5));
    epd_draw_rect(x, y, w, h, color, lepd_framebuffer);
    return 0;
}

static int lepd_render(lua_State *L) {
    epd_draw_grayscale_image(epd_full_screen(), lepd_framebuffer);
    return 0;
}

static const luaL_Reg lepdlib[] = {
        { "power_on", lepd_poweron },
        { "power_off", lepd_poweroff },
        { "clear", lepd_clear },
        { "width", lepd_getwidth },
        { "height", lepd_getheight },
        { "write_string", lepd_write_string },
        { "draw_hline", lepd_draw_hline },
        { "draw_vline", lepd_draw_vline },
        { "draw_circle", lepd_draw_circle },
        { "fill_circle", lepd_fill_circle },
        { "draw_rect", lepd_draw_rect },
        { "render", lepd_render },
        { NULL, NULL }
};

LUAMOD_API int luaopen_epd(lua_State *L) {
    epd_init();
    lepd_framebuffer_init();
    luaL_newlib(L, lepdlib);
    return 1;
}

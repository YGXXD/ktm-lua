#pragma once

extern "C"
{
#include "../lua/lua.h"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
}

inline const char* luaL_typename_ext(lua_State* L, int idx)
{
    if (!lua_isuserdata(L, idx))
        return lua_typename(L, lua_type(L, idx));

    if (!lua_getmetatable(L, idx))
        return "userdata";

    lua_getfield(L, -1, "__name");
    const char* name = lua_tostring(L, -1);

    lua_pop(L, 2);
    return name ? name : "userdata";
}
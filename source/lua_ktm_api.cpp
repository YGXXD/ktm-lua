//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "lua_ktm_api.h"

const char* luaL_typename_ex(lua_State* L, int idx)
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
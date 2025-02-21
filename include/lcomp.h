//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "lua_ktm_api.h"

void register_lcomp(lua_State* L);

template <typename T>
struct lcomp
{
    static int create(lua_State* L);

    static int tostring(lua_State* L);

    static int index(lua_State* L);

    static int newindex(lua_State* L);

    static int add(lua_State* L);

    static int sub(lua_State* L);

    static int mul(lua_State* L);

    static int div(lua_State* L);

    static int eq(lua_State* L);

    static int neq(lua_State* L);

    static int lt(lua_State* L);

    static int le(lua_State* L);

    static int gt(lua_State* L);

    static int ge(lua_State* L);

    static int gc(lua_State* L);

    static void register_type(lua_State* L);
};
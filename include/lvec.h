//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "lua_ktm_api.h"

template <size_t N>
void register_lvec(lua_State* L);

extern template void register_lvec<2>(lua_State* L);
extern template void register_lvec<3>(lua_State* L);
extern template void register_lvec<4>(lua_State* L);

template <size_t N>
struct lvec
{
    template <typename T>
    static int create(lua_State* L);

    template <typename T>
    static int tostring(lua_State* L);

    template <typename T>
    static int index(lua_State* L);

    template <typename T>
    static int newindex(lua_State* L);

    template <typename T>
    static int add(lua_State* L);

    template <typename T>
    static int sub(lua_State* L);

    template <typename T>
    static int mul(lua_State* L);

    template <typename T>
    static int div(lua_State* L);

    template <typename T>
    static int eq(lua_State* L);

    template <typename T>
    static int neq(lua_State* L);

    template <typename T>
    static int lt(lua_State* L);

    template <typename T>
    static int le(lua_State* L);

    template <typename T>
    static int gt(lua_State* L);

    template <typename T>
    static int ge(lua_State* L);

    template <typename T>
    static int gc(lua_State* L);
    
    template <typename T>
    static void register_type(lua_State* L);
};
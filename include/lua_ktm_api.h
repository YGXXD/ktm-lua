//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}
#include "ktm/ktm/ktm.h"

const char* luaL_typename_ex(lua_State* L, int idx);

template <typename T, typename... Args>
inline T* lua_newuserdata_ex(lua_State* L, Args&&... args);

template <typename T>
inline bool luaL_is_ktm_type(lua_State* L, int idx);

template <typename T>
inline T* luaL_check_ktm_type(lua_State* L, int idx);

template <typename T>
struct lua_ktm_typename;

template <typename T>
inline constexpr const char* lua_ktm_typename_v = lua_ktm_typename<T>::value.data();

#include "lua_ktm_api.inl"
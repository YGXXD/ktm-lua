#pragma once

#include "lktm_api.h"

template <typename T>
int fun_create_lua_quat(lua_State* L);

template <typename T>
int fun_lua_quat_tostring(lua_State* L);

template <typename T>
int fun_lua_quat_index(lua_State* L);

template <typename T>
int fun_lua_quat_newindex(lua_State* L);

template <typename T>
int fun_lua_quat_add(lua_State* L);

template <typename T>
int fun_lua_quat_sub(lua_State* L);

template <typename T>
int fun_lua_quat_mul(lua_State* L);

template <typename T>
int fun_lua_quat_div(lua_State* L);

template <typename T>
int fun_lua_quat_eq(lua_State* L);

template <typename T>
int fun_lua_quat_neq(lua_State* L);

template <typename T>
int fun_lua_quat_lt(lua_State* L);

template <typename T>
int fun_lua_quat_le(lua_State* L);

template <typename T>
int fun_lua_quat_gt(lua_State* L);

template <typename T>
int fun_lua_quat_ge(lua_State* L);

template <typename T>
inline void register_lua_quat(lua_State* L);

#include "ltype_quat.inl"
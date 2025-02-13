#pragma once

#include "lktm_api.h"

template <size_t N, typename T>
int fun_create_lua_vec(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_tostring(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_index(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_newindex(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_add(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_sub(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_mul(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_div(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_eq(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_neq(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_lt(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_le(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_gt(lua_State* L);

template <size_t N, typename T>
int fun_lua_vec_ge(lua_State* L);

template <size_t N, typename T>
inline void register_lua_vec(lua_State* L);

#include "ltype_vec.inl"
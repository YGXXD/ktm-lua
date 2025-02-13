#pragma once

#include "lktm_api.h"

template <typename T>
int fun_create_lua_comp(lua_State* L);

template <typename T>
int fun_lua_comp_tostring(lua_State* L);

template <typename T>
int fun_lua_comp_index(lua_State* L);

template <typename T>
int fun_lua_comp_newindex(lua_State* L);

template <typename T>
int fun_lua_comp_add(lua_State* L);

template <typename T>
int fun_lua_comp_sub(lua_State* L);

template <typename T>
int fun_lua_comp_mul(lua_State* L);

template <typename T>
int fun_lua_comp_div(lua_State* L);

template <typename T>
int fun_lua_comp_eq(lua_State* L);

template <typename T>
int fun_lua_comp_neq(lua_State* L);

template <typename T>
int fun_lua_comp_lt(lua_State* L);

template <typename T>
int fun_lua_comp_le(lua_State* L);

template <typename T>
int fun_lua_comp_gt(lua_State* L);

template <typename T>
int fun_lua_comp_ge(lua_State* L);

template <typename T>
inline void register_lua_comp(lua_State* L);

#include "ltype_comp.inl"
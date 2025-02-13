#pragma once

#include "lktm_api.h"

template <size_t Row, size_t Col, typename T>
int fun_create_lua_mat(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_tostring(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_index(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_newindex(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_add(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_sub(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_mul(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_div(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_eq(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_neq(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_lt(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_le(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_gt(lua_State* L);

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_ge(lua_State* L);

template <size_t Row, size_t Col, typename T>
inline void register_lua_mat(lua_State* L);

#include "ltype_mat.inl"
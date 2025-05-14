#pragma once

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include <string_view>
#include "ntr/inc/nephren.hpp"

void lua_pushnobject(lua_State* L, ntr::nobject& object);

ntr::nobject lua_checknobject(lua_State* L, int index, const ntr::ntype* type);

int lua_ntr_new(lua_State* L, const ntr::nclass* type);

int lua_ntr_delete(lua_State* L, const ntr::nclass* type);

int lua_ntr_call(lua_State* L, const ntr::nclass* type, const std::string_view& function_name);

void lua_ntr_regist_function(lua_State* L, const ntr::nclass* type);

void lua_ntr_regist_property(lua_State* L, const ntr::nclass* type);

void lua_ntr_regist_metatable(lua_State* L, const ntr::nclass* type);

void lua_ntr_regist_type(lua_State* L, const std::string_view& type_name);
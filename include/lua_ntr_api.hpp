#pragma once

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include <string_view>

int lua_ntr_new(lua_State* L, const std::string_view& type_name);

int lua_ntr_delete(lua_State* L, const std::string_view& type_name);

int lua_ntr_call(lua_State* L, const std::string_view& type_name, const std::string_view& function_name);

void lua_ntr_register(lua_State* L, const std::string_view& type_name);
#pragma once

#include <string_view>
#include "ntr/inc/nephren.hpp"

struct lua_State;

void* lua_ntr_new_data(lua_State* L, const ntr::nclass* type);
void* lua_ntr_check_data(lua_State* L, int index, const ntr::nclass* type);
void lua_ntr_push_object(lua_State* L, ntr::nobject& object);
ntr::nobject lua_ntr_check_object(lua_State* L, int index, const ntr::ntype* type);
int lua_ntr_new(lua_State* L, const ntr::nclass* type);
int lua_ntr_delete(lua_State* L, const ntr::nclass* type);
int lua_ntr_call(lua_State* L, const ntr::nclass* type, const std::string_view& function_name);
void lua_ntr_set_function(lua_State* L, const ntr::nclass* type);
void lua_ntr_set_property(lua_State* L, const ntr::nclass* type);
void lua_ntr_set_typelife(lua_State* L, const ntr::nclass* type);
void lua_ntr_new_type(lua_State* L, const std::string_view& type_name);
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include <iostream>
#include "lntr_binding.hpp"
#include "lvec2.hpp"
#include "lvec3.hpp"
#include "lvec4.hpp"

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

void regist_lvec2_lua(lua_State* L)
{
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<unsigned int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<float>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<double>>()->name());
}

void regist_lvec3_lua(lua_State* L)
{
    lua_ntr_regist_type(L, ntr::nephren::get<lvec3<int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec3<unsigned int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec3<float>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec3<double>>()->name());
}

void regist_lvec4_lua(lua_State* L)
{
    lua_ntr_regist_type(L, ntr::nephren::get<lvec4<int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec4<unsigned int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec4<float>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec4<double>>()->name());
}

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    regist_lvec2_lua(L);
    regist_lvec3_lua(L);
    regist_lvec4_lua(L);

    if (argc > 1)
    {
        if (luaL_dofile(L, argv[1]) != LUA_OK)
        {
            std::cerr << "Lua Runtime Error: " << lua_tostring(L, -1) << std::endl;
        }
    }

    lua_close(L);

    return 0;
}
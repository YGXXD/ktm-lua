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
#include "lquat.hpp"
#include "lcomp.hpp"
#include "lmat2x2.hpp"
#include "lmat2x3.hpp"
#include "lmat2x4.hpp"
#include "lmat3x2.hpp"
#include "lmat3x3.hpp"
#include "lmat3x4.hpp"
#include "lmat4x2.hpp"
#include "lmat4x3.hpp"
#include "lmat4x4.hpp"

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

void lua_regist_lvecn(lua_State* L)
{
    if (regist_lvec2::flag)
    {
        lua_ntr_regist_type(L, regist_lvec2::iname);
        lua_ntr_regist_type(L, regist_lvec2::uname);
        lua_ntr_regist_type(L, regist_lvec2::fname);
        lua_ntr_regist_type(L, regist_lvec2::dname);
    }
    if (regist_lvec3::flag)
    {
        lua_ntr_regist_type(L, regist_lvec3::iname);
        lua_ntr_regist_type(L, regist_lvec3::uname);
        lua_ntr_regist_type(L, regist_lvec3::fname);
        lua_ntr_regist_type(L, regist_lvec3::dname);
    }
    if (regist_lvec4::flag)
    {
        lua_ntr_regist_type(L, regist_lvec4::iname);
        lua_ntr_regist_type(L, regist_lvec4::uname);
        lua_ntr_regist_type(L, regist_lvec4::fname);
        lua_ntr_regist_type(L, regist_lvec4::dname);
    }
}

void lua_regist_lmatnxm(lua_State* L)
{
    if (regist_lmat2x2::flag)
    {
        lua_ntr_regist_type(L, regist_lmat2x2::iname);
        lua_ntr_regist_type(L, regist_lmat2x2::uname);
        lua_ntr_regist_type(L, regist_lmat2x2::fname);
        lua_ntr_regist_type(L, regist_lmat2x2::dname);
    }
    if (regist_lmat2x3::flag)
    {
        lua_ntr_regist_type(L, regist_lmat2x3::iname);
        lua_ntr_regist_type(L, regist_lmat2x3::uname);
        lua_ntr_regist_type(L, regist_lmat2x3::fname);
        lua_ntr_regist_type(L, regist_lmat2x3::dname);
    }
    if (regist_lmat2x4::flag)
    {
        lua_ntr_regist_type(L, regist_lmat2x4::iname);
        lua_ntr_regist_type(L, regist_lmat2x4::uname);
        lua_ntr_regist_type(L, regist_lmat2x4::fname);
        lua_ntr_regist_type(L, regist_lmat2x4::dname);
    }
    if (regist_lmat3x2::flag)
    {
        lua_ntr_regist_type(L, regist_lmat3x2::iname);
        lua_ntr_regist_type(L, regist_lmat3x2::uname);
        lua_ntr_regist_type(L, regist_lmat3x2::fname);
        lua_ntr_regist_type(L, regist_lmat3x2::dname);
    }
    if (regist_lmat3x3::flag)
    {
        lua_ntr_regist_type(L, regist_lmat3x3::iname);
        lua_ntr_regist_type(L, regist_lmat3x3::uname);
        lua_ntr_regist_type(L, regist_lmat3x3::fname);
        lua_ntr_regist_type(L, regist_lmat3x3::dname);
    }
    if (regist_lmat3x4::flag)
    {
        lua_ntr_regist_type(L, regist_lmat3x4::iname);
        lua_ntr_regist_type(L, regist_lmat3x4::uname);
        lua_ntr_regist_type(L, regist_lmat3x4::fname);
        lua_ntr_regist_type(L, regist_lmat3x4::dname);
    }
    if (regist_lmat4x4::flag)
    {
        lua_ntr_regist_type(L, regist_lmat4x4::iname);
        lua_ntr_regist_type(L, regist_lmat4x4::uname);
        lua_ntr_regist_type(L, regist_lmat4x4::fname);
        lua_ntr_regist_type(L, regist_lmat4x4::dname);
    }
    if (regist_lmat4x2::flag)
    {
        lua_ntr_regist_type(L, regist_lmat4x2::iname);
        lua_ntr_regist_type(L, regist_lmat4x2::uname);
        lua_ntr_regist_type(L, regist_lmat4x2::fname);
        lua_ntr_regist_type(L, regist_lmat4x2::dname);
    }
    if (regist_lmat4x3::flag)
    {
        lua_ntr_regist_type(L, regist_lmat4x3::iname);
        lua_ntr_regist_type(L, regist_lmat4x3::uname);
        lua_ntr_regist_type(L, regist_lmat4x3::fname);
        lua_ntr_regist_type(L, regist_lmat4x3::dname);
    }
    if (regist_lmat4x4::flag)
    {
        lua_ntr_regist_type(L, regist_lmat4x4::iname);
        lua_ntr_regist_type(L, regist_lmat4x4::uname);
        lua_ntr_regist_type(L, regist_lmat4x4::fname);
        lua_ntr_regist_type(L, regist_lmat4x4::dname);
    }
}

void lua_regist_lquat(lua_State* L)
{
    if (regist_lquat::flag)
    {
        lua_ntr_regist_type(L, regist_lquat::fname);
        lua_ntr_regist_type(L, regist_lquat::dname);
    }
}

void lua_regist_lcomp(lua_State* L)
{
    if (regist_lcomp::flag)
    {
        lua_ntr_regist_type(L, regist_lcomp::fname);
        lua_ntr_regist_type(L, regist_lcomp::dname);
    }
}

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_regist_lvecn(L);
    lua_regist_lmatnxm(L);
    lua_regist_lquat(L);
    lua_regist_lcomp(L);

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
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

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

std::vector<std::string_view> registed_ntr_type_names()
{
    std::vector<std::string_view> type_names;
    if (regist_lvec2::flag)
    {
        type_names.push_back(regist_lvec2::iname);
        type_names.push_back(regist_lvec2::uname);
        type_names.push_back(regist_lvec2::fname);
        type_names.push_back(regist_lvec2::dname);
    }
    if (regist_lvec3::flag)
    {
        type_names.push_back(regist_lvec3::iname);
        type_names.push_back(regist_lvec3::uname);
        type_names.push_back(regist_lvec3::fname);
        type_names.push_back(regist_lvec3::dname);
    }
    if (regist_lvec4::flag)
    {
        type_names.push_back(regist_lvec4::iname);
        type_names.push_back(regist_lvec4::uname);
        type_names.push_back(regist_lvec4::fname);
        type_names.push_back(regist_lvec4::dname);
    }
    if (regist_lmat2x2::flag)
    {
        type_names.push_back(regist_lmat2x2::iname);
        type_names.push_back(regist_lmat2x2::uname);
        type_names.push_back(regist_lmat2x2::fname);
        type_names.push_back(regist_lmat2x2::dname);
    }
    if (regist_lmat2x3::flag)
    {
        type_names.push_back(regist_lmat2x3::iname);
        type_names.push_back(regist_lmat2x3::uname);
        type_names.push_back(regist_lmat2x3::fname);
        type_names.push_back(regist_lmat2x3::dname);
    }
    if (regist_lmat2x4::flag)
    {
        type_names.push_back(regist_lmat2x4::iname);
        type_names.push_back(regist_lmat2x4::uname);
        type_names.push_back(regist_lmat2x4::fname);
        type_names.push_back(regist_lmat2x4::dname);
    }
    if (regist_lmat3x2::flag)
    {
        type_names.push_back(regist_lmat3x2::iname);
        type_names.push_back(regist_lmat3x2::uname);
        type_names.push_back(regist_lmat3x2::fname);
        type_names.push_back(regist_lmat3x2::dname);
    }
    if (regist_lmat3x3::flag)
    {
        type_names.push_back(regist_lmat3x3::iname);
        type_names.push_back(regist_lmat3x3::uname);
        type_names.push_back(regist_lmat3x3::fname);
        type_names.push_back(regist_lmat3x3::dname);
    }
    if (regist_lmat3x4::flag)
    {
        type_names.push_back(regist_lmat3x4::iname);
        type_names.push_back(regist_lmat3x4::uname);
        type_names.push_back(regist_lmat3x4::fname);
        type_names.push_back(regist_lmat3x4::dname);
    }
    if (regist_lmat4x2::flag)
    {
        type_names.push_back(regist_lmat4x2::iname);
        type_names.push_back(regist_lmat4x2::uname);
        type_names.push_back(regist_lmat4x2::fname);
        type_names.push_back(regist_lmat4x2::dname);
    }
    if (regist_lmat4x3::flag)
    {
        type_names.push_back(regist_lmat4x3::iname);
        type_names.push_back(regist_lmat4x3::uname);
        type_names.push_back(regist_lmat4x3::fname);
        type_names.push_back(regist_lmat4x3::dname);
    }
    if (regist_lmat4x4::flag)
    {
        type_names.push_back(regist_lmat4x4::iname);
        type_names.push_back(regist_lmat4x4::uname);
        type_names.push_back(regist_lmat4x4::fname);
        type_names.push_back(regist_lmat4x4::dname);
    }
    if (regist_lcomp::flag)
    {
        type_names.push_back(regist_lcomp::fname);
        type_names.push_back(regist_lcomp::dname);
    }
    if (regist_lquat::flag)
    {
        type_names.push_back(regist_lquat::fname);
        type_names.push_back(regist_lquat::dname);
    }
    return type_names;
}

extern "C"
{
#define LUA_LIB

#include <lua.h>
#include <lauxlib.h>
#include "lktmlib.h"

    LUAMOD_API int luaopen_ktm(lua_State* L)
    {
        luaL_checkversion(L);
        lua_newtable(L);
        std::vector<std::string_view> type_names = registed_ntr_type_names();
        for (const auto& type_name : type_names)
        {
            lua_ntr_new_type(L, type_name);
            lua_setfield(L, -2, type_name.data());
        }
        return 1;
    }
}
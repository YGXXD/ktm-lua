#pragma once

#include <sstream>
#include "ltype_comp.h"

template <typename T>
int fun_create_lua_comp(lua_State* L)
{
    constexpr auto comp_name = lua_ktm_typename_v<ktm::comp<T>>;
    int arg_count = lua_gettop(L) - 1;

    switch (arg_count)
    {
    case 0:
    {
        lua_newuserdata_ex<ktm::comp<T>>(L);
    }
    break;
    case 1:
    {
        lua_newuserdata_ex<ktm::comp<T>>(L, *luaL_check_ktm_type<ktm::vec<2, T>>(L, 2));
    }
    break;
    case 2:
    {
        lua_newuserdata_ex<ktm::comp<T>>(L, static_cast<T>(luaL_checknumber(L, 2)),
                                         static_cast<T>(luaL_checknumber(L, 3)));
    }
    break;
    default:
    {
        luaL_error(L, "invalid number of arguments on create %s: %d", comp_name, arg_count);
    }
    }

    luaL_getmetatable(L, comp_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <typename T>
int fun_lua_comp_tostring(lua_State* L)
{
    ktm::comp<T>* c = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
    std::stringstream ss;
    ss << *c;
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

template <typename T>
int fun_lua_comp_index(lua_State* L)
{
    ktm::comp<T>* c = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > 2)
        {
            luaL_error(L, "index out of range [1,2]");
        }
        lua_pushnumber(L, static_cast<lua_Number>((*c)[index - 1]));
    }
    else
    {
        const std::string_view key = lua_tostring(L, 2);

        int index = -1;
        if (key.size() == 1)
        {
            switch (key[0])
            {
            case 'i':
                index = 0;
                break;
            case 'r':
                index = 1;
                break;
            default:
                break;
            }
        }

        if (index != -1 && index < 2)
        {
            lua_pushnumber(L, static_cast<lua_Number>((*c)[index]));
        }
        else
        {
            lua_getmetatable(L, 1);
            lua_pushvalue(L, 2);
            lua_rawget(L, -2);
        }
    }

    return 1;
}

template <typename T>
int fun_lua_comp_newindex(lua_State* L)
{
    ktm::comp<T>* c = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
    T value = static_cast<T>(luaL_checknumber(L, 3));
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > 2)
        {
            luaL_error(L, "index out of range [1,2]");
        }
        (*c)[index - 1] = value;
    }
    else
    {
        const std::string_view key = lua_tostring(L, 2);

        int index = -1;
        if (key.size() == 1)
        {
            switch (key[0])
            {
            case 'i':
                index = 0;
                break;
            case 'r':
                index = 1;
                break;
            default:
                break;
            }
        }

        if (index != -1 && index < 2)
        {
            (*c)[index] = value;
        }
        else
        {
            luaL_error(L, "invalid property name: %s", key);
        }
    }

    return 0;
}

template <typename T>
int fun_lua_comp_add(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        ktm::comp<T> result = (*c1) + (*c2);
        lua_newuserdata_ex<ktm::comp<T>>(L, result);

        constexpr auto comp_name = lua_ktm_typename_v<ktm::comp<T>>;
        luaL_getmetatable(L, comp_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s + %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <typename T>
int fun_lua_comp_sub(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        ktm::comp<T> result = (*c1) - (*c2);
        lua_newuserdata_ex<ktm::comp<T>>(L, result);

        constexpr auto comp_name = lua_ktm_typename_v<ktm::comp<T>>;
        luaL_getmetatable(L, comp_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s - %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <typename T>
int fun_lua_comp_mul(lua_State* L)
{
    ktm::comp<T> result;
    if (lua_isnumber(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        T scalar = static_cast<T>(luaL_checknumber(L, 1));
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        result = scalar * (*c2);
    }
    else if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        result = (*c1) * scalar;
    }
    else if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        result = (*c1) * (*c2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s * %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_newuserdata_ex<ktm::comp<T>>(L, result);

    constexpr auto comp_name = lua_ktm_typename_v<ktm::comp<T>>;
    luaL_getmetatable(L, comp_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <typename T>
int fun_lua_comp_div(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        ktm::comp<T> result = (*c1) / scalar;
        lua_newuserdata_ex<ktm::comp<T>>(L, result);

        constexpr auto comp_name = lua_ktm_typename_v<ktm::comp<T>>;
        luaL_getmetatable(L, comp_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s / %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <typename T>
int fun_lua_comp_eq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        lua_pushboolean(L, *c1 == *c2);
    }
    else
    {
        lua_pushboolean(L, false);
    }

    return 1;
}

template <typename T>
int fun_lua_comp_neq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        lua_pushboolean(L, *c1 != *c2);
    }
    else
    {
        lua_pushboolean(L, true);
    }

    return 1;
}

template <typename T>
int fun_lua_comp_lt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        lua_pushboolean(L, *c1 < *c2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s < %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
int fun_lua_comp_le(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        lua_pushboolean(L, *c1 <= *c2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s <= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
int fun_lua_comp_gt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        lua_pushboolean(L, *c1 > *c2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s > %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
int fun_lua_comp_ge(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::comp<T>>(L, 1) && luaL_is_ktm_type<ktm::comp<T>>(L, 2))
    {
        ktm::comp<T>* c1 = luaL_check_ktm_type<ktm::comp<T>>(L, 1);
        ktm::comp<T>* c2 = luaL_check_ktm_type<ktm::comp<T>>(L, 2);
        lua_pushboolean(L, *c1 >= *c2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s >= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
inline void register_lua_comp(lua_State* L)
{
    constexpr auto comp_name = lua_ktm_typename_v<ktm::comp<T>>;
    luaL_newmetatable(L, comp_name);

    constexpr const luaL_Reg comp_metamethods[] = { { "__tostring", fun_lua_comp_tostring<T> },
                                                    { "__index", fun_lua_comp_index<T> },
                                                    { "__newindex", fun_lua_comp_newindex<T> },
                                                    { "__add", fun_lua_comp_add<T> },
                                                    { "__sub", fun_lua_comp_sub<T> },
                                                    { "__mul", fun_lua_comp_mul<T> },
                                                    { "__div", fun_lua_comp_div<T> },
                                                    { "__eq", fun_lua_comp_eq<T> },
                                                    { "__neq", fun_lua_comp_neq<T> },
                                                    { "__lt", fun_lua_comp_lt<T> },
                                                    { "__le", fun_lua_comp_le<T> },
                                                    { "__gt", fun_lua_comp_gt<T> },
                                                    { "__ge", fun_lua_comp_ge<T> },
                                                    { nullptr, nullptr } };
    luaL_setfuncs(L, comp_metamethods, 0);

    lua_newtable(L);

    constexpr auto fun_create_lua_comp_wrapper = fun_create_lua_comp<T>;
    lua_pushcfunction(L, fun_create_lua_comp_wrapper);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);

    lua_setglobal(L, comp_name);
}
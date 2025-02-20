//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include <sstream>
#include "lquat.h"

void register_lquat(lua_State* L)
{
    lquat<float>::register_type(L);
    lquat<double>::register_type(L);
}

template <typename T>
int lquat<T>::create(lua_State* L)
{
    constexpr auto quat_name = lua_ktm_typename_v<ktm::quat<T>>;
    int arg_count = lua_gettop(L) - 1;

    switch (arg_count)
    {
    case 0:
    {
        lua_newuserdata_ex<ktm::quat<T>>(L);
    }
    break;
    case 1:
    {
        lua_newuserdata_ex<ktm::quat<T>>(L, *luaL_check_ktm_type<ktm::vec<4, T>>(L, 2));
    }
    break;
    case 4:
    {
        lua_newuserdata_ex<ktm::quat<T>>(L, static_cast<T>(luaL_checknumber(L, 2)),
                                         static_cast<T>(luaL_checknumber(L, 3)), static_cast<T>(luaL_checknumber(L, 4)),
                                         static_cast<T>(luaL_checknumber(L, 5)));
    }
    break;
    default:
    {
        luaL_error(L, "invalid number of arguments on create %s: %d", quat_name, arg_count);
    }
    }

    luaL_getmetatable(L, quat_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <typename T>
int lquat<T>::tostring(lua_State* L)
{
    ktm::quat<T>* q = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
    std::stringstream ss;
    ss << *q;
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

template <typename T>
int lquat<T>::index(lua_State* L)
{
    ktm::quat<T>* q = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > 4)
        {
            luaL_error(L, "index out of range [1,4]");
        }
        lua_pushnumber(L, static_cast<lua_Number>((*q)[index - 1]));
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
            case 'j':
                index = 1;
                break;
            case 'k':
                index = 2;
                break;
            case 'r':
                index = 3;
                break;
            default:
                break;
            }
        }

        if (index != -1 && index < 4)
        {
            lua_pushnumber(L, static_cast<lua_Number>((*q)[index]));
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
int lquat<T>::newindex(lua_State* L)
{
    ktm::quat<T>* q = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
    T value = static_cast<T>(luaL_checknumber(L, 3));
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > 4)
        {
            luaL_error(L, "index out of range [1,4]");
        }
        (*q)[index - 1] = value;
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
            case 'j':
                index = 1;
                break;
            case 'k':
                index = 2;
                break;
            case 'r':
                index = 3;
                break;
            default:
                break;
            }
        }

        if (index != -1 && index < 4)
        {
            (*q)[index] = value;
        }
        else
        {
            luaL_error(L, "invalid property name: %s", key);
        }
    }

    return 0;
}

template <typename T>
int lquat<T>::add(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        ktm::quat<T> result = (*q1) + (*q2);
        lua_newuserdata_ex<ktm::quat<T>>(L, result);

        constexpr auto quat_name = lua_ktm_typename_v<ktm::quat<T>>;
        luaL_getmetatable(L, quat_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s + %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <typename T>
int lquat<T>::sub(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        ktm::quat<T> result = (*q1) - (*q2);
        lua_newuserdata_ex<ktm::quat<T>>(L, result);

        constexpr auto quat_name = lua_ktm_typename_v<ktm::quat<T>>;
        luaL_getmetatable(L, quat_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s - %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <typename T>
int lquat<T>::mul(lua_State* L)
{
    ktm::quat<T> result;
    if (lua_isnumber(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        T scalar = static_cast<T>(luaL_checknumber(L, 1));
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        result = scalar * (*q2);
    }
    else if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        result = (*q1) * scalar;
    }
    else if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        result = (*q1) * (*q2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s * %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_newuserdata_ex<ktm::quat<T>>(L, result);

    constexpr auto quat_name = lua_ktm_typename_v<ktm::quat<T>>;
    luaL_getmetatable(L, quat_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <typename T>
int lquat<T>::div(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        ktm::quat<T> result = (*q1) / scalar;
        lua_newuserdata_ex<ktm::quat<T>>(L, result);

        constexpr auto quat_name = lua_ktm_typename_v<ktm::quat<T>>;
        luaL_getmetatable(L, quat_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s / %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <typename T>
int lquat<T>::eq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        lua_pushboolean(L, *q1 == *q2);
    }
    else
    {
        lua_pushboolean(L, false);
    }

    return 1;
}

template <typename T>
int lquat<T>::neq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        lua_pushboolean(L, *q1 != *q2);
    }
    else
    {
        lua_pushboolean(L, true);
    }

    return 1;
}

template <typename T>
int lquat<T>::lt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        lua_pushboolean(L, *q1 < *q2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s < %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
int lquat<T>::le(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        lua_pushboolean(L, *q1 <= *q2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s <= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
int lquat<T>::gt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        lua_pushboolean(L, *q1 > *q2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s > %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
int lquat<T>::ge(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::quat<T>>(L, 1) && luaL_is_ktm_type<ktm::quat<T>>(L, 2))
    {
        ktm::quat<T>* q1 = luaL_check_ktm_type<ktm::quat<T>>(L, 1);
        ktm::quat<T>* q2 = luaL_check_ktm_type<ktm::quat<T>>(L, 2);
        lua_pushboolean(L, *q1 >= *q2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s >= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <typename T>
void lquat<T>::register_type(lua_State* L)
{
    constexpr auto quat_name = lua_ktm_typename_v<ktm::quat<T>>;
    luaL_newmetatable(L, quat_name);

    constexpr const luaL_Reg quat_metamethods[] = { { "__tostring", lquat<T>::tostring },
                                                    { "__index", lquat<T>::index },
                                                    { "__newindex", lquat<T>::newindex },
                                                    { "__add", lquat<T>::add },
                                                    { "__sub", lquat<T>::sub },
                                                    { "__mul", lquat<T>::mul },
                                                    { "__div", lquat<T>::div },
                                                    { "__eq", lquat<T>::eq },
                                                    { "__neq", lquat<T>::neq },
                                                    { "__lt", lquat<T>::lt },
                                                    { "__le", lquat<T>::le },
                                                    { "__gt", lquat<T>::gt },
                                                    { "__ge", lquat<T>::ge },
                                                    { nullptr, nullptr } };
    luaL_setfuncs(L, quat_metamethods, 0);

    lua_newtable(L);

    constexpr auto fun_create_lua_quat_wrapper = lquat<T>::create;
    lua_pushcfunction(L, fun_create_lua_quat_wrapper);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);

    lua_setglobal(L, quat_name);
}
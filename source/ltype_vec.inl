#pragma once

#include <sstream>
#include "ltype_vec.h"

template <size_t N, typename T>
int fun_create_lua_vec(lua_State* L)
{
    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    int arg_count = lua_gettop(L) - 1;

    switch (arg_count)
    {
    case 0:
    {
        lua_newuserdata_ex<ktm::vec<N, T>>(L);
    }
    break;
    case 1:
    {
        lua_newuserdata_ex<ktm::vec<N, T>>(L, static_cast<T>(luaL_checknumber(L, 2)));
    }
    break;
    case N:
    {
        ktm::vec<N, T> value;
        for (int i = 0; i < N; ++i)
            value[i] = static_cast<T>(luaL_checknumber(L, i + 2));
        lua_newuserdata_ex<ktm::vec<N, T>>(L, value);
    }
    break;
    default:
    {
        luaL_error(L, "invalid number of arguments on create %s: %d", vec_name, arg_count);
    }
    break;
    }

    luaL_getmetatable(L, vec_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_tostring(lua_State* L)
{
    ktm::vec<N, T>* v = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
    std::stringstream ss;
    ss << *v;
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_index(lua_State* L)
{
    ktm::vec<N, T>* v = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > N)
        {
            luaL_error(L, "index out of range [1,%d]", N);
        }
        if constexpr (std::is_floating_point_v<T>)
            lua_pushnumber(L, static_cast<lua_Number>((*v)[index - 1]));
        else
            lua_pushinteger(L, static_cast<lua_Integer>((*v)[index - 1]));
    }
    else
    {
        const std::string_view key = lua_tostring(L, 2);

        int index = -1;
        if (key.size() == 1)
        {
            switch (key[0])
            {
            case 'x':
                index = 0;
                break;
            case 'y':
                index = 1;
                break;
            case 'z':
                index = 2;
                break;
            case 'w':
                index = 3;
                break;
            default:
                break;
            }
        }

        if (index != -1 && index < N)
        {
            if constexpr (std::is_floating_point_v<T>)
                lua_pushnumber(L, static_cast<lua_Number>((*v)[index]));
            else
                lua_pushinteger(L, static_cast<lua_Integer>((*v)[index]));
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

template <size_t N, typename T>
int fun_lua_vec_newindex(lua_State* L)
{
    ktm::vec<N, T>* v = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
    T value = static_cast<T>(luaL_checknumber(L, 3));
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > N)
        {
            luaL_error(L, "index out of range [1,%d]", N);
        }
        (*v)[index - 1] = value;
    }
    else
    {
        const std::string_view key = lua_tostring(L, 2);

        int index = -1;
        if (key.size() == 1)
        {
            switch (key[0])
            {
            case 'x':
                index = 0;
                break;
            case 'y':
                index = 1;
                break;
            case 'z':
                index = 2;
                break;
            case 'w':
                index = 3;
                break;
            default:
                break;
            }
        }

        if (index != -1 && index < N)
        {
            (*v)[index] = value;
        }
        else
        {
            luaL_error(L, "invalid property name: %s", key);
        }
    }

    return 0;
}

template <size_t N, typename T>
int fun_lua_vec_add(lua_State* L)
{
    ktm::vec<N, T> result;
    if (lua_isnumber(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        T scalar = static_cast<T>(luaL_checknumber(L, 1));
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        result = scalar + (*v2);
    }
    else if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        result = (*v1) + scalar;
    }
    else if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        result = (*v1) + (*v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s + %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_newuserdata_ex<ktm::vec<N, T>>(L, result);

    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    luaL_getmetatable(L, vec_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_sub(lua_State* L)
{
    ktm::vec<N, T> result;
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        result = (*v1) - scalar;
    }
    else if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        result = (*v1) - (*v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s - %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_newuserdata_ex<ktm::vec<N, T>>(L, result);

    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    luaL_getmetatable(L, vec_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_mul(lua_State* L)
{
    ktm::vec<N, T> result;
    if (lua_isnumber(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        T scalar = static_cast<T>(luaL_checknumber(L, 1));
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        result = scalar * (*v2);
    }
    else if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        result = (*v1) * scalar;
    }
    else if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        result = (*v1) * (*v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s * %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_newuserdata_ex<ktm::vec<N, T>>(L, result);

    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    luaL_getmetatable(L, vec_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_div(lua_State* L)
{
    ktm::vec<N, T> result;
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));
        result = (*v1) / scalar;
    }
    else if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        result = (*v1) / (*v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s / %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_newuserdata_ex<ktm::vec<N, T>>(L, result);

    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    luaL_getmetatable(L, vec_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_eq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        lua_pushboolean(L, *v1 == *v2);
    }
    else
    {
        lua_pushboolean(L, false);
    }
    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_neq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        lua_pushboolean(L, *v1 != *v2);
    }
    else
    {
        lua_pushboolean(L, true);
    }
    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_lt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        lua_pushboolean(L, *v1 < *v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s < %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_le(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        lua_pushboolean(L, *v1 <= *v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s <= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_gt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        lua_pushboolean(L, *v1 > *v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s > %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t N, typename T>
int fun_lua_vec_ge(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::vec<N, T>>(L, 1) && luaL_is_ktm_type<ktm::vec<N, T>>(L, 2))
    {
        ktm::vec<N, T>* v1 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
        ktm::vec<N, T>* v2 = luaL_check_ktm_type<ktm::vec<N, T>>(L, 2);
        lua_pushboolean(L, *v1 >= *v2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s >= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t N, typename T>
inline void register_lua_vec(lua_State* L)
{
    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    luaL_newmetatable(L, vec_name);

    constexpr const luaL_Reg vec_metamethods[] = { { "__tostring", fun_lua_vec_tostring<N, T> },
                                                   { "__index", fun_lua_vec_index<N, T> },
                                                   { "__newindex", fun_lua_vec_newindex<N, T> },
                                                   { "__add", fun_lua_vec_add<N, T> },
                                                   { "__sub", fun_lua_vec_sub<N, T> },
                                                   { "__mul", fun_lua_vec_mul<N, T> },
                                                   { "__div", fun_lua_vec_div<N, T> },
                                                   { "__eq", fun_lua_vec_eq<N, T> },
                                                   { "__neq", fun_lua_vec_neq<N, T> },
                                                   { "__lt", fun_lua_vec_lt<N, T> },
                                                   { "__le", fun_lua_vec_le<N, T> },
                                                   { "__gt", fun_lua_vec_gt<N, T> },
                                                   { "__ge", fun_lua_vec_ge<N, T> },
                                                   { nullptr, nullptr } };
    luaL_setfuncs(L, vec_metamethods, 0);

    lua_newtable(L);

    constexpr auto fun_create_lua_vec_wrapper = fun_create_lua_vec<N, T>;
    lua_pushcfunction(L, fun_create_lua_vec_wrapper);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);

    lua_setglobal(L, vec_name);
}
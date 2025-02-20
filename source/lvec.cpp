#include <sstream>
#include "lvec.h"

template <size_t N>
void register_lvec(lua_State* L)
{
    lvec<N>::template register_type<int>(L);
    lvec<N>::template register_type<unsigned int>(L);
    lvec<N>::template register_type<float>(L);
    lvec<N>::template register_type<double>(L);
}

template void register_lvec<2>(lua_State* L);
template void register_lvec<3>(lua_State* L);
template void register_lvec<4>(lua_State* L);

template <size_t N>
template <typename T>
int lvec<N>::create(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::tostring(lua_State* L)
{
    ktm::vec<N, T>* v = luaL_check_ktm_type<ktm::vec<N, T>>(L, 1);
    std::stringstream ss;
    ss << *v;
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

template <size_t N>
template <typename T>
int lvec<N>::index(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::newindex(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::add(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::sub(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::mul(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::div(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::eq(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::neq(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::lt(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::le(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::gt(lua_State* L)
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

template <size_t N>
template <typename T>
int lvec<N>::ge(lua_State* L)
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

template <size_t N>
template <typename T>
void lvec<N>::register_type(lua_State* L)
{
    constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<N, T>>;
    luaL_newmetatable(L, vec_name);

    constexpr const luaL_Reg vec_metamethods[] = { { "__tostring", lvec<N>::tostring<T> },
                                                   { "__index", lvec<N>::index<T> },
                                                   { "__newindex", lvec<N>::newindex<T> },
                                                   { "__add", lvec<N>::add<T> },
                                                   { "__sub", lvec<N>::sub<T> },
                                                   { "__mul", lvec<N>::mul<T> },
                                                   { "__div", lvec<N>::div<T> },
                                                   { "__eq", lvec<N>::eq<T> },
                                                   { "__neq", lvec<N>::neq<T> },
                                                   { "__lt", lvec<N>::lt<T> },
                                                   { "__le", lvec<N>::le<T> },
                                                   { "__gt", lvec<N>::gt<T> },
                                                   { "__ge", lvec<N>::ge<T> },
                                                   { nullptr, nullptr } };
    luaL_setfuncs(L, vec_metamethods, 0);

    lua_newtable(L);

    constexpr auto fun_create_lua_vec_wrapper = lvec<N>::create<T>;
    lua_pushcfunction(L, fun_create_lua_vec_wrapper);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);

    lua_setglobal(L, vec_name);
}
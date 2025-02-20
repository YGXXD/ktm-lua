//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include <sstream>
#include "lmat.h"

template <size_t Row, size_t Col>
void register_lmat(lua_State* L)
{
    lmat<Row, Col>::template register_type<int>(L);
    lmat<Row, Col>::template register_type<unsigned int>(L);
    lmat<Row, Col>::template register_type<float>(L);
    lmat<Row, Col>::template register_type<double>(L);
}

template void register_lmat<2, 2>(lua_State* L);
template void register_lmat<2, 3>(lua_State* L);
template void register_lmat<2, 4>(lua_State* L);
template void register_lmat<3, 2>(lua_State* L);
template void register_lmat<3, 3>(lua_State* L);
template void register_lmat<3, 4>(lua_State* L);
template void register_lmat<4, 2>(lua_State* L);
template void register_lmat<4, 3>(lua_State* L);
template void register_lmat<4, 4>(lua_State* L);

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::create(lua_State* L)
{
    constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
    int arg_count = lua_gettop(L) - 1;

    ktm::mat<Row, Col, T>* mem = lua_newuserdata_ex<ktm::mat<Row, Col, T>>(L);
    if (arg_count > Row)
    {
        luaL_error(L, "invalid number of arguments on create %s: %d", mat_name, arg_count);
    }
    for (int i = 0; i < arg_count; ++i)
    {
        (*mem)[i] = *luaL_check_ktm_type<ktm::vec<Col, T>>(L, i + 2);
    }

    luaL_getmetatable(L, mat_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::tostring(lua_State* L)
{
    ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
    std::stringstream ss;
    ss << *m;
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::index(lua_State* L)
{
    if (lua_isinteger(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > Row)
        {
            luaL_error(L, "index out of range [1,%d]", Row);
        }

        lua_pushlightuserdata(L, &(*m)[index - 1]);
        lua_pushvalue(L, 1);
        lua_setuservalue(L, -2);

        constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<Col, T>>;
        luaL_getmetatable(L, vec_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 2);
        lua_rawget(L, -2);
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::newindex(lua_State* L)
{
    ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
    ktm::vec<Col, T>* value = luaL_check_ktm_type<ktm::vec<Col, T>>(L, 3);
    if (lua_isinteger(L, 2))
    {
        int index = luaL_checkinteger(L, 2);
        if (index < 1 || index > Row)
        {
            luaL_error(L, "index out of range [1,%d]", Row);
        }
        (*m)[index - 1] = *value;
    }
    else
    {
        luaL_error(L, "invalid property name: %s", lua_tostring(L, 2));
    }
    return 0;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::add(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);

        lua_newuserdata_ex<ktm::mat<Row, Col, T>>(L, *m + *n);

        constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
        luaL_getmetatable(L, mat_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s + %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::sub(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);

        lua_newuserdata_ex<ktm::mat<Row, Col, T>>(L, *m - *n);

        constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
        luaL_getmetatable(L, mat_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s - %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::mul(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);

        if (luaL_is_ktm_type<ktm::mat<4, Row, T>>(L, 2))
        {
            ktm::mat<4, Row, T>* n = luaL_check_ktm_type<ktm::mat<4, Row, T>>(L, 2);

            lua_newuserdata_ex<ktm::mat<4, Col, T>>(L, *m * *n);

            constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<4, Col, T>>;
            luaL_getmetatable(L, mat_name);
        }
        else if (luaL_is_ktm_type<ktm::mat<3, Row, T>>(L, 2))
        {
            ktm::mat<3, Row, T>* n = luaL_check_ktm_type<ktm::mat<3, Row, T>>(L, 2);

            lua_newuserdata_ex<ktm::mat<3, Col, T>>(L, *m * *n);

            constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<3, Col, T>>;
            luaL_getmetatable(L, mat_name);
        }
        else if (luaL_is_ktm_type<ktm::mat<2, Row, T>>(L, 2))
        {
            ktm::mat<2, Row, T>* n = luaL_check_ktm_type<ktm::mat<2, Row, T>>(L, 2);

            lua_newuserdata_ex<ktm::mat<2, Col, T>>(L, *m * *n);

            constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<2, Col, T>>;
            luaL_getmetatable(L, mat_name);
        }
        else if (lua_isnumber(L, 2))
        {
            T scalar = static_cast<T>(luaL_checknumber(L, 2));

            lua_newuserdata_ex<ktm::mat<Row, Col, T>>(L, *m * scalar);

            constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
            luaL_getmetatable(L, mat_name);
        }
        else
        {
            luaL_error(L, "invalid operator: %s * %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
        }
    }
    else if (lua_isnumber(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        T scalar = static_cast<T>(luaL_checknumber(L, 1));
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);

        lua_newuserdata_ex<ktm::mat<Row, Col, T>>(L, *m * scalar);

        constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
        luaL_getmetatable(L, mat_name);
    }
    else
    {
        luaL_error(L, "invalid operator: %s * %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    lua_setmetatable(L, -2);
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::div(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && lua_isnumber(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        T scalar = static_cast<T>(luaL_checknumber(L, 2));

        lua_newuserdata_ex<ktm::mat<Row, Col, T>>(L, *m / scalar);

        constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
        luaL_getmetatable(L, mat_name);
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "invalid operator: %s / %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }

    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::eq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);
        lua_pushboolean(L, *m == *n);
    }
    else
    {
        lua_pushboolean(L, false);
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::neq(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);
        lua_pushboolean(L, *m != *n);
    }
    else
    {
        lua_pushboolean(L, true);
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::lt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);
        lua_pushboolean(L, *m < *n);
    }
    else
    {
        luaL_error(L, "invalid operator: %s < %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::le(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);
        lua_pushboolean(L, *m <= *n);
    }
    else
    {
        luaL_error(L, "invalid operator: %s <= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::gt(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);
        lua_pushboolean(L, *m > *n);
    }
    else
    {
        luaL_error(L, "invalid operator: %s > %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
int lmat<Row, Col>::ge(lua_State* L)
{
    if (luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 1) && luaL_is_ktm_type<ktm::mat<Row, Col, T>>(L, 2))
    {
        ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
        ktm::mat<Row, Col, T>* n = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 2);
        lua_pushboolean(L, *m >= *n);
    }
    else
    {
        luaL_error(L, "invalid operator: %s >= %s", luaL_typename_ex(L, 1), luaL_typename_ex(L, 2));
    }
    return 1;
}

template <size_t Row, size_t Col>
template <typename T>
inline void lmat<Row, Col>::register_type(lua_State* L)
{
    constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>;
    luaL_newmetatable(L, mat_name);

    constexpr const luaL_Reg vec_metamethods[] = { { "__tostring", lmat<Row, Col>::tostring<T> },
                                                   { "__index", lmat<Row, Col>::index<T> },
                                                   { "__newindex", lmat<Row, Col>::newindex<T> },
                                                   { "__add", lmat<Row, Col>::add<T> },
                                                   { "__sub", lmat<Row, Col>::sub<T> },
                                                   { "__mul", lmat<Row, Col>::mul<T> },
                                                   { "__div", lmat<Row, Col>::div<T> },
                                                   { "__eq", lmat<Row, Col>::eq<T> },
                                                   { "__neq", lmat<Row, Col>::neq<T> },
                                                   { "__lt", lmat<Row, Col>::lt<T> },
                                                   { "__le", lmat<Row, Col>::le<T> },
                                                   { "__gt", lmat<Row, Col>::gt<T> },
                                                   { "__ge", lmat<Row, Col>::ge<T> },
                                                   { nullptr, nullptr } };
    luaL_setfuncs(L, vec_metamethods, 0);

    lua_newtable(L);

    constexpr auto fun_create_lua_mat_wrapper = lmat<Row, Col>::create<T>;
    lua_pushcfunction(L, fun_create_lua_mat_wrapper);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);

    lua_setglobal(L, mat_name);
}
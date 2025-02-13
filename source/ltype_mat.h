#pragma once

#include <sstream>
#include "lktm_api.h"

template <size_t Row, size_t Col, typename T>
int fun_create_lua_mat(lua_State* L)
{
    constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>.data();
    ktm::mat<Row, Col, T>* mem =
        reinterpret_cast<ktm::mat<Row, Col, T>*>(lua_newuserdata(L, sizeof(ktm::mat<Row, Col, T>)));
    new (mem) ktm::mat<Row, Col, T>();

    int n = lua_gettop(L) - 2;
    if (n > Row)
    {
        luaL_error(L, "invalid number of arguments on create %s: %d", mat_name, n);
    }
    for (int i = 0; i < n; ++i)
    {
        (*mem)[i] = *luaL_check_ktm_type<ktm::vec<Col, T>>(L, i + 2);
    }

    luaL_getmetatable(L, mat_name);
    lua_setmetatable(L, -2);

    return 1;
}

template <size_t Row, size_t Col, typename T>
int fun_lua_mat_tostring(lua_State* L)
{
    ktm::mat<Row, Col, T>* m = luaL_check_ktm_type<ktm::mat<Row, Col, T>>(L, 1);
    std::stringstream ss;
    ss << *m;
    lua_pushstring(L, ss.str().c_str());
    return 1;
}

template <size_t Row, size_t Col, typename T>
inline void register_lua_mat(lua_State* L)
{
    constexpr auto mat_name = lua_ktm_typename_v<ktm::mat<Row, Col, T>>.data();
    luaL_newmetatable(L, mat_name);

    constexpr const luaL_Reg vec_metamethods[] = { { "__tostring", fun_lua_mat_tostring<Row, Col, T> },
                                                   { nullptr, nullptr } };
    luaL_setfuncs(L, vec_metamethods, 0);

    lua_newtable(L);

    constexpr auto fun_create_lua_mat_wrapper = fun_create_lua_mat<Row, Col, T>;
    lua_pushcfunction(L, fun_create_lua_mat_wrapper);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);

    lua_setglobal(L, mat_name);
}
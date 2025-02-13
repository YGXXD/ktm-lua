#pragma once

#include "lua_ktm_api.h"

template <size_t N, typename T>
struct lua_ktm_typename<ktm::vec<N, T>>
{
    static constexpr inline std::array<char, 6> call()
    {
        if constexpr (std::is_same_v<T, float>)
            return { 'f', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else if constexpr (std::is_same_v<T, double>)
            return { 'd', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else if constexpr (std::is_same_v<T, int>)
            return { 's', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else if constexpr (std::is_same_v<T, unsigned int>)
            return { 'u', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else
            throw std::runtime_error("invalid lua vec type");
    }

    static constexpr auto value = call();
};

template <size_t Row, size_t Col, typename T>
struct lua_ktm_typename<ktm::mat<Row, Col, T>>
{
    static constexpr inline std::array<char, 8> call()
    {
        if constexpr (std::is_same_v<T, float>)
            return { 'f', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col), '\0' };
        else if constexpr (std::is_same_v<T, double>)
            return { 'd', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col), '\0' };
        else if constexpr (std::is_same_v<T, int>)
            return { 's', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col), '\0' };
        else if constexpr (std::is_same_v<T, unsigned int>)
            return { 'u', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col), '\0' };
        else
            throw std::runtime_error("invalid lua vec type");
    }

    static constexpr auto value = call();
};

template <typename T>
inline bool luaL_is_ktm_type(lua_State* L, int idx)
{
    return luaL_testudata(L, idx, lua_ktm_typename_v<T>.data());
}

template <typename T>
inline T* luaL_check_ktm_type(lua_State* L, int idx)
{
    return reinterpret_cast<T*>(luaL_checkudata(L, idx, lua_ktm_typename_v<T>.data()));
}
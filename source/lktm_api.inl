#pragma once

#include "lktm_api.h"

template <size_t N, typename T>
struct lua_ktm_typename<ktm::vec<N, T>>
{
    static constexpr inline auto call()
    {
        if constexpr (std::is_same_v<T, float>)
            return std::array { 'f', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else if constexpr (std::is_same_v<T, double>)
            return std::array { 'd', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else if constexpr (std::is_same_v<T, int>)
            return std::array { 's', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else if constexpr (std::is_same_v<T, unsigned int>)
            return std::array { 'u', 'v', 'e', 'c', static_cast<char>('0' + N), '\0' };
        else
            throw std::runtime_error("invalid lua vec type");
    }

    static constexpr auto value = call();
};

template <size_t Row, size_t Col, typename T>
struct lua_ktm_typename<ktm::mat<Row, Col, T>>
{
    static constexpr inline auto call()
    {
        if constexpr (std::is_same_v<T, float>)
            return std::array { 'f', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col),
                                '\0' };
        else if constexpr (std::is_same_v<T, double>)
            return std::array { 'd', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col),
                                '\0' };
        else if constexpr (std::is_same_v<T, int>)
            return std::array { 's', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col),
                                '\0' };
        else if constexpr (std::is_same_v<T, unsigned int>)
            return std::array { 'u', 'm', 'a', 't', static_cast<char>('0' + Row), 'x', static_cast<char>('0' + Col),
                                '\0' };
        else
            throw std::runtime_error("invalid lua vec type");
    }

    static constexpr auto value = call();
};

template <typename T>
struct lua_ktm_typename<ktm::quat<T>>
{
    static constexpr inline auto call()
    {
        if constexpr (std::is_same_v<T, float>)
            return std::array { 'f', 'q', 'u', 'a', 't', '\0' };
        else if constexpr (std::is_same_v<T, double>)
            return std::array { 'd', 'q', 'u', 'a', 't', '\0' };
        else
            throw std::runtime_error("invalid lua quat type");
    }

    static constexpr auto value = call();
};

template <typename T>
struct lua_ktm_typename<ktm::comp<T>>
{
    static constexpr inline std::array<char, 6> call()
    {
        if constexpr (std::is_same_v<T, float>)
            return { 'f', 'c', 'o', 'm', 'p', '\0' };
        else if constexpr (std::is_same_v<T, double>)
            return { 'd', 'c', 'o', 'm', 'p', '\0' };
        else
            throw std::runtime_error("invalid lua comp type");
    }

    static constexpr auto value = call();
};

template <typename T, typename... Args>
inline T* lua_newuserdata_ex(lua_State* L, Args&&... args)
{
    void* mem = lua_newuserdata(L, sizeof(T));
    new (mem) T(std::forward<Args>(args)...);
    return reinterpret_cast<T*>(mem);
}

template <typename T>
inline bool luaL_is_ktm_type(lua_State* L, int idx)
{
    return luaL_testudata(L, idx, lua_ktm_typename_v<T>);
}

template <typename T>
inline T* luaL_check_ktm_type(lua_State* L, int idx)
{
    return reinterpret_cast<T*>(luaL_checkudata(L, idx, lua_ktm_typename_v<T>));
}
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "lua_ktm_api.h"
#include "lua_ntr_api.hpp"

template <typename T>
struct lvec2
{
    lvec2 __add(const lvec2& other) { return lvec2 { value + other.value }; }

    lvec2 __sub(const lvec2& other) { return lvec2 { value - other.value }; }

    lvec2 __mul(const lvec2& other) { return lvec2 { value * other.value }; }

    lvec2 __div(const lvec2& other) { return lvec2 { value / other.value }; }

    bool __eq(const lvec2& other) { return value == other.value; }

    bool __neq(const lvec2& other) { return value != other.value; }

    bool __lt(const lvec2& other) { return value < other.value; }

    bool __le(const lvec2& other) { return value <= other.value; }

    bool __gt(const lvec2& other) { return value > other.value; }

    bool __ge(const lvec2& other) { return value >= other.value; }

    std::string __tostring() const
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    union
    {
        ktm::vec<2, T> value;

        struct
        {
            T x, y;
        };
    };
};

const int register_lvec2_ntr = []() -> int
{
    auto register_lvec2_ntr_lambda = []<typename T>()
    {
        constexpr auto vec_name = lua_ktm_typename_v<ktm::vec<2, T>>;
        ntr::nephren::type<lvec2<T>>(vec_name)
            .function("__add", &lvec2<T>::__add)
            .function("__sub", &lvec2<T>::__sub)
            .function("__mul", &lvec2<T>::__mul)
            .function("__div", &lvec2<T>::__div)
            .function("__eq", &lvec2<T>::__eq)
            .function("__neq", &lvec2<T>::__neq)
            .function("__lt", &lvec2<T>::__lt)
            .function("__le", &lvec2<T>::__le)
            .function("__gt", &lvec2<T>::__gt)
            .function("__ge", &lvec2<T>::__ge)
            .function("__tostring", &lvec2<T>::__tostring)
            .property("x", &lvec2<T>::x)
            .property("y", &lvec2<T>::y);
    };

    register_lvec2_ntr_lambda.template operator()<int>();
    register_lvec2_ntr_lambda.template operator()<unsigned int>();
    register_lvec2_ntr_lambda.template operator()<float>();
    register_lvec2_ntr_lambda.template operator()<double>();

    return 1;
}();

inline void register_lvec2_lua(lua_State* L)
{
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<unsigned int>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<float>>()->name());
    lua_ntr_regist_type(L, ntr::nephren::get<lvec2<double>>()->name());
}
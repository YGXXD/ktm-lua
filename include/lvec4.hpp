//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <ktm/ktm.h>

template <typename T>
struct lvec4
{
    lvec4 __add(const lvec4& other);
    lvec4 __sub(const lvec4& other);
    lvec4 __mul(const lvec4& other);
    lvec4 __div(const lvec4& other);
    lvec4 __unm();
    bool __eq(const lvec4& other);
    bool __neq(const lvec4& other);
    bool __lt(const lvec4& other);
    bool __le(const lvec4& other);
    bool __gt(const lvec4& other);
    bool __ge(const lvec4& other);
    std::string __tostring() const;

    static lvec4 create(T x, T y, T z, T w);
    static T reduce_add(const lvec4& x);
    static T reduce_min(const lvec4& x);
    static T reduce_max(const lvec4& x);
    static lvec4 min(const lvec4& x, const lvec4& y);
    static lvec4 max(const lvec4& x, const lvec4& y);
    static lvec4 clamp(const lvec4& x, const lvec4& min, const lvec4& max);

    union
    {
        ktm::vec<4, T> value;
        struct
        {
            T x, y, z, w;
        };
    };
};

template <typename T, typename = std::enable_if_t<std::is_signed_v<T>>>
struct lvec4_signed
{
    static lvec4<T> abs(const lvec4<T>& x);
};

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lvec4_floating
{
    static lvec4<T> floor(const lvec4<T>& x);
    static lvec4<T> ceil(const lvec4<T>& x);
    static lvec4<T> round(const lvec4<T>& x);
    static lvec4<T> fract(const lvec4<T>& x);
    static lvec4<T> mod(const lvec4<T>& x, const lvec4<T>& y);
    static lvec4<T> lerp(const lvec4<T>& x, const lvec4<T>& y, T t);
    static lvec4<T> mix(const lvec4<T>& x, const lvec4<T>& y, const lvec4<T>& t);
    static lvec4<T> step(const lvec4<T>& edge, const lvec4<T>& x);
    static lvec4<T> smoothstep(const lvec4<T>& edge0, const lvec4<T>& edge1, const lvec4<T>& x);
};

struct regist_lvec4
{
    static constexpr std::string_view iname = "svec4";
    static constexpr std::string_view uname = "uvec4";
    static constexpr std::string_view fname = "fvec4";
    static constexpr std::string_view dname = "dvec4";
    static const int flag;
};
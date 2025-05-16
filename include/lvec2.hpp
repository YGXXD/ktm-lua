//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ktm/ktm/ktm.h"

template <typename T>
struct lvec2
{
    lvec2 __add(const lvec2& other);
    lvec2 __sub(const lvec2& other);
    lvec2 __mul(const lvec2& other);
    lvec2 __div(const lvec2& other);
    lvec2 __unm();
    bool __eq(const lvec2& other);
    bool __neq(const lvec2& other);
    bool __lt(const lvec2& other);
    bool __le(const lvec2& other);
    bool __gt(const lvec2& other);
    bool __ge(const lvec2& other);
    std::string __tostring() const;

    static lvec2 create(T x, T y);
    static T reduce_add(const lvec2& x);
    static T reduce_min(const lvec2& x);
    static T reduce_max(const lvec2& x);
    static lvec2 min(const lvec2& x, const lvec2& y);
    static lvec2 max(const lvec2& x, const lvec2& y);
    static lvec2 clamp(const lvec2& x, const lvec2& min, const lvec2& max);

    union
    {
        ktm::vec<2, T> value;
        struct
        {
            T x, y;
        };
    };
};

template <typename T, typename = std::enable_if_t<std::is_signed_v<T>>>
struct lvec2_signed
{
    static lvec2<T> abs(const lvec2<T>& x);
};

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lvec2_floating
{
    static lvec2<T> floor(const lvec2<T>& x);
    static lvec2<T> ceil(const lvec2<T>& x);
    static lvec2<T> round(const lvec2<T>& x);
    static lvec2<T> fract(const lvec2<T>& x);
    static lvec2<T> mod(const lvec2<T>& x, const lvec2<T>& y);
    static lvec2<T> lerp(const lvec2<T>& x, const lvec2<T>& y, T t);
    static lvec2<T> mix(const lvec2<T>& x, const lvec2<T>& y, const lvec2<T>& t);
    static lvec2<T> step(const lvec2<T>& edge, const lvec2<T>& x);
    static lvec2<T> smoothstep(const lvec2<T>& edge0, const lvec2<T>& edge1, const lvec2<T>& x);
};

struct regist_lvec2
{
    static constexpr std::string_view iname = "svec2";
    static constexpr std::string_view uname = "uvec2";
    static constexpr std::string_view fname = "fvec2";
    static constexpr std::string_view dname = "dvec2";
    static const int flag;
};
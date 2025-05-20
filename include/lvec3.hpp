//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <ktm/ktm.h>

template <typename T>
struct lvec3
{
    lvec3 __add(const lvec3& other);
    lvec3 __sub(const lvec3& other);
    lvec3 __mul(const lvec3& other);
    lvec3 __div(const lvec3& other);
    lvec3 __unm();
    bool __eq(const lvec3& other);
    bool __neq(const lvec3& other);
    bool __lt(const lvec3& other);
    bool __le(const lvec3& other);
    bool __gt(const lvec3& other);
    bool __ge(const lvec3& other);
    std::string __tostring() const;

    static lvec3 create(T x, T y, T z);
    static T reduce_add(const lvec3& x);
    static T reduce_min(const lvec3& x);
    static T reduce_max(const lvec3& x);
    static lvec3 min(const lvec3& x, const lvec3& y);
    static lvec3 max(const lvec3& x, const lvec3& y);
    static lvec3 clamp(const lvec3& x, const lvec3& min, const lvec3& max);

    union
    {
        ktm::vec<3, T> value;
        struct
        {
            T x, y, z;
        };
    };
};

template <typename T, typename = std::enable_if_t<std::is_signed_v<T>>>
struct lvec3_signed
{
    static lvec3<T> abs(const lvec3<T>& x);
};

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lvec3_floating
{
    static lvec3<T> floor(const lvec3<T>& x);
    static lvec3<T> ceil(const lvec3<T>& x);
    static lvec3<T> round(const lvec3<T>& x);
    static lvec3<T> fract(const lvec3<T>& x);
    static lvec3<T> mod(const lvec3<T>& x, const lvec3<T>& y);
    static lvec3<T> lerp(const lvec3<T>& x, const lvec3<T>& y, T t);
    static lvec3<T> mix(const lvec3<T>& x, const lvec3<T>& y, const lvec3<T>& t);
    static lvec3<T> step(const lvec3<T>& edge, const lvec3<T>& x);
    static lvec3<T> smoothstep(const lvec3<T>& edge0, const lvec3<T>& edge1, const lvec3<T>& x);
};

struct regist_lvec3
{
    static constexpr std::string_view iname = "svec3";
    static constexpr std::string_view uname = "uvec3";
    static constexpr std::string_view fname = "fvec3";
    static constexpr std::string_view dname = "dvec3";
    static const int flag;
};
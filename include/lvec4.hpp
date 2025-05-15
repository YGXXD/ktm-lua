//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ktm/ktm/ktm.h"

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

    union
    {
        ktm::vec<4, T> value;
        struct
        {
            T x, y, z, w;
        };
    };
};

struct regist_lvec4
{
    static constexpr std::string_view iname = "ivec4";
    static constexpr std::string_view uname = "uvec4";
    static constexpr std::string_view fname = "fvec4";
    static constexpr std::string_view dname = "dvec4";
    static const int flag;
};
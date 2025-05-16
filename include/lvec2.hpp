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

    union
    {
        ktm::vec<2, T> value;
        struct
        {
            T x, y;
        };
    };
};

struct regist_lvec2
{
    static constexpr std::string_view iname = "svec2";
    static constexpr std::string_view uname = "uvec2";
    static constexpr std::string_view fname = "fvec2";
    static constexpr std::string_view dname = "dvec2";
    static const int flag;
};
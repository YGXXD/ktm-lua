//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ktm/ktm/ktm.h"

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

    union
    {
        ktm::vec<3, T> value;
        struct
        {
            T x, y, z;
        };
    };
};

struct regist_lvec3
{
    static constexpr std::string_view iname = "svec3";
    static constexpr std::string_view uname = "uvec3";
    static constexpr std::string_view fname = "fvec3";
    static constexpr std::string_view dname = "dvec3";
    static const int flag;
};
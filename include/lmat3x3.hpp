//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ktm/ktm/ktm.h"
#include "lvec3.hpp"

template <typename T>
struct lmat3x3
{
    lmat3x3 __add(const lmat3x3& other);
    lmat3x3 __sub(const lmat3x3& other);
    lmat3x3 __mul(const lmat3x3& other);
    lmat3x3 __unm();
    bool __eq(const lmat3x3& other);
    bool __neq(const lmat3x3& other);
    bool __lt(const lmat3x3& other);
    bool __le(const lmat3x3& other);
    bool __gt(const lmat3x3& other);
    bool __ge(const lmat3x3& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<3, 3, T> value;
        struct
        {
            lvec3<T> col1;
            lvec3<T> col2;
            lvec3<T> col3;
        };
    };
};

struct regist_lmat3x3
{
    static constexpr std::string_view iname = "imat3x3";
    static constexpr std::string_view uname = "umat3x3";
    static constexpr std::string_view fname = "fmat3x3";
    static constexpr std::string_view dname = "dmat3x3";
    static const int flag;
};
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

template <typename T>
struct lmat3x3;

template <typename T>
struct lmat3x4;

#include "ktm/ktm/ktm.h"
#include "lvec3.hpp"

template <typename T>
struct lmat4x3
{
    lmat4x3 __add(const lmat4x3& other);
    lmat4x3 __sub(const lmat4x3& other);
    lmat3x3<T> __mul(const lmat3x4<T>& other);
    lmat4x3 __unm();
    bool __eq(const lmat4x3& other);
    bool __neq(const lmat4x3& other);
    bool __lt(const lmat4x3& other);
    bool __le(const lmat4x3& other);
    bool __gt(const lmat4x3& other);
    bool __ge(const lmat4x3& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<4, 3, T> value;
        struct
        {
            lvec3<T> col1;
            lvec3<T> col2;
            lvec3<T> col3;
            lvec3<T> col4;
        };
    };
};

struct regist_lmat4x3
{
    static constexpr std::string_view iname = "smat4x3";
    static constexpr std::string_view uname = "umat4x3";
    static constexpr std::string_view fname = "fmat4x3";
    static constexpr std::string_view dname = "dmat4x3";
    static const int flag;
};
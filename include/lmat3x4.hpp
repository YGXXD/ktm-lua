//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

template <typename T>
struct lmat4x4;

template <typename T>
struct lmat4x3;

#include "ktm/ktm/ktm.h"
#include "lvec4.hpp"

template <typename T>
struct lmat3x4
{
    lmat3x4 __add(const lmat3x4& other);
    lmat3x4 __sub(const lmat3x4& other);
    lmat4x4<T> __mul(const lmat4x3<T>& other);
    lmat3x4 __unm();
    bool __eq(const lmat3x4& other);
    bool __neq(const lmat3x4& other);
    bool __lt(const lmat3x4& other);
    bool __le(const lmat3x4& other);
    bool __gt(const lmat3x4& other);
    bool __ge(const lmat3x4& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<3, 4, T> value;
        struct
        {
            lvec4<T> col1;
            lvec4<T> col2;
            lvec4<T> col3;
        };
    };
};

struct regist_lmat3x4
{
    static constexpr std::string_view iname = "smat3x4";
    static constexpr std::string_view uname = "umat3x4";
    static constexpr std::string_view fname = "fmat3x4";
    static constexpr std::string_view dname = "dmat3x4";
    static const int flag;
};
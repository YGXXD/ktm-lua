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
struct lmat4x2;

#include "ktm/ktm/ktm.h"
#include "lvec4.hpp"

template <typename T>
struct lmat2x4
{
    lmat2x4 __add(const lmat2x4& other);
    lmat2x4 __sub(const lmat2x4& other);
    lmat4x4<T> __mul(const lmat4x2<T>& other);
    lmat2x4 __unm();
    bool __eq(const lmat2x4& other);
    bool __neq(const lmat2x4& other);
    bool __lt(const lmat2x4& other);
    bool __le(const lmat2x4& other);
    bool __gt(const lmat2x4& other);
    bool __ge(const lmat2x4& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<2, 4, T> value;
        struct
        {
            lvec4<T> col1;
            lvec4<T> col2;
        };
    };
};

struct regist_lmat2x4
{
    static constexpr std::string_view iname = "smat2x4";
    static constexpr std::string_view uname = "umat2x4";
    static constexpr std::string_view fname = "fmat2x4";
    static constexpr std::string_view dname = "dmat2x4";
    static const int flag;
};
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

template <typename T>
struct lmat2x2;

template <typename T>
struct lmat2x4;

#include <ktm/ktm.h>
#include "lvec2.hpp"

template <typename T>
struct lmat4x2
{
    lmat4x2 __add(const lmat4x2& other);
    lmat4x2 __sub(const lmat4x2& other);
    lmat2x2<T> __mul(const lmat2x4<T>& other);
    lmat4x2 __unm();
    bool __eq(const lmat4x2& other);
    bool __neq(const lmat4x2& other);
    bool __lt(const lmat4x2& other);
    bool __le(const lmat4x2& other);
    bool __gt(const lmat4x2& other);
    bool __ge(const lmat4x2& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<4, 2, T> value;
        struct
        {
            lvec2<T> col1;
            lvec2<T> col2;
            lvec2<T> col3;
            lvec2<T> col4;
        };
    };
};

struct regist_lmat4x2
{
    static constexpr std::string_view iname = "smat4x2";
    static constexpr std::string_view uname = "umat4x2";
    static constexpr std::string_view fname = "fmat4x2";
    static constexpr std::string_view dname = "dmat4x2";
    static const int flag;
};
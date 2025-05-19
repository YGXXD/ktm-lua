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
struct lmat2x3;

#include <ktm/ktm.h>
#include "lvec2.hpp"

template <typename T>
struct lmat3x2
{
    lmat3x2 __add(const lmat3x2& other);
    lmat3x2 __sub(const lmat3x2& other);
    lmat2x2<T> __mul(const lmat2x3<T>& other);
    lmat3x2 __unm();
    bool __eq(const lmat3x2& other);
    bool __neq(const lmat3x2& other);
    bool __lt(const lmat3x2& other);
    bool __le(const lmat3x2& other);
    bool __gt(const lmat3x2& other);
    bool __ge(const lmat3x2& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<3, 2, T> value;
        struct
        {
            lvec2<T> col1;
            lvec2<T> col2;
            lvec2<T> col3;
        };
    };
};

struct regist_lmat3x2
{
    static constexpr std::string_view iname = "smat3x2";
    static constexpr std::string_view uname = "umat3x2";
    static constexpr std::string_view fname = "fmat3x2";
    static constexpr std::string_view dname = "dmat3x2";
    static const int flag;
};
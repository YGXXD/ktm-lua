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
struct lmat3x2;

#include <ktm/ktm.h>
#include "lvec3.hpp"

template <typename T>
struct lmat2x3
{
    lmat2x3 __add(const lmat2x3& other);
    lmat2x3 __sub(const lmat2x3& other);
    lmat3x3<T> __mul(const lmat3x2<T>& other);
    lmat2x3 __unm();
    bool __eq(const lmat2x3& other);
    bool __neq(const lmat2x3& other);
    bool __lt(const lmat2x3& other);
    bool __le(const lmat2x3& other);
    bool __gt(const lmat2x3& other);
    bool __ge(const lmat2x3& other);
    std::string __tostring() const;

    union
    {
        ktm::mat<2, 3, T> value;
        struct
        {
            lvec3<T> col1;
            lvec3<T> col2;
        };
    };
};

struct regist_lmat2x3
{
    static constexpr std::string_view iname = "smat2x3";
    static constexpr std::string_view uname = "umat2x3";
    static constexpr std::string_view fname = "fmat2x3";
    static constexpr std::string_view dname = "dmat2x3";
    static const int flag;
};
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <ktm/ktm.h>
#include "lvec4.hpp"

template <typename T>
struct lmat4x4
{
    lmat4x4 __add(const lmat4x4& other);
    lmat4x4 __sub(const lmat4x4& other);
    lmat4x4 __mul(const lmat4x4& other);
    lmat4x4 __unm();
    bool __eq(const lmat4x4& other);
    bool __neq(const lmat4x4& other);
    bool __lt(const lmat4x4& other);
    bool __le(const lmat4x4& other);
    bool __gt(const lmat4x4& other);
    bool __ge(const lmat4x4& other);
    std::string __tostring() const;

    static lmat4x4 create(const lvec4<T>& col1, const lvec4<T>& col2, const lvec4<T>& col3, const lvec4<T>& col4);
    static lmat4x4 from_row(const lvec4<T>& row1, const lvec4<T>& row2, const lvec4<T>& row3, const lvec4<T>& row4);
    static lmat4x4 from_diag(const lvec4<T>& diag);
    static lmat4x4 from_eye();
    static lmat4x4 transpose(const lmat4x4& mat);
    static lvec4<T> diagonal(const lmat4x4& mat);
    static T trace(const lmat4x4& mat);
    static T determinant(const lmat4x4& mat);

    union
    {
        ktm::mat<4, 4, T> value;
        struct
        {
            lvec4<T> col1;
            lvec4<T> col2;
            lvec4<T> col3;
            lvec4<T> col4;
        };
    };
};

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lmat4x4_floating
{
    static lmat4x4<T> inverse(const lmat4x4<T>& mat);
};

struct regist_lmat4x4
{
    static constexpr std::string_view iname = "smat4x4";
    static constexpr std::string_view uname = "umat4x4";
    static constexpr std::string_view fname = "fmat4x4";
    static constexpr std::string_view dname = "dmat4x4";
    static const int flag;
};
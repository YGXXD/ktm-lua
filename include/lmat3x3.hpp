//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <ktm/ktm.h>
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

    static lmat3x3 create(const lvec3<T>& col1, const lvec3<T>& col2, const lvec3<T>& col3);
    static lmat3x3 from_row(const lvec3<T>& row1, const lvec3<T>& row2, const lvec3<T>& row3);
    static lmat3x3 from_diag(const lvec3<T>& diag);
    static lmat3x3 from_eye();
    static lmat3x3 transpose(const lmat3x3& mat);
    static lvec3<T> diagonal(const lmat3x3& mat);
    static T trace(const lmat3x3& mat);
    static T determinant(const lmat3x3& mat);

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

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lmat3x3_floating
{
    static lmat3x3<T> inverse(const lmat3x3<T>& mat);
};

struct regist_lmat3x3
{
    static constexpr std::string_view iname = "smat3x3";
    static constexpr std::string_view uname = "umat3x3";
    static constexpr std::string_view fname = "fmat3x3";
    static constexpr std::string_view dname = "dmat3x3";
    static const int flag;
};
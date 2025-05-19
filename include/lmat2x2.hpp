//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <ktm/ktm.h>
#include "lvec2.hpp"

template <typename T>
struct lmat2x2
{
    lmat2x2 __add(const lmat2x2& other);
    lmat2x2 __sub(const lmat2x2& other);
    lmat2x2 __mul(const lmat2x2& other);
    lmat2x2 __unm();
    bool __eq(const lmat2x2& other);
    bool __neq(const lmat2x2& other);
    bool __lt(const lmat2x2& other);
    bool __le(const lmat2x2& other);
    bool __gt(const lmat2x2& other);
    bool __ge(const lmat2x2& other);
    std::string __tostring() const;

    static lmat2x2 create(const lvec2<T>& col1, const lvec2<T>& col2);
    static lmat2x2 from_row(const lvec2<T>& row1, const lvec2<T>& row2);
    static lmat2x2 from_diag(const lvec2<T>& diag);
    static lmat2x2 from_eye();
    static lmat2x2 transpose(const lmat2x2& mat);
    static lvec2<T> diagonal(const lmat2x2& mat);
    static T trace(const lmat2x2& mat);
    static T determinant(const lmat2x2& mat);

    union
    {
        ktm::mat<2, 2, T> value;
        struct
        {
            lvec2<T> col1;
            lvec2<T> col2;
        };
    };
};

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lmat2x2_floating
{
    static lmat2x2<T> inverse(const lmat2x2<T>& mat);
};

struct regist_lmat2x2
{
    static constexpr std::string_view iname = "smat2x2";
    static constexpr std::string_view uname = "umat2x2";
    static constexpr std::string_view fname = "fmat2x2";
    static constexpr std::string_view dname = "dmat2x2";
    static const int flag;
};
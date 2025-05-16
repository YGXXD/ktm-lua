//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ktm/ktm/ktm.h"
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

struct regist_lmat2x2
{
    static constexpr std::string_view iname = "smat2x2";
    static constexpr std::string_view uname = "umat2x2";
    static constexpr std::string_view fname = "fmat2x2";
    static constexpr std::string_view dname = "dmat2x2";
    static const int flag;
};
//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ktm/ktm/ktm.h"

template <typename T>
struct lcomp
{
    lcomp __add(const lcomp& other);
    lcomp __sub(const lcomp& other);
    lcomp __mul(const lcomp& other);
    lcomp __unm();
    bool __eq(const lcomp& other);
    bool __neq(const lcomp& other);
    bool __lt(const lcomp& other);
    bool __le(const lcomp& other);
    bool __gt(const lcomp& other);
    bool __ge(const lcomp& other);
    std::string __tostring() const;

    union
    {
        ktm::comp<T> value;
        struct
        {
            T i, r;
        };
    };
};

struct regist_lcomp
{
    static constexpr std::string_view fname = "fcomp";
    static constexpr std::string_view dname = "dcomp";
    static const int flag;
};
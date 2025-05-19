//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include <ktm/ktm.h>

template <typename T>
struct lquat
{
    lquat __add(const lquat& other);
    lquat __sub(const lquat& other);
    lquat __mul(const lquat& other);
    lquat __unm();
    bool __eq(const lquat& other);
    bool __neq(const lquat& other);
    bool __lt(const lquat& other);
    bool __le(const lquat& other);
    bool __gt(const lquat& other);
    bool __ge(const lquat& other);
    std::string __tostring() const;

    union
    {
        ktm::quat<T> value;
        struct
        {
            T i, j, k, r;
        };
    };
};

struct regist_lquat
{
    static constexpr std::string_view fname = "fquat";
    static constexpr std::string_view dname = "dquat";
    static const int flag;
};
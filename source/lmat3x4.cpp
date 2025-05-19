#include "lmat3x4.hpp"
#include "lmat4x4.hpp"
#include "lmat4x3.hpp"
#include <ntr/nephren.hpp>

template <typename T>
lmat3x4<T> lmat3x4<T>::__add(const lmat3x4<T>& other)
{
    return lmat3x4<T> { value + other.value };
}

template <typename T>
lmat3x4<T> lmat3x4<T>::__sub(const lmat3x4<T>& other)
{
    return lmat3x4<T> { value - other.value };
}

template <typename T>
lmat4x4<T> lmat3x4<T>::__mul(const lmat4x3<T>& other)
{
    return lmat4x4<T> { value * other.value };
}

template <typename T>
lmat3x4<T> lmat3x4<T>::__unm()
{
    return lmat3x4<T> { -value };
}

template <typename T>
bool lmat3x4<T>::__eq(const lmat3x4<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lmat3x4<T>::__neq(const lmat3x4<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lmat3x4<T>::__lt(const lmat3x4<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lmat3x4<T>::__le(const lmat3x4<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lmat3x4<T>::__gt(const lmat3x4<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lmat3x4<T>::__ge(const lmat3x4<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lmat3x4<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lmat3x4::flag = []() -> int
{
    auto regist_ntr_lmat3x4_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lmat3x4::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lmat3x4::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lmat3x4::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lmat3x4::uname;
        }();

        ntr::nephren::type<lmat3x4<T>>(name)
            .function("__add", &lmat3x4<T>::__add)
            .function("__sub", &lmat3x4<T>::__sub)
            .function("__mul", &lmat3x4<T>::__mul)
            .function("__unm", &lmat3x4<T>::__unm)
            .function("__eq", &lmat3x4<T>::__eq)
            .function("__neq", &lmat3x4<T>::__neq)
            .function("__lt", &lmat3x4<T>::__lt)
            .function("__le", &lmat3x4<T>::__le)
            .function("__gt", &lmat3x4<T>::__gt)
            .function("__ge", &lmat3x4<T>::__ge)
            .function("__tostring", &lmat3x4<T>::__tostring)
            .property("col1", &lmat3x4<T>::col1)
            .property("col2", &lmat3x4<T>::col2)
            .property("col3", &lmat3x4<T>::col3);
    };

    regist_ntr_lmat3x4_lambda.template operator()<int>();
    regist_ntr_lmat3x4_lambda.template operator()<unsigned int>();
    regist_ntr_lmat3x4_lambda.template operator()<float>();
    regist_ntr_lmat3x4_lambda.template operator()<double>();

    return 1;
}();
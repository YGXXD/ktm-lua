#include "lcomp.hpp"
#include <ntr/nephren.hpp>

template <typename T>
lcomp<T> lcomp<T>::__add(const lcomp<T>& other)
{
    return lcomp<T> { value + other.value };
}

template <typename T>
lcomp<T> lcomp<T>::__sub(const lcomp<T>& other)
{
    return lcomp<T> { value - other.value };
}

template <typename T>
lcomp<T> lcomp<T>::__mul(const lcomp<T>& other)
{
    return lcomp<T> { value * other.value };
}

template <typename T>
lcomp<T> lcomp<T>::__unm()
{
    return lcomp<T> { -value };
}

template <typename T>
bool lcomp<T>::__eq(const lcomp<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lcomp<T>::__neq(const lcomp<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lcomp<T>::__lt(const lcomp<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lcomp<T>::__le(const lcomp<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lcomp<T>::__gt(const lcomp<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lcomp<T>::__ge(const lcomp<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lcomp<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lcomp::flag = []() -> int
{
    auto regist_ntr_lcomp_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lcomp::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lcomp::dname;
        }();

        ntr::nephren::type<lcomp<T>>(name)
            .function("__add", &lcomp<T>::__add)
            .function("__sub", &lcomp<T>::__sub)
            .function("__mul", &lcomp<T>::__mul)
            .function("__unm", &lcomp<T>::__unm)
            .function("__eq", &lcomp<T>::__eq)
            .function("__neq", &lcomp<T>::__neq)
            .function("__lt", &lcomp<T>::__lt)
            .function("__le", &lcomp<T>::__le)
            .function("__gt", &lcomp<T>::__gt)
            .function("__ge", &lcomp<T>::__ge)
            .function("__tostring", &lcomp<T>::__tostring)
            .property("i", &lcomp<T>::i)
            .property("r", &lcomp<T>::r);
    };

    regist_ntr_lcomp_lambda.template operator()<float>();
    regist_ntr_lcomp_lambda.template operator()<double>();

    return 1;
}();
#include "lquat.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lquat<T> lquat<T>::__add(const lquat<T>& other)
{
    return lquat<T> { value + other.value };
}

template <typename T>
lquat<T> lquat<T>::__sub(const lquat<T>& other)
{
    return lquat<T> { value - other.value };
}

template <typename T>
lquat<T> lquat<T>::__mul(const lquat<T>& other)
{
    return lquat<T> { value * other.value };
}

template <typename T>
lquat<T> lquat<T>::__unm()
{
    return lquat<T> { -value };
}

template <typename T>
bool lquat<T>::__eq(const lquat<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lquat<T>::__neq(const lquat<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lquat<T>::__lt(const lquat<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lquat<T>::__le(const lquat<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lquat<T>::__gt(const lquat<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lquat<T>::__ge(const lquat<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lquat<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lquat::flag = []() -> int
{
    auto regist_ntr_lquat_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lquat::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lquat::dname;
        }();

        ntr::nephren::type<lquat<T>>(name)
            .function("__add", &lquat<T>::__add)
            .function("__sub", &lquat<T>::__sub)
            .function("__mul", &lquat<T>::__mul)
            .function("__unm", &lquat<T>::__unm)
            .function("__eq", &lquat<T>::__eq)
            .function("__neq", &lquat<T>::__neq)
            .function("__lt", &lquat<T>::__lt)
            .function("__le", &lquat<T>::__le)
            .function("__gt", &lquat<T>::__gt)
            .function("__ge", &lquat<T>::__ge)
            .function("__tostring", &lquat<T>::__tostring)
            .property("i", &lquat<T>::i)
            .property("j", &lquat<T>::j)
            .property("k", &lquat<T>::k)
            .property("r", &lquat<T>::r);
    };

    regist_ntr_lquat_lambda.template operator()<float>();
    regist_ntr_lquat_lambda.template operator()<double>();

    return 1;
}();
#include "lvec4.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lvec4<T> lvec4<T>::__add(const lvec4<T>& other)
{
    return lvec4<T> { value + other.value };
}

template <typename T>
lvec4<T> lvec4<T>::__sub(const lvec4<T>& other)
{
    return lvec4<T> { value - other.value };
}

template <typename T>
lvec4<T> lvec4<T>::__mul(const lvec4<T>& other)
{
    return lvec4<T> { value * other.value };
}

template <typename T>
lvec4<T> lvec4<T>::__div(const lvec4<T>& other)
{
    return lvec4<T> { value / other.value };
}

template <typename T>
lvec4<T> lvec4<T>::__unm()
{
    return lvec4<T> { -value };
}

template <typename T>
bool lvec4<T>::__eq(const lvec4<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lvec4<T>::__neq(const lvec4<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lvec4<T>::__lt(const lvec4<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lvec4<T>::__le(const lvec4<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lvec4<T>::__gt(const lvec4<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lvec4<T>::__ge(const lvec4<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lvec4<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lvec4::flag = []() -> int
{
    auto regist_ntr_lvec4_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lvec4::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lvec4::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lvec4::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lvec4::uname;
        }();

        ntr::nephren::type<lvec4<T>>(name)
            .function("__add", &lvec4<T>::__add)
            .function("__sub", &lvec4<T>::__sub)
            .function("__mul", &lvec4<T>::__mul)
            .function("__div", &lvec4<T>::__div)
            .function("__unm", &lvec4<T>::__unm)
            .function("__eq", &lvec4<T>::__eq)
            .function("__neq", &lvec4<T>::__neq)
            .function("__lt", &lvec4<T>::__lt)
            .function("__le", &lvec4<T>::__le)
            .function("__gt", &lvec4<T>::__gt)
            .function("__ge", &lvec4<T>::__ge)
            .function("__tostring", &lvec4<T>::__tostring)
            .property("x", &lvec4<T>::x)
            .property("y", &lvec4<T>::y)
            .property("z", &lvec4<T>::z)
            .property("w", &lvec4<T>::w);
    };

    regist_ntr_lvec4_lambda.template operator()<int>();
    regist_ntr_lvec4_lambda.template operator()<unsigned int>();
    regist_ntr_lvec4_lambda.template operator()<float>();
    regist_ntr_lvec4_lambda.template operator()<double>();

    return 1;
}();
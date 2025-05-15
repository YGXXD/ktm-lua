#include "lvec2.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lvec2<T> lvec2<T>::__add(const lvec2<T>& other)
{
    return lvec2<T> { value + other.value };
}

template <typename T>
lvec2<T> lvec2<T>::__sub(const lvec2<T>& other)
{
    return lvec2<T> { value - other.value };
}

template <typename T>
lvec2<T> lvec2<T>::__mul(const lvec2<T>& other)
{
    return lvec2<T> { value * other.value };
}

template <typename T>
lvec2<T> lvec2<T>::__div(const lvec2<T>& other)
{
    return lvec2<T> { value / other.value };
}

template <typename T>
lvec2<T> lvec2<T>::__unm()
{
    return lvec2<T> { -value };
}

template <typename T>
bool lvec2<T>::__eq(const lvec2<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lvec2<T>::__neq(const lvec2<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lvec2<T>::__lt(const lvec2<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lvec2<T>::__le(const lvec2<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lvec2<T>::__gt(const lvec2<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lvec2<T>::__ge(const lvec2<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lvec2<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lvec2::flag = []() -> int
{
    auto regist_ntr_lvec2_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lvec2::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lvec2::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lvec2::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lvec2::uname;
        }();

        ntr::nephren::type<lvec2<T>>(name)
            .function("__add", &lvec2<T>::__add)
            .function("__sub", &lvec2<T>::__sub)
            .function("__mul", &lvec2<T>::__mul)
            .function("__div", &lvec2<T>::__div)
            .function("__unm", &lvec2<T>::__unm)
            .function("__eq", &lvec2<T>::__eq)
            .function("__neq", &lvec2<T>::__neq)
            .function("__lt", &lvec2<T>::__lt)
            .function("__le", &lvec2<T>::__le)
            .function("__gt", &lvec2<T>::__gt)
            .function("__ge", &lvec2<T>::__ge)
            .function("__tostring", &lvec2<T>::__tostring)
            .property("x", &lvec2<T>::x)
            .property("y", &lvec2<T>::y);
    };

    regist_ntr_lvec2_lambda.template operator()<int>();
    regist_ntr_lvec2_lambda.template operator()<unsigned int>();
    regist_ntr_lvec2_lambda.template operator()<float>();
    regist_ntr_lvec2_lambda.template operator()<double>();

    return 1;
}();
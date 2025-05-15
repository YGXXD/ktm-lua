#include "lvec3.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lvec3<T> lvec3<T>::__add(const lvec3<T>& other)
{
    return lvec3<T> { value + other.value };
}

template <typename T>
lvec3<T> lvec3<T>::__sub(const lvec3<T>& other)
{
    return lvec3<T> { value - other.value };
}

template <typename T>
lvec3<T> lvec3<T>::__mul(const lvec3<T>& other)
{
    return lvec3<T> { value * other.value };
}

template <typename T>
lvec3<T> lvec3<T>::__div(const lvec3<T>& other)
{
    return lvec3<T> { value / other.value };
}

template <typename T>
lvec3<T> lvec3<T>::__unm()
{
    return lvec3<T> { -value };
}

template <typename T>
bool lvec3<T>::__eq(const lvec3<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lvec3<T>::__neq(const lvec3<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lvec3<T>::__lt(const lvec3<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lvec3<T>::__le(const lvec3<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lvec3<T>::__gt(const lvec3<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lvec3<T>::__ge(const lvec3<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lvec3<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lvec3::flag = []() -> int
{
    auto regist_ntr_lvec3_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lvec3::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lvec3::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lvec3::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lvec3::uname;
        }();

        ntr::nephren::type<lvec3<T>>(name)
            .function("__add", &lvec3<T>::__add)
            .function("__sub", &lvec3<T>::__sub)
            .function("__mul", &lvec3<T>::__mul)
            .function("__div", &lvec3<T>::__div)
            .function("__unm", &lvec3<T>::__unm)
            .function("__eq", &lvec3<T>::__eq)
            .function("__neq", &lvec3<T>::__neq)
            .function("__lt", &lvec3<T>::__lt)
            .function("__le", &lvec3<T>::__le)
            .function("__gt", &lvec3<T>::__gt)
            .function("__ge", &lvec3<T>::__ge)
            .function("__tostring", &lvec3<T>::__tostring)
            .property("x", &lvec3<T>::x)
            .property("y", &lvec3<T>::y)
            .property("z", &lvec3<T>::z);
    };

    regist_ntr_lvec3_lambda.template operator()<int>();
    regist_ntr_lvec3_lambda.template operator()<unsigned int>();
    regist_ntr_lvec3_lambda.template operator()<float>();
    regist_ntr_lvec3_lambda.template operator()<double>();

    return 1;
}();
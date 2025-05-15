#include "lmat2x3.hpp"
#include "lmat3x3.hpp"
#include "lmat3x2.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lmat2x3<T> lmat2x3<T>::__add(const lmat2x3<T>& other)
{
    return lmat2x3<T> { value + other.value };
}

template <typename T>
lmat2x3<T> lmat2x3<T>::__sub(const lmat2x3<T>& other)
{
    return lmat2x3<T> { value - other.value };
}

template <typename T>
lmat3x3<T> lmat2x3<T>::__mul(const lmat3x2<T>& other)
{
    return lmat3x3<T> { value * other.value };
}

template <typename T>
lmat2x3<T> lmat2x3<T>::__unm()
{
    return lmat2x3<T> { -value };
}

template <typename T>
bool lmat2x3<T>::__eq(const lmat2x3<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lmat2x3<T>::__neq(const lmat2x3<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lmat2x3<T>::__lt(const lmat2x3<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lmat2x3<T>::__le(const lmat2x3<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lmat2x3<T>::__gt(const lmat2x3<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lmat2x3<T>::__ge(const lmat2x3<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lmat2x3<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lmat2x3::flag = []() -> int
{
    auto regist_ntr_lmat2x3_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lmat2x3::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lmat2x3::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lmat2x3::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lmat2x3::uname;
        }();

        ntr::nephren::type<lmat2x3<T>>(name)
            .function("__add", &lmat2x3<T>::__add)
            .function("__sub", &lmat2x3<T>::__sub)
            .function("__mul", &lmat2x3<T>::__mul)
            .function("__unm", &lmat2x3<T>::__unm)
            .function("__eq", &lmat2x3<T>::__eq)
            .function("__neq", &lmat2x3<T>::__neq)
            .function("__lt", &lmat2x3<T>::__lt)
            .function("__le", &lmat2x3<T>::__le)
            .function("__gt", &lmat2x3<T>::__gt)
            .function("__ge", &lmat2x3<T>::__ge)
            .function("__tostring", &lmat2x3<T>::__tostring)
            .property("col1", &lmat2x3<T>::col1)
            .property("col2", &lmat2x3<T>::col2);
    };

    regist_ntr_lmat2x3_lambda.template operator()<int>();
    regist_ntr_lmat2x3_lambda.template operator()<unsigned int>();
    regist_ntr_lmat2x3_lambda.template operator()<float>();
    regist_ntr_lmat2x3_lambda.template operator()<double>();

    return 1;
}();
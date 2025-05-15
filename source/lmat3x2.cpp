#include "lmat3x2.hpp"
#include "lmat2x2.hpp"
#include "lmat2x3.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lmat3x2<T> lmat3x2<T>::__add(const lmat3x2<T>& other)
{
    return lmat3x2<T> { value + other.value };
}

template <typename T>
lmat3x2<T> lmat3x2<T>::__sub(const lmat3x2<T>& other)
{
    return lmat3x2<T> { value - other.value };
}

template <typename T>
lmat2x2<T> lmat3x2<T>::__mul(const lmat2x3<T>& other)
{
    return lmat2x2<T> { value * other.value };
}

template <typename T>
lmat3x2<T> lmat3x2<T>::__unm()
{
    return lmat3x2<T> { -value };
}

template <typename T>
bool lmat3x2<T>::__eq(const lmat3x2<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lmat3x2<T>::__neq(const lmat3x2<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lmat3x2<T>::__lt(const lmat3x2<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lmat3x2<T>::__le(const lmat3x2<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lmat3x2<T>::__gt(const lmat3x2<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lmat3x2<T>::__ge(const lmat3x2<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lmat3x2<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lmat3x2::flag = []() -> int
{
    auto regist_ntr_lmat3x2_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lmat3x2::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lmat3x2::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lmat3x2::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lmat3x2::uname;
        }();

        ntr::nephren::type<lmat3x2<T>>(name)
            .function("__add", &lmat3x2<T>::__add)
            .function("__sub", &lmat3x2<T>::__sub)
            .function("__mul", &lmat3x2<T>::__mul)
            .function("__unm", &lmat3x2<T>::__unm)
            .function("__eq", &lmat3x2<T>::__eq)
            .function("__neq", &lmat3x2<T>::__neq)
            .function("__lt", &lmat3x2<T>::__lt)
            .function("__le", &lmat3x2<T>::__le)
            .function("__gt", &lmat3x2<T>::__gt)
            .function("__ge", &lmat3x2<T>::__ge)
            .function("__tostring", &lmat3x2<T>::__tostring)
            .property("col1", &lmat3x2<T>::col1)
            .property("col2", &lmat3x2<T>::col2)
            .property("col3", &lmat3x2<T>::col3);
    };

    regist_ntr_lmat3x2_lambda.template operator()<int>();
    regist_ntr_lmat3x2_lambda.template operator()<unsigned int>();
    regist_ntr_lmat3x2_lambda.template operator()<float>();
    regist_ntr_lmat3x2_lambda.template operator()<double>();

    return 1;
}();
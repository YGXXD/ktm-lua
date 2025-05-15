#include "lmat4x4.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lmat4x4<T> lmat4x4<T>::__add(const lmat4x4<T>& other)
{
    return lmat4x4<T> { value + other.value };
}

template <typename T>
lmat4x4<T> lmat4x4<T>::__sub(const lmat4x4<T>& other)
{
    return lmat4x4<T> { value - other.value };
}

template <typename T>
lmat4x4<T> lmat4x4<T>::__mul(const lmat4x4<T>& other)
{
    return lmat4x4<T> { value * other.value };
}

template <typename T>
lmat4x4<T> lmat4x4<T>::__unm()
{
    return lmat4x4<T> { -value };
}

template <typename T>
bool lmat4x4<T>::__eq(const lmat4x4<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lmat4x4<T>::__neq(const lmat4x4<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lmat4x4<T>::__lt(const lmat4x4<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lmat4x4<T>::__le(const lmat4x4<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lmat4x4<T>::__gt(const lmat4x4<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lmat4x4<T>::__ge(const lmat4x4<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lmat4x4<T>::__tostring() const
{
    return value.to_string();
}

const int regist_lmat4x4::flag = []() -> int
{
    auto regist_ntr_lmat4x4_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lmat4x4::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lmat4x4::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lmat4x4::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lmat4x4::uname;
        }();

        ntr::nephren::type<lmat4x4<T>>(name)
            .function("__add", &lmat4x4<T>::__add)
            .function("__sub", &lmat4x4<T>::__sub)
            .function("__mul", &lmat4x4<T>::__mul)
            .function("__unm", &lmat4x4<T>::__unm)
            .function("__eq", &lmat4x4<T>::__eq)
            .function("__neq", &lmat4x4<T>::__neq)
            .function("__lt", &lmat4x4<T>::__lt)
            .function("__le", &lmat4x4<T>::__le)
            .function("__gt", &lmat4x4<T>::__gt)
            .function("__ge", &lmat4x4<T>::__ge)
            .function("__tostring", &lmat4x4<T>::__tostring)
            .property("col1", &lmat4x4<T>::col1)
            .property("col2", &lmat4x4<T>::col2)
            .property("col3", &lmat4x4<T>::col3)
            .property("col4", &lmat4x4<T>::col4);
    };

    regist_ntr_lmat4x4_lambda.template operator()<int>();
    regist_ntr_lmat4x4_lambda.template operator()<unsigned int>();
    regist_ntr_lmat4x4_lambda.template operator()<float>();
    regist_ntr_lmat4x4_lambda.template operator()<double>();

    return 1;
}();
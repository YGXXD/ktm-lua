#include "lmat3x3.hpp"
#include <ntr/nephren.hpp>

template <typename T>
lmat3x3<T> lmat3x3<T>::__add(const lmat3x3<T>& other)
{
    return lmat3x3<T> { value + other.value };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::__sub(const lmat3x3<T>& other)
{
    return lmat3x3<T> { value - other.value };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::__mul(const lmat3x3<T>& other)
{
    return lmat3x3<T> { value * other.value };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::__unm()
{
    return lmat3x3<T> { -value };
}

template <typename T>
bool lmat3x3<T>::__eq(const lmat3x3<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lmat3x3<T>::__neq(const lmat3x3<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lmat3x3<T>::__lt(const lmat3x3<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lmat3x3<T>::__le(const lmat3x3<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lmat3x3<T>::__gt(const lmat3x3<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lmat3x3<T>::__ge(const lmat3x3<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lmat3x3<T>::__tostring() const
{
    return value.to_string();
}

template <typename T>
lmat3x3<T> lmat3x3<T>::create(const lvec3<T>& col1, const lvec3<T>& col2, const lvec3<T>& col3)
{
    return lmat3x3<T> { ktm::mat<3, 3, T> { col1.value, col2.value, col3.value } };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::from_row(const lvec3<T>& row1, const lvec3<T>& row2, const lvec3<T>& row3)
{
    return lmat3x3<T> { ktm::mat<3, 3, T>::from_row(row1.value, row2.value, row3.value) };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::from_diag(const lvec3<T>& diag)
{
    return lmat3x3<T> { ktm::mat<3, 3, T>::from_diag(diag.value) };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::from_eye()
{
    return lmat3x3<T> { ktm::mat<3, 3, T>::from_eye() };
}

template <typename T>
lmat3x3<T> lmat3x3<T>::transpose(const lmat3x3& mat)
{
    return lmat3x3<T> { ktm::transpose(mat.value) };
}

template <typename T>
lvec3<T> lmat3x3<T>::diagonal(const lmat3x3& mat)
{
    return lvec3<T> { ktm::diagonal(mat.value) };
}

template <typename T>
T lmat3x3<T>::trace(const lmat3x3& mat)
{
    return ktm::trace(mat.value);
}

template <typename T>
T lmat3x3<T>::determinant(const lmat3x3& mat)
{
    return ktm::determinant(mat.value);
}

template <typename T, typename Void>
lmat3x3<T> lmat3x3_floating<T, Void>::inverse(const lmat3x3<T>& mat)
{
    return lmat3x3<T> { ktm::inverse(mat.value) };
}

const int regist_lmat3x3::flag = []() -> int
{
    auto regist_ntr_lmat3x3_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lmat3x3::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lmat3x3::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lmat3x3::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lmat3x3::uname;
        }();

        ntr::nephren::type<lmat3x3<T>>(name)
            .function("__add", &lmat3x3<T>::__add)
            .function("__sub", &lmat3x3<T>::__sub)
            .function("__mul", &lmat3x3<T>::__mul)
            .function("__unm", &lmat3x3<T>::__unm)
            .function("__eq", &lmat3x3<T>::__eq)
            .function("__neq", &lmat3x3<T>::__neq)
            .function("__lt", &lmat3x3<T>::__lt)
            .function("__le", &lmat3x3<T>::__le)
            .function("__gt", &lmat3x3<T>::__gt)
            .function("__ge", &lmat3x3<T>::__ge)
            .function("__tostring", &lmat3x3<T>::__tostring)
            .function("create", &lmat3x3<T>::create)
            .function("from_row", &lmat3x3<T>::from_row)
            .function("from_diag", &lmat3x3<T>::from_diag)
            .function("from_eye", &lmat3x3<T>::from_eye)
            .function("transpose", &lmat3x3<T>::transpose)
            .function("diagonal", &lmat3x3<T>::diagonal)
            .function("trace", &lmat3x3<T>::trace)
            .function("determinant", &lmat3x3<T>::determinant)
            .property("col1", &lmat3x3<T>::col1)
            .property("col2", &lmat3x3<T>::col2)
            .property("col3", &lmat3x3<T>::col3);

        if constexpr (std::is_floating_point_v<T>)
        {
            ntr::nephren::type<lmat3x3<T>>().function("inverse", &lmat3x3_floating<T, void>::inverse);
        }
    };
    regist_ntr_lmat3x3_lambda.template operator()<int>();
    regist_ntr_lmat3x3_lambda.template operator()<unsigned int>();
    regist_ntr_lmat3x3_lambda.template operator()<float>();
    regist_ntr_lmat3x3_lambda.template operator()<double>();

    return 1;
}();
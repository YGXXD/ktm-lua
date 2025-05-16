#include "lmat2x2.hpp"
#include "ntr/inc/nephren.hpp"

template <typename T>
lmat2x2<T> lmat2x2<T>::__add(const lmat2x2<T>& other)
{
    return lmat2x2<T> { value + other.value };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::__sub(const lmat2x2<T>& other)
{
    return lmat2x2<T> { value - other.value };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::__mul(const lmat2x2<T>& other)
{
    return lmat2x2<T> { value * other.value };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::__unm()
{
    return lmat2x2<T> { -value };
}

template <typename T>
bool lmat2x2<T>::__eq(const lmat2x2<T>& other)
{
    return value == other.value;
}

template <typename T>
bool lmat2x2<T>::__neq(const lmat2x2<T>& other)
{
    return value != other.value;
}

template <typename T>
bool lmat2x2<T>::__lt(const lmat2x2<T>& other)
{
    return value < other.value;
}

template <typename T>
bool lmat2x2<T>::__le(const lmat2x2<T>& other)
{
    return value <= other.value;
}

template <typename T>
bool lmat2x2<T>::__gt(const lmat2x2<T>& other)
{
    return value > other.value;
}

template <typename T>
bool lmat2x2<T>::__ge(const lmat2x2<T>& other)
{
    return value >= other.value;
}

template <typename T>
std::string lmat2x2<T>::__tostring() const
{
    return value.to_string();
}

template <typename T>
lmat2x2<T> lmat2x2<T>::create(const lvec2<T>& col1, const lvec2<T>& col2)
{
    return lmat2x2<T> { ktm::mat<2, 2, T> { col1.value, col2.value } };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::from_row(const lvec2<T>& row1, const lvec2<T>& row2)
{
    return lmat2x2<T> { ktm::mat<2, 2, T>::from_row(row1.value, row2.value) };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::from_diag(const lvec2<T>& diag)
{
    return lmat2x2<T> { ktm::mat<2, 2, T>::from_diag(diag.value) };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::from_eye()
{
    return lmat2x2<T> { ktm::mat<2, 2, T>::from_eye() };
}

template <typename T>
lmat2x2<T> lmat2x2<T>::transpose(const lmat2x2& mat)
{
    return lmat2x2<T> { ktm::transpose(mat.value) };
}

template <typename T>
lvec2<T> lmat2x2<T>::diagonal(const lmat2x2& mat)
{
    return lvec2<T> { ktm::diagonal(mat.value) };
}

template <typename T>
T lmat2x2<T>::trace(const lmat2x2& mat)
{
    return ktm::trace(mat.value);
}

template <typename T>
T lmat2x2<T>::determinant(const lmat2x2& mat)
{
    return ktm::determinant(mat.value);
}

template <typename T, typename Void>
lmat2x2<T> lmat2x2_floating<T, Void>::inverse(const lmat2x2<T>& mat)
{
    return lmat2x2<T> { ktm::inverse(mat.value) };
}

const int regist_lmat2x2::flag = []() -> int
{
    auto regist_ntr_lmat2x2_lambda = []<typename T>()
    {
        constexpr std::string_view name = []()
        {
            if constexpr (std::is_same_v<T, float>)
                return regist_lmat2x2::fname;
            else if constexpr (std::is_same_v<T, double>)
                return regist_lmat2x2::dname;
            else if constexpr (std::is_same_v<T, int>)
                return regist_lmat2x2::iname;
            else if constexpr (std::is_same_v<T, unsigned int>)
                return regist_lmat2x2::uname;
        }();

        ntr::nephren::type<lmat2x2<T>>(name)
            .function("__add", &lmat2x2<T>::__add)
            .function("__sub", &lmat2x2<T>::__sub)
            .function("__mul", &lmat2x2<T>::__mul)
            .function("__unm", &lmat2x2<T>::__unm)
            .function("__eq", &lmat2x2<T>::__eq)
            .function("__neq", &lmat2x2<T>::__neq)
            .function("__lt", &lmat2x2<T>::__lt)
            .function("__le", &lmat2x2<T>::__le)
            .function("__gt", &lmat2x2<T>::__gt)
            .function("__ge", &lmat2x2<T>::__ge)
            .function("__tostring", &lmat2x2<T>::__tostring)
            .function("create", &lmat2x2<T>::create)
            .function("from_row", &lmat2x2<T>::from_row)
            .function("from_diag", &lmat2x2<T>::from_diag)
            .function("from_eye", &lmat2x2<T>::from_eye)
            .function("transpose", &lmat2x2<T>::transpose)
            .function("diagonal", &lmat2x2<T>::diagonal)
            .function("trace", &lmat2x2<T>::trace)
            .function("determinant", &lmat2x2<T>::determinant)
            .property("col1", &lmat2x2<T>::col1)
            .property("col2", &lmat2x2<T>::col2);

        if constexpr (std::is_floating_point_v<T>)
        {
            ntr::nephren::type<lmat2x2<T>>().function("inverse", &lmat2x2_floating<T>::inverse);
        }
    };

    regist_ntr_lmat2x2_lambda.template operator()<int>();
    regist_ntr_lmat2x2_lambda.template operator()<unsigned int>();
    regist_ntr_lmat2x2_lambda.template operator()<float>();
    regist_ntr_lmat2x2_lambda.template operator()<double>();

    return 1;
}();
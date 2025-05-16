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

template <typename T>
lvec4<T> lvec4<T>::create(T x, T y, T z, T w)
{
    return lvec4<T> { ktm::vec<4, T> { x, y, z, w } };
}

template <typename T>
T lvec4<T>::reduce_add(const lvec4<T>& x)
{
    return ktm::reduce_add(x.value);
}

template <typename T>
T lvec4<T>::reduce_min(const lvec4<T>& x)
{
    return ktm::reduce_min(x.value);
}

template <typename T>
T lvec4<T>::reduce_max(const lvec4<T>& x)
{
    return ktm::reduce_max(x.value);
}

template <typename T>
lvec4<T> lvec4<T>::min(const lvec4<T>& x, const lvec4<T>& y)
{
    return lvec4<T> { ktm::min(x.value, y.value) };
}

template <typename T>
lvec4<T> lvec4<T>::max(const lvec4<T>& x, const lvec4<T>& y)
{
    return lvec4<T> { ktm::max(x.value, y.value) };
}

template <typename T>
lvec4<T> lvec4<T>::clamp(const lvec4<T>& x, const lvec4<T>& min, const lvec4<T>& max)
{
    return lvec4<T> { ktm::clamp(x.value, min.value, max.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_signed<T, Void>::abs(const lvec4<T>& x)
{
    return lvec4<T> { ktm::abs(x.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::floor(const lvec4<T>& x)
{
    return lvec4<T> { ktm::floor(x.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::ceil(const lvec4<T>& x)
{
    return lvec4<T> { ktm::ceil(x.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::round(const lvec4<T>& x)
{
    return lvec4<T> { ktm::round(x.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::fract(const lvec4<T>& x)
{
    return lvec4<T> { ktm::fract(x.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::mod(const lvec4<T>& x, const lvec4<T>& y)
{
    return lvec4<T> { ktm::mod(x.value, y.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::lerp(const lvec4<T>& x, const lvec4<T>& y, T t)
{
    return lvec4<T> { ktm::lerp(x.value, y.value, t) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::mix(const lvec4<T>& x, const lvec4<T>& y, const lvec4<T>& t)
{
    return lvec4<T> { ktm::mix(x.value, y.value, t.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::step(const lvec4<T>& edge, const lvec4<T>& x)
{
    return lvec4<T> { ktm::step(edge.value, x.value) };
}

template <typename T, typename Void>
lvec4<T> lvec4_floating<T, Void>::smoothstep(const lvec4<T>& edge0, const lvec4<T>& edge1, const lvec4<T>& x)
{
    return lvec4<T> { ktm::smoothstep(edge0.value, edge1.value, x.value) };
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
            .function("create", &lvec4<T>::create)
            .function("reduce_add", &lvec4<T>::reduce_add)
            .function("reduce_min", &lvec4<T>::reduce_min)
            .function("reduce_max", &lvec4<T>::reduce_max)
            .function("min", &lvec4<T>::min)
            .function("max", &lvec4<T>::max)
            .function("clamp", &lvec4<T>::clamp)
            .property("x", &lvec4<T>::x)
            .property("y", &lvec4<T>::y)
            .property("z", &lvec4<T>::z)
            .property("w", &lvec4<T>::w);

        if constexpr (std::is_signed_v<T>)
        {
            ntr::nephren::type<lvec4<T>>().function("abs", &lvec4_signed<T>::abs);
        }

        if constexpr (std::is_floating_point_v<T>)
        {
            ntr::nephren::type<lvec4<T>>()
                .function("floor", &lvec4_floating<T>::floor)
                .function("ceil", &lvec4_floating<T>::ceil)
                .function("round", &lvec4_floating<T>::round)
                .function("fract", &lvec4_floating<T>::fract)
                .function("mod", &lvec4_floating<T>::mod)
                .function("lerp", &lvec4_floating<T>::lerp)
                .function("mix", &lvec4_floating<T>::mix)
                .function("step", &lvec4_floating<T>::step)
                .function("smoothstep", &lvec4_floating<T>::smoothstep);
        }
    };

    regist_ntr_lvec4_lambda.template operator()<int>();
    regist_ntr_lvec4_lambda.template operator()<unsigned int>();
    regist_ntr_lvec4_lambda.template operator()<float>();
    regist_ntr_lvec4_lambda.template operator()<double>();

    return 1;
}();
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

template <typename T>
lvec3<T> lvec3<T>::create(T x, T y, T z)
{
    return lvec3<T> { ktm::vec<3, T> { x, y, z } };
}

template <typename T>
T lvec3<T>::reduce_add(const lvec3<T>& x)
{
    return ktm::reduce_add(x.value);
}

template <typename T>
T lvec3<T>::reduce_min(const lvec3<T>& x)
{
    return ktm::reduce_min(x.value);
}

template <typename T>
T lvec3<T>::reduce_max(const lvec3<T>& x)
{
    return ktm::reduce_max(x.value);
}

template <typename T>
lvec3<T> lvec3<T>::min(const lvec3<T>& x, const lvec3<T>& y)
{
    return lvec3<T> { ktm::min(x.value, y.value) };
}

template <typename T>
lvec3<T> lvec3<T>::max(const lvec3<T>& x, const lvec3<T>& y)
{
    return lvec3<T> { ktm::max(x.value, y.value) };
}

template <typename T>
lvec3<T> lvec3<T>::clamp(const lvec3<T>& x, const lvec3<T>& min, const lvec3<T>& max)
{
    return lvec3<T> { ktm::clamp(x.value, min.value, max.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_signed<T, Void>::abs(const lvec3<T>& x)
{
    return lvec3<T> { ktm::abs(x.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::floor(const lvec3<T>& x)
{
    return lvec3<T> { ktm::floor(x.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::ceil(const lvec3<T>& x)
{
    return lvec3<T> { ktm::ceil(x.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::round(const lvec3<T>& x)
{
    return lvec3<T> { ktm::round(x.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::fract(const lvec3<T>& x)
{
    return lvec3<T> { ktm::fract(x.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::mod(const lvec3<T>& x, const lvec3<T>& y)
{
    return lvec3<T> { ktm::mod(x.value, y.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::lerp(const lvec3<T>& x, const lvec3<T>& y, T t)
{
    return lvec3<T> { ktm::lerp(x.value, y.value, t) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::mix(const lvec3<T>& x, const lvec3<T>& y, const lvec3<T>& t)
{
    return lvec3<T> { ktm::mix(x.value, y.value, t.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::step(const lvec3<T>& edge, const lvec3<T>& x)
{
    return lvec3<T> { ktm::step(edge.value, x.value) };
}

template <typename T, typename Void>
lvec3<T> lvec3_floating<T, Void>::smoothstep(const lvec3<T>& edge0, const lvec3<T>& edge1, const lvec3<T>& x)
{
    return lvec3<T> { ktm::smoothstep(edge0.value, edge1.value, x.value) };
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
            .function("create", &lvec3<T>::create)
            .function("reduce_add", &lvec3<T>::reduce_add)
            .function("reduce_min", &lvec3<T>::reduce_min)
            .function("reduce_max", &lvec3<T>::reduce_max)
            .function("min", &lvec3<T>::min)
            .function("max", &lvec3<T>::max)
            .function("clamp", &lvec3<T>::clamp)
            .property("x", &lvec3<T>::x)
            .property("y", &lvec3<T>::y)
            .property("z", &lvec3<T>::z);

        if constexpr (std::is_signed_v<T>)
        {
            ntr::nephren::type<lvec3<T>>().function("abs", &lvec3_signed<T>::abs);
        }

        if constexpr (std::is_floating_point_v<T>)
        {
            ntr::nephren::type<lvec3<T>>()
                .function("floor", &lvec3_floating<T>::floor)
                .function("ceil", &lvec3_floating<T>::ceil)
                .function("round", &lvec3_floating<T>::round)
                .function("fract", &lvec3_floating<T>::fract)
                .function("mod", &lvec3_floating<T>::mod)
                .function("lerp", &lvec3_floating<T>::lerp)
                .function("mix", &lvec3_floating<T>::mix)
                .function("step", &lvec3_floating<T>::step)
                .function("smoothstep", &lvec3_floating<T>::smoothstep);
        }
    };

    regist_ntr_lvec3_lambda.template operator()<int>();
    regist_ntr_lvec3_lambda.template operator()<unsigned int>();
    regist_ntr_lvec3_lambda.template operator()<float>();
    regist_ntr_lvec3_lambda.template operator()<double>();

    return 1;
}();
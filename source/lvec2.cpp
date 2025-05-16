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

template <typename T>
lvec2<T> lvec2<T>::create(T x, T y)
{
    return lvec2<T> { ktm::vec<2, T> { x, y } };
}

template <typename T>
T lvec2<T>::reduce_add(const lvec2<T>& x)
{
    return ktm::reduce_add(x.value);
}

template <typename T>
T lvec2<T>::reduce_min(const lvec2<T>& x)
{
    return ktm::reduce_min(x.value);
}

template <typename T>
T lvec2<T>::reduce_max(const lvec2<T>& x)
{
    return ktm::reduce_max(x.value);
}

template <typename T>
lvec2<T> lvec2<T>::min(const lvec2<T>& x, const lvec2<T>& y)
{
    return lvec2<T> { ktm::min(x.value, y.value) };
}

template <typename T>
lvec2<T> lvec2<T>::max(const lvec2<T>& x, const lvec2<T>& y)
{
    return lvec2<T> { ktm::max(x.value, y.value) };
}

template <typename T>
lvec2<T> lvec2<T>::clamp(const lvec2<T>& x, const lvec2<T>& min, const lvec2<T>& max)
{
    return lvec2<T> { ktm::clamp(x.value, min.value, max.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_signed<T, Void>::abs(const lvec2<T>& x)
{
    return lvec2<T> { ktm::abs(x.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::floor(const lvec2<T>& x)
{
    return lvec2<T> { ktm::floor(x.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::ceil(const lvec2<T>& x)
{
    return lvec2<T> { ktm::ceil(x.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::round(const lvec2<T>& x)
{
    return lvec2<T> { ktm::round(x.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::fract(const lvec2<T>& x)
{
    return lvec2<T> { ktm::fract(x.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::mod(const lvec2<T>& x, const lvec2<T>& y)
{
    return lvec2<T> { ktm::mod(x.value, y.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::lerp(const lvec2<T>& x, const lvec2<T>& y, T t)
{
    return lvec2<T> { ktm::lerp(x.value, y.value, t) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::mix(const lvec2<T>& x, const lvec2<T>& y, const lvec2<T>& t)
{
    return lvec2<T> { ktm::mix(x.value, y.value, t.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::step(const lvec2<T>& edge, const lvec2<T>& x)
{
    return lvec2<T> { ktm::step(edge.value, x.value) };
}

template <typename T, typename Void>
lvec2<T> lvec2_floating<T, Void>::smoothstep(const lvec2<T>& edge0, const lvec2<T>& edge1, const lvec2<T>& x)
{
    return lvec2<T> { ktm::smoothstep(edge0.value, edge1.value, x.value) };
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
            .function("create", &lvec2<T>::create)
            .function("reduce_add", &lvec2<T>::reduce_add)
            .function("reduce_min", &lvec2<T>::reduce_min)
            .function("reduce_max", &lvec2<T>::reduce_max)
            .function("min", &lvec2<T>::min)
            .function("max", &lvec2<T>::max)
            .function("clamp", &lvec2<T>::clamp)
            .property("x", &lvec2<T>::x)
            .property("y", &lvec2<T>::y);

        if constexpr (std::is_signed_v<T>)
        {
            ntr::nephren::type<lvec2<T>>().function("abs", &lvec2_signed<T>::abs);
        }

        if constexpr (std::is_floating_point_v<T>)
        {
            ntr::nephren::type<lvec2<T>>()
                .function("floor", &lvec2_floating<T>::floor)
                .function("ceil", &lvec2_floating<T>::ceil)
                .function("round", &lvec2_floating<T>::round)
                .function("fract", &lvec2_floating<T>::fract)
                .function("mod", &lvec2_floating<T>::mod)
                .function("lerp", &lvec2_floating<T>::lerp)
                .function("mix", &lvec2_floating<T>::mix)
                .function("step", &lvec2_floating<T>::step)
                .function("smoothstep", &lvec2_floating<T>::smoothstep);
        }
    };

    regist_ntr_lvec2_lambda.template operator()<int>();
    regist_ntr_lvec2_lambda.template operator()<unsigned int>();
    regist_ntr_lvec2_lambda.template operator()<float>();
    regist_ntr_lvec2_lambda.template operator()<double>();

    return 1;
}();
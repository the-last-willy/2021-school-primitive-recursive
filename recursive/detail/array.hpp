#pragma once

#include <algorithm> // std::copy
#include <array> // std::array, std::begin, std::end
#include <span> // std::span, std::begin, std::end
#include <tuple> // std::tuple
#include <type_traits> // std::enable_if_t

namespace rec {
namespace detail {

template<
    typename Ty,
    std::size_t Ith = 0,
    typename... Args,
    std::enable_if_t<(Ith < sizeof...(Args)), int> = 0> constexpr
std::array<Ty, sizeof...(Args)> static_casted_as_array(
    const std::tuple<Args...>& t)
{
    auto a = static_casted_as_array<Ty, Ith + 1>(t);
    a[Ith] = static_cast<Ty>(std::get<Ith>(t));
    return a;
}

template<
    typename Ty,
    std::size_t Ith,
    typename... Args,
    std::enable_if_t<(Ith == sizeof...(Args)), int> = 0> constexpr
std::array<Ty, sizeof...(Args)> static_casted_as_array(
    const std::tuple<Args...>&)
{
    return {};
}

// Push

template<typename Ty, std::size_t N> constexpr
std::array<Ty, N + 1> pushed_back_as_array(
    std::span<const Ty, N> s, const Ty& e)
{
    auto a = std::array<Ty, N + 1>{};
    std::copy(std::begin(s), std::end(s), std::begin(a));
    a.back() = e;
    return a;
}

template<typename Ty, std::size_t N> constexpr
std::array<Ty, N + 1> pushed_front_as_array(
    std::span<const Ty, N> s, const Ty& e)
{
    auto a = std::array<Ty, N + 1>{e};
    std::copy(std::begin(s), std::end(s), std::begin(a) + 1);
    return a;
}

} // namespace detail
} // namespace rec

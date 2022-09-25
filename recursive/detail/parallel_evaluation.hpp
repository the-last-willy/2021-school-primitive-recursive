#pragma once

#include <recursive/detail/arity.hpp> // rec::arity
#include <recursive/aliases.hpp> // rec::arr, rec::span

#include <tuple> // std::tuple
#include <type_traits> // std::enable_if_t

namespace rec {
namespace detail {

template<
    std::size_t Ith = 0,
    typename... Fs,
    std::size_t Arity,
    std::enable_if_t<(Ith < sizeof...(Fs)), int> = 0> constexpr
arr<sizeof...(Fs)> parallel_evaluation_as_array(
    const std::tuple<Fs...>& fs, span<Arity> input)
{
    auto e = parallel_evaluation_as_array<Ith + 1>(fs, input);
    e[Ith] = std::get<Ith>(fs)(input)[0];
    return e;
}

template<
    std::size_t Ith,
    typename... Fs,
    std::size_t Arity,
    std::enable_if_t<(Ith == sizeof...(Fs)), int> = 0> constexpr
arr<sizeof...(Fs)> parallel_evaluation_as_array(
    const std::tuple<Fs...>&, span<Arity>)
{
    return {};
}

} // namespace detail
} // namespace rec

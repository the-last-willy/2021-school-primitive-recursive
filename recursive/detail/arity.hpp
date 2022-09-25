#pragma once

#include <recursive/aliases.hpp> // rec::span

#include <type_traits> // std::integral_constant

namespace rec {
namespace detail {

// Credits to 'https://stackoverflow.com/questions/27866909/get-function-arity-from-template-parameter/27867127#27867127'.

template<typename... Args>
struct arity {};

// Helper variable template 
template<typename... Args>
constexpr auto arity_v = arity<Args...>::value;

template<typename Ty, typename... Args>
struct arity<Ty, Args...> : std::integral_constant<std::size_t, arity_v<Ty>> {
    static_assert(arity_v<Ty> == arity_v<Args...>,
        "arity<Args...>: Arity is not constant through parameter pack or is not defined for one of the parameters.");
};

template<typename Ty>
struct arity<Ty> : arity<decltype(&Ty::operator())> {};

template<typename Ty>
struct arity<Ty&> : arity<decltype(&Ty::operator())> {};

// Specializations for functions

template<typename R, std::size_t Arity>
struct arity<R(span<Arity>)>
: std::integral_constant<std::size_t, Arity> {};

template<typename R, std::size_t Arity>
struct arity<R(&)(span<Arity>)>
: std::integral_constant<std::size_t, Arity> {};

template<typename R, std::size_t Arity>
struct arity<R(*)(span<Arity>)>
: std::integral_constant<std::size_t, Arity> {};

template<typename R, std::size_t Arity>
struct arity<R(*const)(span<Arity>)>
: std::integral_constant<std::size_t, Arity> {};

template<typename R, std::size_t Arity>
struct arity<R(*const&)(span<Arity>)>
: std::integral_constant<std::size_t, Arity> {};

// Specializations for lambda functions

template<typename R, typename C, std::size_t Arity>
struct arity<R(C::*)(span<Arity>)>
: std::integral_constant<std::size_t, Arity> {};

template<typename R, typename C, std::size_t Arity>
struct arity<R(C::*)(span<Arity>) const>
: std::integral_constant<std::size_t, Arity> {};

} // namespace detail
} // namespace rec

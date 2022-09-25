#pragma once

#include <recursive/detail/arity.hpp> // rec::detail::arity_v
#include <recursive/detail/array.hpp> // rec::detail::static_casted_as_array
#include <recursive/aliases.hpp> // rec::arr

#include <tuple> // std::make_tuple
#include <utility> // std::forward

// Provides a handy facility to evaluate recursive constructions.

namespace rec {

template<typename F, typename... Args> constexpr
nat eval(const F& f, Args&&... args) {
    static_assert(detail::arity_v<F> == sizeof...(Args),
        "eval<F, ...Args>: Argument count must be equal to function arity.");
    return f(detail::static_casted_as_array<nat>(
        std::make_tuple(std::forward<Args>(args)...)))[0];
}

} // namespace rec

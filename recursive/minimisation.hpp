#pragma once

#include <recursive/detail/arity.hpp> // rec::detail::arity_v
#include <recursive/detail/array.hpp> // rec::detail::pushed_front
#include <recursive/aliases.hpp> // rec::span

#include <algorithm> // std::copy

namespace rec {

// Minimisation.
// Takes a function of arity n + 1.
// Returns a function of arity n.
template<typename G> constexpr
auto Min(const G& g) {
    static_assert(detail::arity_v<G> > 0);
    return [=](span<detail::arity_v<G> - 1> input) -> arr<1> {
        auto g_input = detail::pushed_front_as_array(input, nat{0});
        while(g(g_input)[0] != 0) ++g_input[0];
        return {g_input[0]};
    };
}

} // namespace rec

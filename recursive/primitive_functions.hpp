#pragma once

#include <recursive/detail/array.hpp> // std::array, rec::detail::pushed_back, rec::detail::pushed_front
#include <recursive/detail/parallel_evaluation.hpp> // detail::parallel_evaluation
#include <recursive/detail/span.hpp> // std::span, rec::detail::popped_back, rec::detail::popped_front
#include <recursive/aliases.hpp> // rec::arr, rec::nat, rec::span

#include <tuple> // std::make_tuple

namespace rec {

// Constant function.
template<std::size_t Arity> constexpr
arr<1> O(span<Arity>) {
    return {0};
}

// Successor function.
constexpr
arr<1> S(span<1> s) {
    return {s[0] + 1};
}

// Projection function
// Mathematician indexing [1, n]
template<std::size_t Ith, std::size_t Arity> constexpr
arr<1> Pi(span<Arity> s) {
    static_assert(Ith > 0 && Ith <= Arity,
        "Pi<Ith, Arity>: Template parameter Ith must belong to [1, Arity].");
    return {s[Ith - 1]};
}

namespace detail {

template<typename F, typename... Gs> constexpr
auto unchecked_Comp(const F& f, Gs&&... gs) {
    // Capture by copy to avoid dangling references.
    // Had to write 'f = f' otherwise constexpr would fail on MSVC (?).
    return [f = f, gs = std::make_tuple(std::forward<Gs>(gs)...)]
        (span<detail::arity_v<Gs...>> input) constexpr -> arr<1>
    {
        return {f(detail::parallel_evaluation_as_array(gs, input))};
    };
}

} // namespace detail

// Composition
template<typename F, typename... Gs> constexpr
auto Comp(const F& f, Gs&&... gs) {
    static_assert(detail::arity_v<F> == sizeof...(Gs),
        "Comp<F, ...Gs>: Arity of f must be equal to the number of gs.");
    return detail::unchecked_Comp(f, std::forward<Gs>(gs)...);
}

namespace detail {

template<typename B, typename H> constexpr
auto unchecked_Rec(const B& b, const H& h) {
    return [b = b, h = h](span<detail::arity_v<B> + 1> input) -> arr<1> {
        auto h_input = detail::pushed_back_as_array(
            input, b(detail::popped_front(input))[0]);
        for(h_input[0] = 0; h_input[0] < input[0]; ++h_input[0]) {
            h_input.back() = h(h_input)[0];
        }
        return {h_input.back()};
    };
}

} // namespace detail

// Recursion
// Performances could be improved by lazy evaluating reccurence term.
template<typename B, typename H> constexpr
auto Rec(const B& b, const H& h) {
    static_assert(detail::arity_v<B> + 2 == detail::arity_v<H>,
        "Rec<B, H>: Incoherent arity of parameters. 'arity of h' must be equal to 'arity of b + 2'.");
    return detail::unchecked_Rec(b, h);
}

} // namespace rec

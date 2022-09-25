#pragma once

#include <span> // std::span

namespace rec {
namespace detail {

// Valid only for fixed size 'std::span'.

// Pop

template<typename Ty, std::size_t N> constexpr
std::span<Ty, N - 1> popped_back(std::span<Ty, N> s) {
    return s.subspan<0, N - 1>();
}

template<typename Ty, std::size_t N> constexpr
std::span<Ty, N - 1> popped_front(std::span<Ty, N> s) {
    return s.subspan<1>();
}

} // namespace detail
} // namespace rec

#pragma once

#include <array> // std::array
#include <cstdlib> // std::size_t
#include <span> // std::span

namespace rec {

using nat = std::size_t;

template<std::size_t Size>
using arr = std::array<nat, Size>;

template<std::size_t Size>
using span = std::span<const nat, Size>;

} // namespace rec

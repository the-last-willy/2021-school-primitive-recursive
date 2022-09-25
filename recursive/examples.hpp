#pragma once

#include <recursive/primitive.hpp>

namespace rec {

// Defining N-ary constant in terms of 0-ary constant - for reference.
constexpr auto O1 = Rec(O<0>, Pi<2, 2>);
constexpr auto O2 = Rec(O1, Pi<3, 3>);
constexpr auto O3 = Rec(O2, Pi<4, 4>);
// ...

// Defining identity in terms of unary projection.
constexpr auto I = Pi<1, 1>;

// Natural to boolean conversion.
constexpr auto B = Rec(O<0>, Comp(Comp(S, O<1>), Pi<1, 2>));

// N-ary true constant.
template<std::size_t Arity>
constexpr auto T = Comp(S, O<Arity>);

// N-ary false constant.
template<std::size_t Arity>
constexpr auto F = O<Arity>;

// Basic boolean algebra operations.

constexpr auto And = Rec(F<1>, Pi<2, 3>);

constexpr auto Or = Rec(I, T<3>);

constexpr auto Not = Rec(T<0>, F<2>);

// Secondary boolean algebra operations.

constexpr auto Xor = Rec(I, Comp(Not, Pi<2, 3>));

constexpr auto Impli = Rec(T<1>, Pi<2, 3>);

constexpr auto Equiv = Rec(Not, Pi<2, 3>);

// N-ary natural constants.

template<std::size_t Arity>
constexpr auto One = Comp(S, O<Arity>);

template<std::size_t Arity>
constexpr auto Two = Comp(S, One<Arity>);

template<std::size_t Arity>
constexpr auto Three = Comp(S, Two<Arity>);

// Basic arithmetic.

// Predecessor.
constexpr auto P = Rec(O<0>, Pi<1, 2>);

constexpr auto Sum = Rec(Pi<1, 1>, Comp(S, Pi<3, 3>));

// Truncated difference.
constexpr auto TDiff = Comp(Rec(Pi<1, 1>, Comp(P, Pi<3, 3>)), Pi<2, 2>, Pi<1, 2>);

// Absolute difference.
constexpr auto AbsDiff = Comp(Sum, TDiff, Comp(TDiff, Pi<2, 2>, Pi<1, 2>));

constexpr auto Prod = Rec(O<1>, Comp(Sum, Pi<2, 3>, Pi<3, 3>));

constexpr auto Fact = Rec(One<0>, Comp(Prod, Comp(S, Pi<1, 2>), Pi<2, 2>));

constexpr auto Pow = Comp(Rec(One<1>, Comp(Prod, Pi<2, 3>, Pi<3, 3>)), Pi<2, 2>, Pi<1, 2>);

// Comparisons.

constexpr auto Eq = Comp(Not, AbsDiff);

// Branching.

constexpr auto If = Rec(Pi<2, 2>, Pi<2, 4>);

// Modular arithmetic.

constexpr auto Mod = Rec(O<1>, Comp(If, Comp(Eq, Comp(S, Pi<3, 3>), Pi<2, 3>), O<3>, Comp(S, Pi<3, 3>)));

constexpr auto Div = Comp(Not, Mod);

// Primality.

constexpr auto Prim = Comp(Eq, Comp(S, Comp(Rec(O<1>, Comp(Sum, Comp(Div, Pi<2, 3>, Pi<1, 3>), Pi<3, 3>)), I, I)), Two<1>);

} // namespace rec

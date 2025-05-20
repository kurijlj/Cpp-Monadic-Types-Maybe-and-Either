// ============================================================================
// Provides an implementation of the Maybe monad for robust presence handling.
//  Copyright (C) 2025 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This file is part of Cpp-Monadic-Types.
// 
// Cpp-Monadic-Types is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software  Foundation, either version 3 of the License, or (at your option)
// any later version.
// 
// Cpp-Monadic-Types is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// Cpp-Monadic-Types. If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// 2025-05-20 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * Maybe.h: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Headers Include Section
// ============================================================================

// Standard library headers
#include <functional>
#include <optional>
#include <stdexcept> // For std::runtime_error
#include <utility>   // For std::forward

// ============================================================================
// Implementation Section
// ============================================================================

/** ---------------------------------------------------------------------------
 * @brief Represents a value that may or may not be present.
 *
 * This type is an alias for `std::optional<T>`, serving as a monadic
 * container similar to `Maybe` in functional programming languages. It allows
 * for computations to proceed only if a value is present, elegantly handling
 * the absence of a value without resorting to null pointers or exceptions.
 *
 * @tparam T The type of the value that may or may not be present.
 * -------------------------------------------------------------------------- */
template <typename T>
using Maybe = std::optional<T>;

/** ---------------------------------------------------------------------------
 * @brief Monadic bind operation for the `Maybe` type.
 *
 * This function applies a transformation function `f` to the value contained
 * within a `Maybe` object, but only if the `Maybe` object actually holds
 * a value.
 *
 * If the input `Maybe` \p mb contains a value, `f` is invoked with that value,
 * and its result (which must be another `Maybe<R>`) is returned.
 * If the input `Maybe` \p mb is empty, `f` is not invoked, and an empty
 * `Maybe<R>` is returned, effectively propagating the "nothing" state.
 * This structure allows for chaining operations that might fail or
 * yield no result.
 *
 * @tparam T The type of the value held by the input `Maybe`.
 * @tparam F The type of the function to apply. `F` must be callable with a `T`
 * and must return a `Maybe<R>` for some type `R`.
 * @tparam R The type of the value held by the resulting `Maybe` (i.e., the
 * `value_type` of the `Maybe` returned by `F`). This type is
 * automatically deduced.
 * @param mb A constant reference to the input `Maybe` object.
 * @param f The function to apply to the contained value if present.
 * @return A `Maybe<R>` representing the result of applying `f` if `mb`
 * contained a value, otherwise an empty `Maybe<R>`.
 *
 * @note This `mbind` implementation strictly enforces that the function `f`
 * must return another `Maybe` (i.e., an `std::optional<U>`). Attempting to
 * chain a function that returns a raw value (`U` instead of `Maybe<U>`) will
 * result in a compilation error.
 * -------------------------------------------------------------------------- */
template <
	typename T,
	typename F,
	typename R = typename std::invoke_result_t<F, T>::value_type
>
auto mbind(const Maybe<T>& mb, F f) -> Maybe<R> {
  if (mb) {
    return std::invoke(f, mb.value());    
  } else {
    return {};    
  }
}

/** ---------------------------------------------------------------------------
 * @brief Pipe operator for monadic chaining on the `Maybe` type.
 *
 * This operator provides a fluent and idiomatic syntax for chaining
 * `mbind` operations, allowing for a more readable functional style.
 * It passes an rvalue reference to a `Maybe` object to a function `f`
 * using the pipe syntax (`maybe_obj | some_function`).
 *
 * @tparam T The type of the value held by the input `Maybe`.
 * @tparam F The type of the function to apply. `F` must be callable with a `T`
 * and must return a `Maybe<U>` for some type `U`.
 * @param e An rvalue reference to the input `Maybe` object. This allows for
 * efficient moving of the `Maybe` through the chain.
 * @param f An rvalue reference to the function to apply.
 * @return The result of the `mbind` operation, which is a `Maybe<U>`. The
 * specific type `U` is automatically deduced based on the return type of `f`.
 *
 * @note This operator uses perfect forwarding to handle both lvalue and rvalue
 * `Maybe` objects and functions efficiently.
 * -------------------------------------------------------------------------- */
template <typename T, typename F>
auto operator|(Maybe<T>&& e, F&& f) {
  return mbind<T, F>(std::forward<Maybe<T>>(e), std::forward<F>(f));
}

// End of 'Maybe.h'
// ============================================================================
// Provides an implementation of the Either monad for robust error handling.
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
// 2025-05-13 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * Either.h: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Headers Include Section
// ============================================================================

// Standard library headers
#include <functional>
#include <stdexcept> // For std::runtime_error
#include <utility>   // For std::forward
#include <variant>

// ============================================================================
// Implementation Section
// ============================================================================

/** ---------------------------------------------------------------------------
 * @brief Defines a common error type for the Either monad.
 * -------------------------------------------------------------------------- */
using Err = std::runtime_error;

/** ---------------------------------------------------------------------------
 * @brief Represents a value that can be either a successful value of type T
 * or an error of type Err.
 *
 * This type is similar to Result in Rust or Maybe/Either in functional
 * programming, providing a way to handle computations that might fail without
 * relying on exceptions for control flow.
 *
 * @tparam T The type representing the successful value.
 * -------------------------------------------------------------------------- */
template <typename T>
using Either = std::variant<T, Err>;

/** ---------------------------------------------------------------------------
 * @brief Functor to check if an Either variant holds the successful (right)
 * value of type T.
 *
 * This functor can be used with std::visit to determine if an Either object
 * contains a value of type T (returns true) or an error of type Err (returns
 * false).
 *
 * @tparam T The successful value type of the Either.
 * -------------------------------------------------------------------------- */
template <typename T>
struct IsRight {
  /** -------------------------------------------------------------------------
   * @brief Checks if the variant holds a successful value.
   * @param t A constant reference to the successful value.
   * @return true, indicating the Either holds a successful value.
   * ------------------------------------------------------------------------ */
  bool operator()(const T& t) const {
    return true;
  }

  /** -------------------------------------------------------------------------
   * @brief Checks if the variant holds an error.
   * @param err A constant reference to the error value.
   * @return false, indicating the Either does not hold a successful value.
   * ------------------------------------------------------------------------ */
  bool operator()(const Err& err) const {
    return false;
  }
};

/** ---------------------------------------------------------------------------
 * @brief Functor to check if an Either variant holds an error (left) value of
 * type Err.
 *
 * This functor can be used with std::visit to determine if an Either object
 * contains a value of type T (returns false) or an error of type Err (returns
 * true).
 *
 * @tparam T The successful value type of the Either.
 * @tparam Err The error type of the Either.
 * -------------------------------------------------------------------------- */
template <typename T>
struct IsLeft {
  /** -------------------------------------------------------------------------
   * @brief Checks if the variant holds a successful value.
   * @param t A constant reference to the successful value.
   * @return false, indicating the Either holds a successful value.
   * ------------------------------------------------------------------------ */
  bool operator()(const T& t) const {
    return false;
  }

  /** -------------------------------------------------------------------------
   * @brief Checks if the variant holds an error.
   * @param err A constant reference to the error value.
   * @return true, indicating the Either does not hold a successful value.
   * ------------------------------------------------------------------------ */
  bool operator()(const Err& err) const {
    return true;
  }
};

/** ---------------------------------------------------------------------------
 * @brief Monadic bind operation for the Either monad.
 *
 * If the input Either \p e holds a successful value of type T, this function
 * applies the function \p f to that value. The function \p f is expected to
 * take a \p T and return an \c Either of type \p R. If \p e holds an error,
 * the error is propagated through wrapped in an \c Either of type \p R. This
 * allows for chaining computations that might fail.
 *
 * @tparam T The successful value type of the input Either.
 * @tparam F The type of the function to apply to the successful value. This
 * function should take a \p T and return an \c Either of type \p R.
 * @tparam R The successful value type of the resulting Either. This type is
 * deduced as the first alternative type of the \c Either returned by \p f.
 * @param e A constant reference to the input Either.
 * @param f The function to apply to the successful value.
 * @return An \c Either of type \p R representing the result of applying \p f
 * if \p e was successful, or the original error wrapped in \c Either<\p R>
 * otherwise.
 *
 * @note This implementation expects the function \p f to return an \c Either
 * to maintain the monadic chain. The successful type \p R is deduced from the
 * return type of \p f.
 * -------------------------------------------------------------------------- */
template <
  typename T,
  typename F,
  typename R
    = typename std::variant_alternative_t<0, std::invoke_result_t<F, T>>
>
auto mbind(const Either<T>& e, F f)
  -> Either<R> {
  // Check if the Either holds an error (is left).
  if (std::visit(IsLeft<T>(), e)) {
    // If it's an error, propagate the error by wrapping it in an Either<R>.
    return Either<R>(std::get<Err>(e));
  }

  // with it, returning the resulting Either<R>.
  return std::invoke(f, std::get<T>(e));
}

/** ---------------------------------------------------------------------------
 * @brief Pipe operator for monadic bind on the Either monad.
 *
 * This operator provides a more fluent syntax for chaining \c mbind operations.
 * It allows you to pass an \c Either object to a function \p f (that performs a
 * monadic bind) using the pipe syntax (\p e | \p f).
 *
 * @tparam T The successful value type of the Either.
 * @tparam F The type of the function to apply (a function that takes an
 * \c Either<T> and returns an \c Either<U> for some type U). The successful
 * type \c U will be deduced by the \c mbind function.
 * @param e An rvalue reference to the Either object.
 * @param f An rvalue reference to the function to apply.
 * @return The result of the \c mbind operation: \c Either<U>.
 *
 * @note This operator uses perfect forwarding to handle both lvalue and rvalue
 * \c Either objects and functions efficiently.
 * -------------------------------------------------------------------------- */
template <typename T, typename F>
auto operator|(Either<T>&& e, F&& f) {
  // Forward the Either and the function to the mbind function. The return
  // type of mbind will deduce the 'R' in its signature.
  using R = typename std::variant_alternative_t<0, std::invoke_result_t<F, T>>;
  return mbind<T, F>(std::forward<Either<T>>(e), std::forward<F>(f));
}

// End of 'Either.h'
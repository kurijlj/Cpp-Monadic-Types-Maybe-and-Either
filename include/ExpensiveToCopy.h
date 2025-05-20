// ============================================================================
// Provides an custom type for the testing of the monadic types implementation.
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
// * ExpensiveToCopy.h: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Headers Include Section
// ============================================================================

// Project headers
#include "Either.h"
#include "Maybe.h"

// Standard library headers
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// Implementation Section
// ============================================================================

/** ---------------------------------------------------------------------------
 * @brief A class designed to be expensive to copy, used for demonstrating
 * move semantics with Maybe and Either monads.
 *
 * This class contains a large `std::vector` to simulate significant memory
 * overhead during copy operations. Its constructors, destructors, and
 * assignment operators track calls using a static counter, `count`,
 * allowing verification of move vs. copy operations in monadic chains.
 * -------------------------------------------------------------------------- */
struct ExpensiveToCopy {
  /** -------------------------------------------------------------------------
   * @brief Static counter to track the number of active ExpensiveToCopy
   * instances.
   * This helps in verifying proper object lifecycle and move semantics.
   * ------------------------------------------------------------------------ */
  static int count;

  /** -------------------------------------------------------------------------
   * @brief Unique identifier for each instance of ExpensiveToCopy.
   * ------------------------------------------------------------------------ */
  int id;

  /** -------------------------------------------------------------------------
   * @brief A large vector to simulate significant memory allocation,
   * making copy operations expensive.
   * ------------------------------------------------------------------------ */
  std::vector<int> data{1000, 0};


  /** -------------------------------------------------------------------------
   * @brief Default constructor for ExpensiveToCopy.
   * Increments the static count and assigns a unique ID.
   * ------------------------------------------------------------------------ */
  ExpensiveToCopy();

  /** -------------------------------------------------------------------------
   * @brief Destructor for ExpensiveToCopy.
   * ------------------------------------------------------------------------ */
  ~ExpensiveToCopy();

  /** -------------------------------------------------------------------------
   * @brief Copy constructor for ExpensiveToCopy.
   * Increments the static count and copies data from another instance.
   * @param other The ExpensiveToCopy object to copy from.
   * ------------------------------------------------------------------------ */
  ExpensiveToCopy(const ExpensiveToCopy&);

  /** -------------------------------------------------------------------------
   * @brief Move constructor for ExpensiveToCopy.
   * Efficiently moves resources from a temporary object.
   * Does not increment the static count, as it's a transfer of ownership.
   * @param other The ExpensiveToCopy rvalue object to move from.
   * ------------------------------------------------------------------------ */
  ExpensiveToCopy(ExpensiveToCopy&&) noexcept;

  /** -------------------------------------------------------------------------
   * @brief Copy assignment operator for ExpensiveToCopy.
   * Handles self-assignment and copies data.
   * @param other The ExpensiveToCopy object to copy from.
   * @return A reference to the current object.
   * ------------------------------------------------------------------------ */
  ExpensiveToCopy& operator=(const ExpensiveToCopy&);

  /** -------------------------------------------------------------------------
   * @brief Move assignment operator for ExpensiveToCopy.
   * Efficiently moves resources from a temporary object.
   * @param other The ExpensiveToCopy rvalue object to move from.
   * @return A reference to the current object.
   * ------------------------------------------------------------------------ */
  ExpensiveToCopy& operator=(ExpensiveToCopy&&) noexcept;


  /** -------------------------------------------------------------------------
   * @brief Overloads the stream insertion operator for ExpensiveToCopy.
   * Allows printing ExpensiveToCopy objects to an output stream.
   * @param os The output stream.
   * @param obj The ExpensiveToCopy object to print.
   * @return A reference to the output stream.
   * ------------------------------------------------------------------------ */
  friend std::ostream& operator<<(
    std::ostream& os,
    const ExpensiveToCopy& obj
  );
};

/** ---------------------------------------------------------------------------
 * @brief Utility function to print the value contained within a Maybe monad.
 *
 * If the Maybe object contains a value, it prints the value to `std::cout`.
 * If the Maybe object is empty, it prints "No value".
 *
 * @tparam T The type of the value that the Maybe object may contain.
 * @param mb A constant reference to the Maybe object to print.
 * -------------------------------------------------------------------------- */
template<typename T>
void print_maybe(const Maybe<T>& mb) {
  if (mb) {
    // If Maybe has a value, print it.
    std::cout << mb.value() << "\n";
  } else {
    // If Maybe is empty, print "No value".
    std::cout << "No value\n";
  }
};

/** ---------------------------------------------------------------------------
 * @brief A visitor functor for printing the content of an Either monad.
 *
 * This functor is designed to be used with `std::visit` on an `Either` object.
 * It provides overloaded `operator()` for both the `Err` (error) type and
 * the successful value `T`, printing the relevant content to `std::cout`.
 *
 * @tparam T The successful value type of the Either monad.
 * -------------------------------------------------------------------------- */
template <typename T>
struct PrintResult {
  /** -------------------------------------------------------------------------
   * @brief Overload for visiting the error (Err) state of an Either.
   * @param err The constant reference to the error object.
   * ------------------------------------------------------------------------ */
  void operator()(const Err& err) {
    std::cout << err.what() << "\n";
  }

  /** -------------------------------------------------------------------------
   * @brief Overload for visiting the successful (T) state of an Either.
   * @param val The constant reference to the successful value.
   * ------------------------------------------------------------------------ */
  void operator()(const T& val) {
    std::cout << val << "\n";
  }
};

/** ---------------------------------------------------------------------------
 * @brief A custom error class inheriting from `Err` (std::runtime_error),
 * used to indicate a failure during creation of ExpensiveToCopy.
 * -------------------------------------------------------------------------- */
class FailedToCreate : public Err {
public:
  /** -------------------------------------------------------------------------
   * @brief Constructs a FailedToCreate error with a predefined message.
   * ------------------------------------------------------------------------ */
  explicit FailedToCreate() : Err{"Failed to create 'ExpensiveToCopy'"} { };
};


/** ---------------------------------------------------------------------------
 * @brief Creates an `ExpensiveToCopy` object wrapped in a `Maybe` monad.
 *
 * This function simulates an operation that might fail to produce an object.
 *
 * @param success A boolean flag; if true, an `ExpensiveToCopy` object is
 * created and returned in a `Maybe`. If false, an empty `Maybe` is returned.
 * @return A `Maybe<ExpensiveToCopy>` containing a new instance if `success` is
 * true, otherwise an empty `Maybe`.
 * -------------------------------------------------------------------------- */
Maybe<ExpensiveToCopy> create_expensive_m(bool);

/** ---------------------------------------------------------------------------
 * @brief Creates an `ExpensiveToCopy` object wrapped in an `Either` monad.
 *
 * This function simulates an operation that might either succeed or produce
 * an error.
 *
 * @param success A boolean flag; if true, an `ExpensiveToCopy` object is
 * created and returned in an `Either` as a success. If false, a
 * `FailedToCreate` error is returned in the `Either`.
 * @return An `Either<ExpensiveToCopy>` containing a new instance on success,
 * or a `FailedToCreate` error on failure.
 * -------------------------------------------------------------------------- */
Either<ExpensiveToCopy> create_expensive_e(bool);

/** ---------------------------------------------------------------------------
 * @brief Transforms an `ExpensiveToCopy` object, returning it wrapped in a
 * `Maybe` monad.
 *
 * This function takes an existing `ExpensiveToCopy` object (by const reference
 * to avoid implicit copies) and returns a new `ExpensiveToCopy` object
 * (simulating a transformation) wrapped in a `Maybe`. This serves as a step in
 * a monadic chain for `Maybe`.
 *
 * @param obj A constant reference to the `ExpensiveToCopy` object to transform.
 * @return A `Maybe<ExpensiveToCopy>` containing a newly constructed object.
 * -------------------------------------------------------------------------- */
Maybe<ExpensiveToCopy> transform_expensive_m(const ExpensiveToCopy&);

/** ---------------------------------------------------------------------------
 * @brief Transforms an `ExpensiveToCopy` object, returning it wrapped in an
 * `Either` monad.
 *
 * This function takes an existing `ExpensiveToCopy` object (by const
 * reference) and returns a new `ExpensiveToCopy` object wrapped in an `Either`
 * as a success. This serves as a step in a monadic chain for `Either`.
 *
 * @param obj A constant reference to the `ExpensiveToCopy` object to transform.
 * @return An `Either<ExpensiveToCopy>` containing a newly constructed object
 * as success.
 * -------------------------------------------------------------------------- */
Either<ExpensiveToCopy> transform_expensive_e(const ExpensiveToCopy&);

/** ---------------------------------------------------------------------------
 * @brief Accumulates data from an `ExpensiveToCopy` object, returning an `int`
 * wrapped in a `Maybe` monad.
 *
 * This function takes an `ExpensiveToCopy` object and extracts an integer
 * result from it. This represents a final step in a `Maybe` chain where the
 * result is no longer an `ExpensiveToCopy` object but a simpler value.
 *
 * @param obj A constant reference to the `ExpensiveToCopy` object to
 * accumulate from.
 * @return A `Maybe<int>` containing the accumulated integer result.
 * -------------------------------------------------------------------------- */
Maybe<int> accumulate_expensive_m(const ExpensiveToCopy&);

/** ---------------------------------------------------------------------------
 * @brief Accumulates data from an `ExpensiveToCopy` object, returning an
 * `int` wrapped in an `Either` monad.
 *
 * This function takes an `ExpensiveToCopy` object and extracts an integer
 * result from it. This represents a final step in an `Either` chain where the
 * result is no longer an `ExpensiveToCopy` object but a simpler value.
 *
 * @param obj A constant reference to the `ExpensiveToCopy` object to
 * accumulate from.
 * @return An `Either<int>` containing the accumulated integer result
 * as success.
 * -------------------------------------------------------------------------- */
Either<int> accumulate_expensive_e(const ExpensiveToCopy&);

// End of 'ExpensiveToCopy.h'
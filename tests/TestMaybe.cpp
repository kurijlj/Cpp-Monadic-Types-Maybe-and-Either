// ============================================================================
// Unit tests for the Maybe monad implementation using GoogleTest.
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
// * TestMaybe.h: created.
//
// ============================================================================

// ============================================================================
// Headers include section
// ============================================================================

// Test source
#include "Maybe.h" // Include the header file for the Maybe monad

// Standard library headers
#include <cmath> // Include for mathematical functions like std::sqrt

// External libraries headers
#include <gtest/gtest.h>  // GoogleTest framework for unit testing


// ============================================================================
// Test fixtures section
// ============================================================================

// A function that multiplies an integer by one and returns it wrapped in
// an Maybe.
auto multiplyOne(int a) -> Maybe<int> {
  // std::cout << "1 * " << a << "\n";
  return 1 * a;
}

// A function that calculates the modulo 42 of an integer and returns it
// wrapped in an Maybe. Returns an std::nullopt if the input is zero.
auto modulo(int a) -> Maybe<int> {
  if (0 == a) {
		// Return an Maybe containing the std::nullopt
    return {};
  }

  // std::cout << "42 % " << a << "\n";
  return 42 % a; // Return the result wrapped in an Either
}

// A function that calculates the square root of an integer and returns it
// wrapped in an Maybe<float>. Returns the std::nullopt if the input
// is negative.
auto squareRoot(int a) -> Maybe<float> {
  if (0 > a) {
		// Return an Maybe containing the std::nullopt
    return {};
  }

  // std::cout << "sqrt(" << a << ")\n";

  // Return the square root wrapped in an Maybe
  return std::sqrt(static_cast<float>(a));
}


// Test fixture class 'MaybeTest' that inherits from testing::Test.
// This allows setting up common objects and state for multiple test cases.
class MaybeTest : public testing::Test {
protected:
  // Create Maybe instances with different states for testing.

  Maybe<int> negative{-42};         // Maybe holding a negative integer
                                    // (valid state, has a value)
  Maybe<int> zero{0};               // Maybe holding zero (valid state,
	                                  // has a value)
  Maybe<int> valid{42};             // Maybe holding a positive integer
	                                  // (valid state, has a value)
  Maybe<int> invalid{std::nullopt}; // Maybe explicitly holding no value
	                                  // (empty state)
};


// ============================================================================
// Test cases section
// ============================================================================

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------
//
// Description: Tests the correct initialization of Maybe instances, verifying
//              that values are stored correctly and that an empty Maybe
//              is recognized as such.
//
// ----------------------------------------------------------------------------
TEST_F(MaybeTest, Initialization) {
	// Assert that the 'negative' Maybe holds the expected value.
  EXPECT_EQ(-42, negative.value());
	// Assert that the 'zero' Maybe holds the expected value.
  EXPECT_EQ(0, zero.value());
	// Assert that the 'valid' Maybe holds the expected value.
  EXPECT_EQ(42, valid.value());
	// Assert that the 'invalid' Maybe is empty (does not hold a value).
  EXPECT_FALSE(invalid);
}

// ----------------------------------------------------------------------------
// Monadic Bind
// ----------------------------------------------------------------------------
//
// Description: Tests the monadic bind ('mbind') operation directly. It verifies
//              that the provided function is applied only to 'Maybe' instances
//              that contain a value, and that 'empty' Maybe instances
//              propagate their empty state. It also checks the correctness of
//              the resulting values or empty states.
//
// ----------------------------------------------------------------------------
TEST_F(MaybeTest, MonadicBind) {
	// Apply 'multiplyOne' to 'negative'. Expected: Maybe<-42>.
    auto r1 = mbind(negative, multiplyOne);
    // Apply 'modulo' to 'negative'. Expected: Maybe<0> (42 % -42 is 0).
    auto r2 = mbind(negative, modulo);
    // Apply 'squareRoot' to 'negative'. Expected: Maybe<float> {} (sqrt of negative fails).
    auto r3 = mbind(negative, squareRoot);
    // Apply 'multiplyOne' to 'zero'. Expected: Maybe<0>.
    auto r4 = mbind(zero, multiplyOne);
    // Apply 'modulo' to 'zero'. Expected: Maybe<int> {} (modulo by zero fails).
    auto r5 = mbind(zero, modulo);
    // Apply 'squareRoot' to 'zero'. Expected: Maybe<0.0f>.
    auto r6 = mbind(zero, squareRoot);
    // Apply 'multiplyOne' to 'valid'. Expected: Maybe<42>.
    auto r7 = mbind(valid, multiplyOne);
    // Apply 'modulo' to 'valid'. Expected: Maybe<0> (42 % 42 is 0).
    auto r8 = mbind(valid, modulo);
    // Apply 'squareRoot' to 'valid'. Expected: Maybe<sqrt(42.0f)>.
    auto r9 = mbind(valid, squareRoot);
    // Apply 'multiplyOne' to 'invalid'. Expected: Maybe<int> {} (propagates empty state).
    auto r10 = mbind(invalid, multiplyOne);
    // Apply 'modulo' to 'invalid'. Expected: Maybe<int> {} (propagates empty state).
    auto r11 = mbind(invalid, modulo);
    // Apply 'squareRoot' to 'invalid'. Expected: Maybe<float> {} (propagates empty state).
    auto r12 = mbind(invalid, squareRoot);

    // Verify presence/absence of values in the results.
    EXPECT_TRUE(r1);  // Should have a value
    EXPECT_TRUE(r2);  // Should have a value
    EXPECT_FALSE(r3); // Should be empty (sqrt negative)
    EXPECT_TRUE(r4);  // Should have a value
    EXPECT_FALSE(r5); // Should be empty (modulo by zero)
    EXPECT_TRUE(r6);  // Should have a value
    EXPECT_TRUE(r7);  // Should have a value
    EXPECT_TRUE(r8);  // Should have a value
    EXPECT_TRUE(r9);  // Should have a value
    EXPECT_FALSE(r10); // Should be empty (propagated from invalid)
    EXPECT_FALSE(r11); // Should be empty (propagated from invalid)
    EXPECT_FALSE(r12); // Should be empty (propagated from invalid)

    // Check the actual values after binding.
    EXPECT_EQ(-42, r1.value());
    EXPECT_EQ(0, r2.value());
    // Expect std::bad_optional_access exception when calling value() on
		// an empty Maybe.
    EXPECT_THROW(r3.value(), std::bad_optional_access);
    EXPECT_EQ(0, r4.value());
    // Expect std::bad_optional_access exception when calling value() on
		// an empty Maybe.
    EXPECT_THROW(r5.value(), std::bad_optional_access);
    EXPECT_EQ(0, r6.value());
    EXPECT_EQ(42, r7.value());
    EXPECT_EQ(0, r8.value());
    // Use a small epsilon for floating-point comparisons to account for
		// precision differences.
    EXPECT_LT(std::abs(std::sqrt(42.0f) - r9.value()), 0.00001f);
    // Expect std::bad_optional_access exception when calling value() on
		// an empty Maybe.
    EXPECT_THROW(r10.value(), std::bad_optional_access);
    // Expect std::bad_optional_access exception when calling value() on
		// an empty Maybe.
    EXPECT_THROW(r11.value(), std::bad_optional_access);
    // Expect std::bad_optional_access exception when calling value() on
		// an empty Maybe.
    EXPECT_THROW(r12.value(), std::bad_optional_access);
}

// ----------------------------------------------------------------------------
// Pipe Operator
// ----------------------------------------------------------------------------
//
// Description: Tests the pipe operator ('|') for monadic chaining of Maybe
//              operations. It verifies that functions are applied sequentially
//              to valid values and that an 'empty' state is propagated
//              correctly through the chain.
//
// ----------------------------------------------------------------------------
TEST_F(MaybeTest, PipeOperator) {
  // Chain operations on a negative Maybe: multiplyOne -> modulo -> squareRoot.
  // Calculation: (-42 * 1) -> -42. Then (42 % -42) -> 0. Then sqrt(0) -> 0.0.
  auto r1 = std::forward<decltype(negative)>(negative)
    | multiplyOne
    | modulo
    | squareRoot;
  // Chain operations on a zero Maybe: multiplyOne -> modulo -> squareRoot.
  // Calculation: (0 * 1) -> 0. Then modulo(0) fails -> empty Maybe.
	// Chain stops.
  auto r2 = std::forward<decltype(zero)>(zero)
    | multiplyOne
    | modulo
    | squareRoot;
  // Chain operations on a valid Maybe: multiplyOne -> modulo -> squareRoot.
  // Calculation: (42 * 1) -> 42. Then (42 % 42) -> 0. Then sqrt(0) -> 0.0.
  auto r3 = std::forward<decltype(valid)>(valid)
    | multiplyOne
    | modulo
    | squareRoot;
  // Chain operations on a negative Maybe: multiplyOne -> squareRoot.
  // Calculation: (-42 * 1) -> -42. Then squareRoot(-42) fails -> empty Maybe.
	// Chain stops.
  auto r4 = std::forward<decltype(negative)>(negative)
    | multiplyOne
    | squareRoot;
  // Chain operations on an initially invalid Maybe:
	// multiplyOne -> modulo -> squareRoot.
  // Expected: The initial empty state will be propagated immediately;
	// no functions applied.
  auto r5 = std::forward<decltype(invalid)>(invalid)
    | multiplyOne
    | modulo
    | squareRoot;

  // Check the final result of the chained operations on an
	// initially negative value.
  EXPECT_TRUE(r1);
  EXPECT_EQ(0.0f, r1.value()); // Use float literal for comparison

  // Check the final result of the chained operations on zero (expecting
	// empty due to modulo).
  EXPECT_FALSE(r2);
  // Expect std::bad_optional_access exception when calling value() on
	// an empty Maybe.
  EXPECT_THROW(r2.value(), std::bad_optional_access);

  // Check the final result of the chained operations on a valid initial value.
  EXPECT_TRUE(r3);
  EXPECT_EQ(0.0f, r3.value());

  // Check the final result of the chained operations on a negative value
	// for square root (expecting empty).
  EXPECT_FALSE(r4);
  // Expect std::bad_optional_access exception when calling value() on
	// an empty Maybe.
  EXPECT_THROW(r4.value(), std::bad_optional_access);

  // Check the final result of the chained operations on an initially
	// invalid value (expecting empty).
  EXPECT_FALSE(r5);
  // Expect std::bad_optional_access exception when calling value() on
	// an empty Maybe.
  EXPECT_THROW(r5.value(), std::bad_optional_access);
}

// End of 'TestMaybe.cpp'
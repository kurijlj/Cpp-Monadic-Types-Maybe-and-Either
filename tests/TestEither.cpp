// ============================================================================
// Unit tests for the Either monad implementation using GoogleTest.
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
// 2025-05-19 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * TestEither.h: created.
//
// ============================================================================

// ============================================================================
// Headers include section
// ============================================================================

// Test source
#include "Either.h" // Include the header file for the Either monad

// Standard library headers
#include <cmath> // Include for mathematical functions like std::sqrt

// External libraries headers
#include <gtest/gtest.h>  // GoogleTest framework for unit testing


// ============================================================================
// Test fixtures section
// ============================================================================

// Proper error class subclassed from the Err (i.e. std::runtime_error)
class InvalidInitErr : public Err {
public:
  explicit InvalidInitErr() : Err{"Invalid initialization"} {};
};

// Invalid error class not subclassed from the Err
class InvalidErrType {};

class DivisionByZeroErr : public Err {
public:
  explicit DivisionByZeroErr() : Err{"Division by zero"} {};
};

class SqrtNegativeErr : public Err {
public:
  explicit SqrtNegativeErr() : Err{"Trying to square root negative integer"} {};
};

// A function that multiplies an integer by one and returns it wrapped in an Either.
auto multiplyOne(int a) -> Either<int> {
  // std::cout << "1 * " << a << "\n";
  return 1 * a;
}

// A function that calculates the modulo 42 of an integer and returns it
// wrapped in an Either. Returns an error if the input is zero.
auto modulo(int a) -> Either<int> {
  if (0 == a) {
		// Return an Either containing the division by zero error
    return DivisionByZeroErr{};
  }

  // std::cout << "42 % " << a << "\n";
  return 42 % a; // Return the result wrapped in an Either
}

// A function that calculates the square root of an integer and returns it
// wrapped in an Either<float>. Returns an error if the input is negative.
auto squareRoot(int a) -> Either<float> {
  if (0 > a) {
		// Return an Either containing the square root negative error
    return SqrtNegativeErr{};
  }

  // std::cout << "sqrt(" << a << ")\n";

  // Return the square root wrapped in an Either
  return std::sqrt(static_cast<float>(a));
}


// Test fixture class 'EitherTest' that inherits from testing::Test.
// This allows setting up common objects and state for multiple test cases.
class EitherTest : public testing::Test {
protected:
  // Create Either instances with different states for testing.
  Either<int> negative{-42}; // Either holding a negative integer (Right)
  Either<int> zero{0};    // Either holding zero (Right)
  Either<int> valid{42};   // Either holding a positive integer (Right)
  Either<int> invalid{InvalidInitErr{}}; // Either holding an error (Left)
  // Following line throws the following compiler error:
  //   - no matching constructor for initialization of 'Either<int>'
  // so the type safety should be ensured
  // Either<int> invalid_type{InvalidErrType{}};
  // This commented-out line demonstrates that the Either type enforces
  // that you can only construct it with either the successful type (int)
  // or the defined error type (Err, which is std::runtime_error or a subclass).
  // Attempting to initialize it with an unrelated type (InvalidErrType) fails
  // at compile time, ensuring type safety.
};


// ============================================================================
// Test cases section
// ============================================================================

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------
//
// Description: Tests the correct initialization of Either instances in both
//              the Right (successful value) and Left (error) states.
//
// ----------------------------------------------------------------------------
TEST_F(EitherTest, Initialization) {
  // Check if the 'negative' Either holds a Right (int) value.
  EXPECT_TRUE(std::visit(IsRight<int>(), negative));
  // Check if the 'zero' Either holds a Right (int) value.
  EXPECT_TRUE(std::visit(IsRight<int>(), zero));
  // Check if the 'valid' Either holds a Right (int) value.
  EXPECT_TRUE(std::visit(IsRight<int>(), valid));
  // Check if the 'invalid' Either holds a Left (Err) value.
  EXPECT_FALSE(std::visit(IsRight<int>(), invalid));
  // Check if the 'invalid' Either holds a Left (Err) value.
  EXPECT_TRUE(std::visit(IsLeft<int>(), invalid));
  // Check if the 'negative' Either does NOT hold a Left (Err) value.
  EXPECT_FALSE(std::visit(IsLeft<int>(), negative));
  // Check if the 'zero' Either does NOT hold a Left (Err) value.
  EXPECT_FALSE(std::visit(IsLeft<int>(), zero));
  // Check if the 'valid' Either does NOT hold a Left (Err) value.
  EXPECT_FALSE(std::visit(IsLeft<int>(), valid));
  // Check if the 'negative' Either holds the expected integer value.
  EXPECT_EQ(-42, std::get<int>(negative));
  // Check if the 'zero' Either holds the expected integer value.
  EXPECT_EQ(0, std::get<int>(zero));
  // Check if the 'valid' Either holds the expected integer value.
  EXPECT_EQ(42, std::get<int>(valid));
  // Check if the 'invalid' Either holds the expected error message.
  EXPECT_STREQ("Invalid initialization", std::get<Err>(invalid).what());
}

// ----------------------------------------------------------------------------
// Monadic Bind
// ----------------------------------------------------------------------------
//
// Description: Tests the monadic bind ('mbind') operation. It verifies that
//              the provided function is applied to Right values and that Left
//              values are propagated through without applying the function.
//
// ----------------------------------------------------------------------------
TEST_F(EitherTest, MonadicBind) {
  // Apply 'multiplyOne' to a negative Either. The function should be applied.
  auto r1 = mbind(negative, multiplyOne);
  // Apply 'modulo' to a negative Either. The function should be applied.
  auto r2 = mbind(negative, modulo);
  // Apply 'squareRoot' to a negative Either. The function should be applied,
  // and it's expected to return an error.
  auto r3 = mbind(negative, squareRoot);
  // Apply 'multiplyOne' to a zero Either. The function should be applied.
  auto r4 = mbind(zero, multiplyOne);
  // Apply 'modulo' to a zero Either. The function should be applied,
  // and it's expected to return a division by zero error.
  auto r5 = mbind(zero, modulo);
  // Apply 'squareRoot' to a zero Either. The function should be applied.
  auto r6 = mbind(zero, squareRoot);
  // Apply 'multiplyOne' to a valid Either. The function should be applied.
  auto r7 = mbind(valid, multiplyOne);
  // Apply 'modulo' to a valid Either. The function should be applied.
  auto r8 = mbind(valid, modulo);
  // Apply 'squareRoot' to a valid Either. The function should be applied.
  auto r9 = mbind(valid, squareRoot);
  // Apply 'multiplyOne' to an invalid Either. The function should
	// NOT be applied.
  auto r10 = mbind(invalid, multiplyOne);
  // Apply 'modulo' to an invalid Either. The function should NOT be applied.
  auto r11 = mbind(invalid, modulo);
  // Apply 'squareRoot' to an invalid Either. The function should
	// NOT be applied.
  auto r12 = mbind(invalid, squareRoot);

  // Check that the result of binding with a negative value is Right.
  EXPECT_TRUE(std::visit(IsRight<int>(), r1));
  // Check that the result of binding with a negative value is Right.
  EXPECT_TRUE(std::visit(IsRight<int>(), r2));
  // Check that the result of binding with a negative value for square root
	// is Left (float).
  EXPECT_FALSE(std::visit(IsRight<float>(), r3));
  // Check that the result of binding with zero is Right.
  EXPECT_TRUE(std::visit(IsRight<int>(), r4));
  // Check that the result of binding with zero for modulo is Left (int).
  EXPECT_FALSE(std::visit(IsRight<int>(), r5));
  // Check that the result of binding with zero for square root
	// is Right (float).
  EXPECT_TRUE(std::visit(IsRight<float>(), r6));
  // Check that the result of binding with a valid value is Right.
  EXPECT_TRUE(std::visit(IsRight<int>(), r7));
  // Check that the result of binding with a valid value is Right.
  EXPECT_TRUE(std::visit(IsRight<int>(), r8));
  // Check that the result of binding with a valid value for square root
	// is Right (float).
  EXPECT_TRUE(std::visit(IsRight<float>(), r9));
  // Check that binding with an invalid value results in Left.
  EXPECT_FALSE(std::visit(IsRight<int>(), r10));
  // Check that binding with an invalid value results in Left.
  EXPECT_FALSE(std::visit(IsRight<int>(), r11));
  // Check that binding with an invalid value results in Left (float).
  EXPECT_FALSE(std::visit(IsRight<float>(), r12));

  // Check the actual values after binding.
  EXPECT_EQ(std::get<int>(negative), std::get<int>(r1));
  EXPECT_EQ(0, std::get<int>(r2));
  // Check the error message for the square root of a negative number.
  EXPECT_STREQ(
    "Trying to square root negative integer",
    std::get<Err>(r3).what()
  );
}

// ----------------------------------------------------------------------------
// Pipe Operator
// ----------------------------------------------------------------------------
//
// Description: Tests the pipe operator ('|') for monadic chaining of Either
//        operations. It verifies that functions are applied sequentially
//        to Right values and that errors are propagated correctly.
//
// ----------------------------------------------------------------------------
TEST_F(EitherTest, PipeOperator) {
  // Chain operations on a negative Either: multiplyOne -> modulo -> squareRoot.
  // Expected: sqrt(42 % (1 * -42)) => sqrt(42 % -42) => sqrt(0) => 0.
  auto r1 = std::forward<decltype(negative)>(negative)
    | multiplyOne
    | modulo
    | squareRoot;
  // Chain operations on a zero Either: multiplyOne -> modulo -> squareRoot.
  // Expected: modulo(0) will return a DivisionByZeroErr.
  auto r2 = std::forward<decltype(zero)>(zero)
    | multiplyOne
    | modulo
    | squareRoot;
  // Chain operations on a valid Either: multiplyOne -> modulo -> squareRoot.
  // Expected: sqrt(42 % (1 * 42)) => sqrt(42 % 42) => sqrt(0) => 0.
  auto r3 = std::forward<decltype(valid)>(valid)
    | multiplyOne
    | modulo
    | squareRoot;
  // Chain operations on a negative Either: multiplyOne -> squareRoot.
  // Expected: squareRoot(-42) will return a SqrtNegativeErr.
  auto r4 = std::forward<decltype(negative)>(negative)
    | multiplyOne
    | squareRoot;
  // Chain operations on an invalid Either: multiplyOne -> modulo -> squareRoot.
  // Expected: The initial error will be propagated.
  auto r5 = std::forward<decltype(invalid)>(invalid)
    | multiplyOne
    | modulo
    | squareRoot;

  // Check the final result of the chained operations on a negative value.
  EXPECT_TRUE(std::visit(IsRight<float>(), r1));
  EXPECT_EQ(0.0, std::get<float>(r1));
  // Check the final result of the chained operations on zero
	// (expecting an error).
  EXPECT_FALSE(std::visit(IsRight<float>(), r2));
  EXPECT_STREQ(
    "Division by zero",
    std::get<Err>(r2).what()
  );
  // Check the final result of the chained operations on a valid value.
  EXPECT_TRUE(std::visit(IsRight<float>(), r3));
  EXPECT_EQ(0.0, std::get<float>(r3));
  // Check the final result of the chained operations on a negative value for
	// square root (expecting an error).
  EXPECT_FALSE(std::visit(IsRight<float>(), r4));
  EXPECT_STREQ(
    "Trying to square root negative integer",
    std::get<Err>(r4).what()
  );
  // Check the final result of the chained operations on an invalid
	// initial value (expecting the initial error).
  EXPECT_FALSE(std::visit(IsRight<float>(), r5));
  EXPECT_STREQ(
    "Invalid initialization",
    std::get<Err>(r5).what()
  );
}

// End of 'TestEither.cpp'
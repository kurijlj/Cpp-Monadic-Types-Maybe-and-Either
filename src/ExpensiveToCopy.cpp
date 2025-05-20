// ============================================================================
// Provides an implementation for the `ExpensiveToCopy` custom type.
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
// * ExpensiveToCopy.cpp: created.
//
// ============================================================================

// ============================================================================
// Headers Include Section
// ============================================================================

// Related header
#include "ExpensiveToCopy.h"

int ExpensiveToCopy::count = 0;

ExpensiveToCopy::ExpensiveToCopy()
{
  count++;
  id = count;
  std::cout << "ExpensiveToCopy[" << id <<"]: Constructed ...\n";
}

ExpensiveToCopy::~ExpensiveToCopy()
{
  std::cout << "ExpensiveToCopy[" << id << "]: Destroyed ...\n";
}

ExpensiveToCopy::ExpensiveToCopy(const ExpensiveToCopy& other)
{
  for (int i = 0; i < 1000; ++i) this->data[i] = 1;
  count++;
  id = count;
  std::cout << "ExpensiveToCopy[" << id << "]: Copy constructed ...\n";
}

ExpensiveToCopy::ExpensiveToCopy(ExpensiveToCopy&& other) noexcept
{
  count++;
  id = count;
  std::cout << "ExpensiveToCopy[" << id << "]: Moved ...\n";
}

ExpensiveToCopy& ExpensiveToCopy::operator=(const ExpensiveToCopy&)
{
  for (int i = 0; i < 1000; ++i) data[i] = 2;
  count++;
  id = count;
  std::cout << "ExpensiveToCopy[" << id << "]: Copy assigned ...\n";
  return *this;
}

ExpensiveToCopy& ExpensiveToCopy::operator=(ExpensiveToCopy&& other) noexcept
{
  count++;
  id = count;
  std::cout << "ExpensiveToCopy[" << id << "]: Move assigned ...\n";
  return *this;
}

Maybe<ExpensiveToCopy> create_expensive_m(bool success)
{
  if (success) {
    return ExpensiveToCopy{};
  } else {
    return std::nullopt;
  }
}

Either<ExpensiveToCopy> create_expensive_e(bool success)
{
  if (success) {
    return ExpensiveToCopy{};
  } else {
    return FailedToCreate{};
  }
}

Maybe<ExpensiveToCopy> transform_expensive_m(const ExpensiveToCopy& other)
{
  std::cout << "Transforming ExpensiveToCopy[" << other.id << "]\n";
  ExpensiveToCopy ec{};
  for (auto& e : ec.data) e = 3;
  return std::move(ec);
}

Either<ExpensiveToCopy> transform_expensive_e(const ExpensiveToCopy& other)
{
  std::cout << "Transforming ExpensiveToCopy[" << other.id << "]\n";
  ExpensiveToCopy ec{};
  for (auto& e : ec.data) e = 3;
  return std::move(ec);
}

Maybe<int> accumulate_expensive_m(const ExpensiveToCopy& ec)
{
  std::cout << "Accumulating ExpensiveToCopy[" << ec.id << "]\n";
  return 42;
}

Either<int> accumulate_expensive_e(const ExpensiveToCopy& ec)
{
  std::cout << "Accumulating ExpensiveToCopy[" << ec.id << "]\n";
  return 42;
}

std::ostream& operator<<(std::ostream& os, const ExpensiveToCopy& obj) {
  os << "ExpensiveToCopy[" << obj.id <<"]\n";
  return os;
}

// End of 'ExpensiveToCopy.cpp'
// ============================================================================
// Demo app implementation definition.
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
// * MaybeEitherDemoImplementation.cpp: created.
//
// ============================================================================

// ============================================================================
// Headers Include Section
// ============================================================================

// Project library headers
#include "ExpensiveToCopy.h"
#include "Either.h"
#include "MaybeEitherDemoImplementation.h"

#include <variant>

// ============================================================================
// Class Implementation Section
// ============================================================================

int
MaybeEitherDemoImplementation::operator()(
  MainProgramAction const& action,
  std::string_view const& exec_name
) const
{
  std::cout << exec_name << ": Maybe type demo: \n";
  std::cout
    << exec_name
    << ": Using mbind directly with a temporary rvalue ...\n";
  auto result1 = mbind<ExpensiveToCopy, decltype(accumulate_expensive_m)>(
    std::forward<Maybe<ExpensiveToCopy>>(create_expensive_m(false)), 
    accumulate_expensive_m
  );
  std::cout << exec_name << ": ";
  print_maybe<int>(result1);
  std::cout << "\n";

  std::cout
    << exec_name
    << ": Using mbind directly with a named lvalue ...\n";
  auto expensive_maybe = create_expensive_m(true);
  auto result2 = mbind(expensive_maybe, accumulate_expensive_m);
  std::cout << exec_name << ": ";
  print_maybe<int>(result2);
  std::cout << "\n";

  std::cout
    << exec_name
    << ": Using the pipe operator with a temporary rvalue ...\n";
  auto result3 = create_expensive_m(true) | accumulate_expensive_m;
  std::cout << exec_name << ": ";
  print_maybe<int>(result3);
  std::cout << "\n";

  std::cout
    << exec_name
    << ": Using the pipe operator with a named lvalue ...\n";
  auto expensive_maybe_pipe = create_expensive_m(true);
  auto result4
    = std::forward<Maybe<ExpensiveToCopy>>(expensive_maybe_pipe)
    | accumulate_expensive_m;
  std::cout << exec_name << ": ";
  print_maybe<int>(result4);
  std::cout << "\n";

  std::cout << exec_name << ": Chaining operations to an error value ...\n";
  auto result5 =
    create_expensive_m(false)
    | transform_expensive_m
    | accumulate_expensive_m;
  std::cout << exec_name << ": ";
  print_maybe<int>(result5);
  std::cout << "\n";

  std::cout << exec_name << ": Chaining operations to an valid value ...\n";
  auto result6 =
    create_expensive_m(true)
    | transform_expensive_m
    | accumulate_expensive_m;
  std::cout << exec_name << ": ";
  print_maybe<int>(result6);
  std::cout << "\n";

  std::cout << exec_name << ": Either type demo: \n";
  std::cout
    << exec_name
    << ": Using mbind directly with a temporary rvalue ...\n";
  auto result7 = mbind<ExpensiveToCopy, decltype(accumulate_expensive_e)>(
    std::forward<Either<ExpensiveToCopy>>(create_expensive_e(false)), 
    accumulate_expensive_e
  );
  std::cout << exec_name << ": ";
  std::visit(PrintResult<int>(), result7);
  std::cout << "\n";

  std::cout
    << exec_name
    << ": Using mbind directly with a named lvalue ...\n";
  auto expensive_either = create_expensive_e(true);
  auto result8 = mbind(expensive_either, accumulate_expensive_e);
  std::cout << exec_name << ": ";
  std::visit(PrintResult<int>(), result8);
  std::cout << "\n";

  std::cout
    << exec_name
    << ": Using the pipe operator with a temporary rvalue ...\n";
  auto result9 = create_expensive_e(true) | accumulate_expensive_e;
  std::cout << exec_name << ": ";
  std::visit(PrintResult<int>(), result9);
  std::cout << "\n";

  std::cout
    << exec_name
    << ": Using the pipe operator with a named lvalue ...\n";
  auto expensive_either_pipe = create_expensive_e(true);
  auto result10
    = std::forward<Either<ExpensiveToCopy>>(expensive_either_pipe)
    | accumulate_expensive_e;
  std::cout << exec_name << ": ";
  std::visit(PrintResult<int>(), result10);
  std::cout << "\n";

  std::cout << exec_name << ": Chaining operations to an error value ...\n";
  auto result11 =
    create_expensive_e(false)
    | transform_expensive_e
    | accumulate_expensive_e;
  std::cout << exec_name << ": ";
  std::visit(PrintResult<int>(), result11);
  std::cout << "\n";

  std::cout << exec_name << ": Chaining operations to an valid value ...\n";
  auto result12 =
    create_expensive_e(true)
    | transform_expensive_e
    | accumulate_expensive_e;
  std::cout << exec_name << ": ";
  std::visit(PrintResult<int>(), result12);
  std::cout << "\n";

  return EXIT_SUCCESS;
}

// End of 'MaybeEitherDemoImplementation.cpp'
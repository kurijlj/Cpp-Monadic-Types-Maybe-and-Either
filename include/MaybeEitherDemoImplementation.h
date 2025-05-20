// ============================================================================
// Demo app implementation for the Maybe/Either monadic operations.
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
// * MaybeEitherDemoImplementation.h: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Headers Include Section
// ============================================================================

// Project library headers
#include <MaybeEitherCommon.h>
#include <ProgramActions/MainProgramAction.h>

// Standard library headers
#include <array>
#include <cmath>
#include <exception>
#include <iostream>
#include <string_view>

// ============================================================================
// Class Declaration Section
// ============================================================================

/** ---------------------------------------------------------------------------
 * @brief Concrete implementation of the strategy for the main program action.
 *
 * This class provides a sample implementation of the execution logic that would
 * be performed when a MainProgramAction is executed. It serves as a
 * demonstration of how to create concrete strategies for program actions.
 * -------------------------------------------------------------------------- */
class MaybeEitherDemoImplementation
{
public:
    /** -----------------------------------------------------------------------
     * @brief Default constructor for OdbDemoImplementation.
     * ---------------------------------------------------------------------- */
    explicit MaybeEitherDemoImplementation() = default;

    /** -----------------------------------------------------------------------
     * @brief Executes the main program action.
     *
     * This operator() overload defines the behavior of the main program
     * strategy when invoked. It takes a constant reference to a
     * MainProgramAction object and a string_view representing the execution
     * name.
     *
     * @param action    A constant reference to the MainProgramAction object.
     * (Note: In this simple example, the action object itself is not directly
     * used, but it is included as part of the strategy's signature).
     * @param exec_name A string_view representing the name or identifier of the
     * main program action being executed.
     * @return EXIT_SUCCESS to indicate successful execution of this
     * demonstration strategy.
     * ---------------------------------------------------------------------- */
    int operator()(
        MainProgramAction const& action,
        std::string_view const& exec_name
    ) const;
};

// End of 'MaybeEitherDemoImplementation.h'
// ============================================================================
// Demo app definition.
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
// * MaybeEitherDemo.cpp: created.
//
// ============================================================================

// ============================================================================
// Headers include section
// ============================================================================

// Related header
#include <MaybeEitherDemo.h>

// Project library headers
#include <ProgramActions/ShowHelpClippStrategy.h>
#include <ProgramActions/ShowUsageClippStrategy.h>
#include <ProgramActions/ShowVersionInfoStrategy.h>
#include <ProgramActions/UnsupportedOptionsClippStrategy.h>
#include "MaybeEitherDemoImplementation.h"

// Standard library headers
#include <filesystem>

// External libraries headers

// ============================================================================
// Global constants section
// ============================================================================

static constexpr std::string_view kAppName = "maybe_either_demo";
static constexpr std::string_view kVersionString = "0.1";
static constexpr std::string_view kAppDoc = "\
A small program to demonstrate implementation of the Maybe/Either monads\
for the C++17.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";


// ============================================================================
// Main function section
// ============================================================================

int main(int argc, char *argv[])
{
    namespace fs = std::filesystem;  // Define a shorter alias for filesystem

    // Determine the exec name under wich program is beeing executed
    std::string execName = fs::path(argv[0]).filename().string();

    // Parse command line options
    auto result = clipp::parse(argc, argv, appOptions);

    // Reference to a program action that will be executed
    std::unique_ptr<ProgramAction> programAction;

    // Check for the unsupported options --------------------------------------
    if (!userOptionValues.m_Unsupported.empty())
    {
        programAction = std::make_unique<UnsupportedOptionsAction> (
        UnsupportedOptionsClippStrategy(userOptionValues.m_Unsupported)
        );
    }

    // Check for high priority switches ---------------------------------------
    // (i.e. '--help', '--usage', '--version')
    else if (userOptionValues.m_ShowHelp)
    {
        // Check if the help switch was triggered. We give help switch the
        // highest priority, so if it is triggered we don't need to check
        // anything else.
        programAction = std::make_unique<ShowHelpAction> (
        ShowHelpClippStrategy(appOptions, kAppDoc, kAuthorEmail)
        );
    }
    else if (userOptionValues.m_PrintUsage)
    {
        // Check if the usage switch was triggered. Usge switch has the second
        // highest priority, so if it is triggered we don't need to check
        // anything else.
        auto fmt = clipp::doc_formatting {}
            .first_column(0)
            .last_column(79);
        programAction = std::make_unique<ShowUsageAction> (
            ShowUsageClippStrategy(appOptions, fmt)
        );
    }
    else if (userOptionValues.m_ShowVersion)
    {
        // Check if the version switch was triggered. Version switch has the
        // third highest priority.
        programAction = std::make_unique<ShowVersionInfoAction> (
            ShowVersionInfoStrategy(
                kVersionString,
                kYearString,
                kAuthorName,
                kLicense
            )
        );
    }
    else
    {
        // No high priority switch was passed. Proceed with the main code.
        programAction = std::make_unique<MainProgramAction> (
            MaybeEitherDemoImplementation()
        );
    }

  return programAction->execute(execName.c_str());
}

// End of 'OdbDemo.cpp'
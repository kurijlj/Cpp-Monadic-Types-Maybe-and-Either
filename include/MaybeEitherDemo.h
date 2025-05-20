// ============================================================================
// Demo app for the Maybe/Either monadic operations.
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
// * MaybeEitherDemo.h: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Macro Definitions Section
// ============================================================================

// ============================================================================
// Headers include section
// ============================================================================

// Project library headers
#include "MaybeEitherCommon.h"

// Standard library headers

// External library headers
#include <clipp/clipp.hpp>


// ============================================================================
// CLI Options Data Structure Section
// ============================================================================

// Define the data structure to store user selected (parsed) option values.
// We use the same data structure to define, and store the default
// option values
struct CliOptionValues
{
    std::vector<std::string> m_Unsupported;  // Store parsed options that do
                                             // not fit any of the provided
                                             // options
    bool m_ShowHelp;
    bool m_PrintUsage;
    bool m_ShowVersion;
};

// Define the default values for the command line options
static CliOptionValues userOptionValues
{
    {},          // m_Unsupported
    false,       // m_ShowHelp
    false,       // m_PrintUsage
    false        // m_ShowVersion
};


// ============================================================================
// Parser Setup Section
// ============================================================================

auto appOptions = (
    // Define the command line options and their default values.
    // - Must have more than one option.
    // - The order of the options is important.
    // - The order of the options in the group is important.
    // - Take care not to omitt value filter when parsing file
    //   and directory names. Otherwise, the parser will treat options
    //   as values.
    // - Define positional arguments first
    // - Define positional srguments as optional to enforce
    //   the priority of help, usage and version switches. Then enforce
    //   the required positional arguments by checking if their
    //   values are set.
    (
        (
            clipp::option("-h", "--help")
                .set(userOptionValues.m_ShowHelp)
        ).doc(kHelpOptionDoc.data()),
        (
            clipp::option("--usage")
                .set(userOptionValues.m_PrintUsage)
        ).doc(kUsageOptionDoc.data()),
        (
            clipp::option("-V", "--version")
                .set(userOptionValues.m_ShowVersion)
        ).doc(kVersionOptionDoc.data())
    ).doc("general options:"),
    // (
    //     clipp::value(
    //         clipp::match::prefix_not("-"),
    //         "OUTPUT_FILE",
    //         userOptionValues.m_OutFile
    //     ).doc(kOutFileOptionDoc.data()),
    // ).doc("file options:"),
    clipp::any_other(userOptionValues.m_Unsupported)
);

// End of 'MaybeEitherDemo.h'
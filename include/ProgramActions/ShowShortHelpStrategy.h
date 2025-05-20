// ShowShortHelpStrategy.h
#pragma once

#include "ShowShortHelpAction.h"

#include <iostream>

// ----------------------------------------------------------------------------
// ShowShortHelpStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for displaying short help information about the program
//
// ----------------------------------------------------------------------------
class ShowShortHelpStrategy {
public:
  explicit ShowShortHelpStrategy() = default;

  // Shows short help message
  int operator()(
      ShowShortHelpAction const& action,
      std::string_view const& exec_name
    ) const {
    std::cout << "\n";

    // Print short help message
    std::cout << "Try '" << exec_name << " --help' for more information.\n";

    return EXIT_FAILURE;
  }
};

// End of 'ShowShortHelpStrategy.h'
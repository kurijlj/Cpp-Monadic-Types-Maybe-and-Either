// UnsupportedOptionsClippStrategy.h
#pragma once

// Related header
#include "UnsupportedOptionsAction.h"

// Standard Library headers
#include <iostream>

// ----------------------------------------------------------------------------
// UnsupportedOptionsClippStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for displaying aggregated unsupported options and short
//              help message about the program using Clipp library
//
// ----------------------------------------------------------------------------
class UnsupportedOptionsClippStrategy {
public:
  explicit UnsupportedOptionsClippStrategy(
      std::vector<std::string> const& unsupported_options
    ) : unsupported_options_(unsupported_options) { }

  // Shows aggregated unsupported options and short help message
  int operator()(UnsupportedOptionsAction const& action,
      std::string_view const& exec_name) const {
    std::cerr << exec_name << ": Unsupported options: ";
    for (const auto& opt : unsupported_options_) {
      std::cerr << opt << " ";
    }
    std::cerr << "\n";

    // Print short help message
    std::cout << "Try '" << exec_name << " --help' for more information.\n";

    return EXIT_FAILURE;
  }

private:
  std::vector<std::string> const& unsupported_options_;
};

// End of 'UnsupportedOptionsClippStrategy.h'
// ShowUsageClippStrategy.h
#pragma once

#include "ShowUsageAction.h"

#include <iostream>

#include <clipp.hpp>    // command line arguments parsing

// ----------------------------------------------------------------------------
// ShowUsageClippStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for displaying usage information about the program
//
// ----------------------------------------------------------------------------
class ShowUsageClippStrategy {
public:
  explicit ShowUsageClippStrategy(
    clipp::group const& group,
    clipp::doc_formatting const& fmt = clipp::doc_formatting{}
    ) : group_(group), fmt_(fmt) { }

  // Shows usage information
  int operator()(
      ShowUsageAction const& action,
      std::string_view const& exec_name
      ) const {
    std::cout << clipp::usage_lines(group_, std::string {exec_name}, fmt_)
      << "\n";

    return EXIT_SUCCESS;
  }

private:
  clipp::group group_;
  clipp::doc_formatting fmt_;
};

// End of 'ShowUsageClippStrategy.h'
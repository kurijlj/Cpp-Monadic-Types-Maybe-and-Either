// MainProgramStrategy.h
#pragma once

#include "MainProgramAction.h"

#include <iostream>

// ----------------------------------------------------------------------------
// MainProgramStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for executing the main program
//
// ----------------------------------------------------------------------------
class MainProgramStrategy {
public:
  explicit MainProgramStrategy() = default;

  // Executes the main program
  int operator()(
      MainProgramAction const& action,
      std::string_view const& exec_name
    ) const {
    std::cout << exec_name << ": Hello world!\n";

    return EXIT_SUCCESS;
  }
};

// End of 'MainProgramStrategy.h'
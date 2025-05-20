// ProgramAction.h
#pragma once

#include <cstdlib>
#include <functional>
#include <string_view>

// ----------------------------------------------------------------------------
// ProgramAction
// ----------------------------------------------------------------------------
//
// Description: Abstract class for all actions that can be executed by
//              the program
//
// ----------------------------------------------------------------------------

class ProgramAction {
public:
  ~ProgramAction() = default;

  virtual int execute(std::string_view const& exec_name) const = 0;
};

// End of 'ProgramAction.h'
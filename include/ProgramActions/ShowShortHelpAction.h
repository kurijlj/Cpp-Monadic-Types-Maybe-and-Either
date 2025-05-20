// ShowShortHelpAction.h
#pragma once

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// ShowShortHelpAction
// ----------------------------------------------------------------------------
//
// Description: Displays short help information about the program
//
// ----------------------------------------------------------------------------
class ShowShortHelpAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(
    ShowShortHelpAction const&,
    std::string_view const&
    )>;

  explicit ShowShortHelpAction(ExecuteStrategy executor)
    : executor_(std::move(executor))
  { }
  
  // Shows short help message
  int execute(std::string_view const& exec_name) const override{
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

// End of 'ShowShortHelpAction.h'
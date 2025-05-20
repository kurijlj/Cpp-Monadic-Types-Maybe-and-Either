// ShowHelpAction.h
#pragma once

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// ShowHelpAction
// ----------------------------------------------------------------------------
//
// Description: Displays help information about the program
//
// ----------------------------------------------------------------------------
class ShowHelpAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(
    ShowHelpAction const&,
    std::string_view const&
    )>;

  explicit ShowHelpAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(std::string_view const& exec_name) const override {
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

// End of 'ShowHelpAction.h'
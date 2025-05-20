// ShowUsageAction.h
#pragma once

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// ShowUsageAction
// ----------------------------------------------------------------------------
//
// Description: Displays usage information about the program
//
// ----------------------------------------------------------------------------
class ShowUsageAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(
    ShowUsageAction const&,
    std::string_view const&
    )>;

  explicit ShowUsageAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(std::string_view const& exec_name) const override {
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

// End of 'ShowUsageAction.h'
// UnsupportedOptionsAction.h
#pragma once

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// UnsupportedOptionsAction
// ----------------------------------------------------------------------------
//
// Description: Displays aggregated unsupported options and short help message
//
// ----------------------------------------------------------------------------
class UnsupportedOptionsAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(
    UnsupportedOptionsAction const&,
    std::string_view const&
    )>;

  explicit UnsupportedOptionsAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  // Shows aggregated unsupported options and short help message
  int execute(std::string_view const& exec_name) const override{
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

// End of 'UnsupportedOptionsAction.h'
// MainProgramAction.h
#pragma once

#include "ProgramAction.h"

// ----------------------------------------------------------------------------
// MainProgramAction
// ----------------------------------------------------------------------------
//
// Description: Executes the main action of the program
//
// ----------------------------------------------------------------------------
class MainProgramAction : public ProgramAction {
public:
  using ExecuteStrategy = std::function<int(
    MainProgramAction const&,
    std::string_view const&
    )>;

  explicit MainProgramAction(ExecuteStrategy executor)
    : executor_(std::move(executor)) { }
  
  int execute(std::string_view const& exec_name) const override {
    return executor_(*this, exec_name);
  }

private:
  ExecuteStrategy executor_;
};

// End of 'MainProgramAction.h'
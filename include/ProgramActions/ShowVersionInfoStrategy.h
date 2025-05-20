// ShowVersionInfoStrategy.h
#pragma once

#include "ShowVersionInfoAction.h"

#include <iostream>
#include <string>

// ----------------------------------------------------------------------------
// ShowVersionInfoStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for displaying version information about the program
//
// ----------------------------------------------------------------------------
class ShowVersionInfoStrategy {
public:
  explicit ShowVersionInfoStrategy(
    std::string_view const& app_version,
    std::string_view const& release_year,
    std::string_view const& author_name,
    std::string_view const& license
    ) : app_version_(app_version),
        release_year_(release_year),
        author_name_(author_name),
        license_(license) { }

  // Shows version information
  int operator()(
      ShowVersionInfoAction const& action,
      std::string_view const& exec_name
      ) const {
    std::cout
      << exec_name << " "
      << app_version_ << " Copyright (C) "
      << release_year_ << " "
      << author_name_ << "\n"
      << license_;

    return EXIT_SUCCESS;
  }

private:
  std::string app_version_;
  std::string release_year_;
  std::string author_name_;
  std::string license_;
};

// End of 'ShowVersionInfoStrategy.h'
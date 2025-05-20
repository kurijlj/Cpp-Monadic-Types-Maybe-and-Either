// ShowHelpClippStrategy.h
#pragma once

#include "ShowHelpAction.h"

#include <iostream>

#include <clipp.hpp>

// ----------------------------------------------------------------------------
// ShowHelpClippStrategy
// ----------------------------------------------------------------------------
//
// Description: Strategy for displaying help information about the program
//
// ----------------------------------------------------------------------------
class ShowHelpClippStrategy {
public:
  explicit ShowHelpClippStrategy(
    clipp::group const& group,
    std::string_view const& app_doc,
    std::string_view const& author_email
    ) : group_(group),
        app_doc_(app_doc),
        author_email_(author_email) { }

  // Shows help information
  int operator()(
      ShowHelpAction const& action,
      std::string_view const& exec_name
      ) const {
    auto fmt = clipp::doc_formatting{}.first_column(0).last_column(79);
    clipp::man_page man;

    man.prepend_section(
      "USAGE",
      clipp::usage_lines(group_, std::string {exec_name}, fmt).str()
      );
    man.append_section("", std::string {app_doc_});
    man.append_section("", clipp::documentation(group_, fmt).str());
    man.append_section(
      "",
      "Report bugs to <" + std::string {author_email_} + ">."
      );

    std::cout << man;

    return EXIT_SUCCESS;
  }

private:
  clipp::group group_;
  std::string app_doc_;
  std::string author_email_;
};

// End of 'ShowHelpClippStrategy.h'
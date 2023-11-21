// Implementation file for user_context.hpp
// 
// Things stored in the User Context are:
//  - A limited history of the past evaluated expressions
//  - The max size of the list of history
//  - The value of the last expression evaluated
//  - A list of all reserved keywords
//  - A map of all current user variables to their values
//  - [TODO] A list of all currently opened graphs 
//
// Author(s): 
// Jake Bernard [from (est) 10/20/2023 - Present],
//
// Last update:
//  - 11/21/2023 (Jake): Commented file
//
#include <vector>
#include <string>
#include <map>
#include <array>
#include <cctype>

#include "user_context.hpp"
#include "util/flags.hpp"

// This is a "string_view" array because it's considered best practices
// to have constexpr structures not use dynamic objects due to some
// problems that can arise with calling destructors.
constexpr std::string_view kReservedKeywords[] = {
                                "exit", "var", "vars",
                                "savetovar", "history",
                                "removevar", "help",
                                "switchGUI", "e",
                                "pi", "g", "log",
                                "ln", "sqrt", "root"
                              };

std::size_t UserContext::history_len() {
  return history_.size();
}

void UserContext::add_history(std::string expr) {
  if (history_.front() == expr) {
    return;
  }
  if (history_len() >= max_history_len_) {
    history_.pop_back();
  }
  history_.push_front(expr);
}

std::list<std::string>& UserContext::get_history() {
  return history_;
}

std::map<std::string, int>& UserContext::get_var_list() {
  return user_vars_;
}

bool UserContext::in_keywords(std::string var) {
  for (auto keyword : kReservedKeywords) {
    if (var == keyword) {
      return true;
    }
  }
  return false;
}

bool UserContext::var_exists(std::string var) {
  return user_vars_.contains(var);
}

flags::UserVarMsg UserContext::add_var(std::string var, int val) {

  if (in_keywords(var)) {
    return flags::UserVarMsg::kVarReservedError;
  }

  else if (var_exists(var)) {
    return flags::UserVarMsg::kVarNeedOverwrite;
  }

  else if (!var_format_correct(var)) {
    return flags::UserVarMsg::kVarFormatError;
  }

  else {
    user_vars_.insert({var, val});
    return flags::UserVarMsg::kVarWriteSuccess;
  }
}

bool UserContext::remove_var(std::string var) {
  if (var_exists(var)) {
    user_vars_.erase(var);
    return true;
  }
  else {
    return false;
  }
}

void UserContext::overwrite_var(std::string var, int val) {
  user_vars_[var] = val;
}

bool UserContext::var_format_correct(std::string var) {
  std::string::iterator itr;
  for (itr = var.begin(); itr != var.end(); itr++) {
    if (std::isaalpha(*itr) || (*itr) == '_') {
      continue;
    }
    else {
      return false;
    }
  }
  return true;
}
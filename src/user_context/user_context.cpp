#include <vector>
#include <string>
#include <map>
#include <array>

#include "user_context.h"
#include "util/flags.h"

std::size_t UserContext::history_len() {
  return history_.size();
}

void UserContext::add_history(std::string expr) {
  if (history_len() == max_history_len_) {
    history_.pop_back();
  }
  history_.push_back(expr);
}

std::list<std::string>& UserContext::get_history() {
  return history_;
}

bool UserContext::in_keywords(std::string var) {
  // TODO(Jake): implement functionality later
  return false;
}

bool UserContext::var_exists(std::string var) {
  // TODO(Jake): implement functionality later
  return false;
}

flags::UserVarMsg UserContext::add_var(std::string var, int val) {
  if (in_keywords(var)) {
    return flags::UserVarMsg::kVarReservedError;
  }
  else if (var_exists(var)) {
    return flags::UserVarMsg::kVarNeedOverwrite;
  }

  // TODO (Jake): Implement this
  // else if (!var_format_correct(var)) {
  //   return flags::UserVarMsg::kVarFormatError;
  // }

  else {
    // TODO(Jake): insert var and value into user_vars
    return flags::UserVarMsg::kVarWriteSuccess;
  }
}

bool UserContext::remove_var(std::string var) {
  // TODO(Jake): insert var and value into user_vars
  return false;
}
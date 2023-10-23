#include <iostream>

#include "ui/interface.h"
#include "util/flags.h"

void AppInterface::AddToHistory(std::string expr) {
  user_context_.add_history(expr);
}

flags::UserVarMsg AppInterface::AddToUserVars(std::string var, int val) {
  // TODO (Jake): add functionality
  return flags::UserVarMsg::kVarWriteSuccess;
}

bool AppInterface::RemoveFromUserVars(std::string var) {
  // TODO (Jake): add functionality
  std::cout << "Functionality not yet implemented :)\n";
  return true;
}

AppInterface::AppInterface() {}

AppInterface::AppInterface(UserContext &context) {
  // TODO (Jake): use move semantics later
  user_context_ = context;
}
AppInterface::~AppInterface() {}
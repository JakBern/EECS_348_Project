// This the implementation file for the Interface abstract base class.
//
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
//
//
// Last update:
//  - 11/30/2023 (Jake): Commented out unused functionality, removed functions
//      AddToVars, AddToHistory, etc (can be done easily in each UI)
#include <iostream>
#include <memory>

#include "ui/interface.hpp"
#include "util/flags.hpp"

AppInterface::AppInterface(std::shared_ptr<UserContext> context,
                            std::shared_ptr<Parser> parser) : 
                            user_context_(context), parser_(parser) {}

AppInterface::~AppInterface() {}
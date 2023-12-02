// Runs the program, switching between interfaces when necessary and loading
// any previous config from config.cfg
//
// Be sure to look at the Google C++ Style Guide when
// necessary and set your tabs to enter 2 spaces.
// We'll probably have to add a license later and include the boilerplate.
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
// Vidur Pandiripally [from 10/24/2023 - Present],
//
// Last update:
//  - 11/30/2023 (Jake): Updated to include parser
//

#include <memory>
#include <iostream>

#include "ui/tui/tui.hpp"
#include "ui/interface.hpp"
#include "util/flags.hpp"
#include "util/helper.hpp"
#include "user_context/user_context.hpp"
#include "parser/parser.hpp"

int main() {

  // TODO(Jake): Find way to hide command line at startup.
  // TODO: Might be an OS-specific operation.

  // The window in which the program will be run
  std::unique_ptr<AppInterface> window = nullptr;

  std::shared_ptr<UserContext> context = std::make_shared<UserContext>();

  std::shared_ptr<Parser> parser = std::make_shared<Parser>();

  // TUI and GUI are child classes of AppInterface,
  // so we can make our window either of those.
  // ====Config is currently unused, but in a working state===
  // if (!helper::config::UseGUI()) {
    window = std::make_unique<TUI>(context, parser);
  // }
  // TODO(Jake): Add GUI implementation
  // else {
  //   window =  std::make_unique<GUI>(context/*, parser*/);
  // }

  while (true) {

    // The program will stop running once an internal signal is given to quit or
    // to switch to the other GUI type. This signal is returned as an
    // InterfaceCode (see util/flags.h)
    flags::InterfaceCode exit_code = window->Run();

    // Only possible exit code at the moment
    if ( exit_code == flags::InterfaceCode::kCleanExit) {
      window->Close();
      break;
    }

    // else if (exit_code == flags::InterfaceCode::kSwitchToTUI) {
    //   std::unique_ptr<TUI> temp = std::make_unique<TUI>(window);
    //   window->Close();
    //   window = temp;
    // } 

    // TODO: When GUI is added
    //
    // else if (exit_code == flags::InterfaceCode::kSwitchToGUI) {
    //   std::unique_ptr<GUI> temp = std::make_unique<GUI>(window);
    //   window->Close();
    //   window = temp;
    // }
    }

  return 0;

}
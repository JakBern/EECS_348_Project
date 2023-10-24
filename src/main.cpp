// Runs the program, switching between interfaces when necessary and loading
// any previous config from config.cfg
//
// Be sure to look at the Google C++ Style Guide when
// necessary and set your tabs to enter 2 spaces.
// We'll probably have to add a license later and include the boilerplate.
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
// YourName Here [from Blank - Blank]
//
// Last update:
//  - 10/19/2023 (Jake): Created file, added basic code
//

#include <memory>
#include <iostream>

#include "ui/tui/tui.h"
#include "ui/interface.h"
#include "util/flags.h"
#include "util/helper.h"
#include "user_context/user_context.h"

int main() {

  // TODO(Jake): Find way to hide command line at startup.
  // TODO: Might be an OS-specific operation.

  // The window in which the program will be run
  std::unique_ptr<AppInterface> window = nullptr;

  std::shared_ptr<UserContext> context = std::make_shared<UserContext>();

  // TODO: Add in parser when implemented
  // std::shared_ptr<Parser> context = std::make_shared<Parser>(context);

  // TUI and GUI are child classes of AppInterface,
  // so we can make our window either of those.
  if (!helper::config::UseGUI()) {
    window = std::make_unique<TUI>(context/*, parser*/);
  }
  // TODO: Add GUI implementation
  // else {
  //   window =  std::make_unique<GUI>(context/*, parser*/);
  // }

  while (true) {

    // The program will stop running once an internal signal is given to quit or
    // to switch to the other GUI type. This signal is returned as an
    // InterfaceCode (see util/flags.h)
    flags::InterfaceCode exit_code = window->Run();

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
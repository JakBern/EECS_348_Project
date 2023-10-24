#include <iostream>
#include <string_view>

#include "ui/tui/tui.h"
#include "util/flags.h"
#include "user_context/user_context.h"

constexpr std::string_view kWelcomeMessage = 
"Welcome to the Arithmetic Expression Evaluator\n";

constexpr std::string_view kMainMenuMessage = 
"Enter an expression or command below, type \"help\" for help:\n";

constexpr std::string_view kHelpMessage = 
"Supported operators:\n"
"+, -, /, *, %, ^ (or **)\n"
"Current commands are:\n"
"- \"exit\": exits program\n"
"- \"history\": displays history and allows selecting a previous expression\n"
"- \"vars\": displays all user stored variables and their values\n"
"- \"removevar <varname>\": removes variable with matching name\n"
"- \"savetovar <varname>\": saves result of expression to <varname>\n"
"- \"switchGUI\": switches to GUI version of program\n"
"- \"help\": displays this stuff\n";

void TUI::LoadFromHistory(int expr_num) {
  std::cout << "Functionality not yet implemented :)\n";
}

void TUI::Eval(std::string expr) {
  // parser_.eval(expr)
  std::cout << "Functionality not yet implemented :)\n";
  std::cout << "Entered string was added to history.\n";
  user_context_.add_history(expr);
}


void TUI::DisplayError(std::string expr, 
                        flags::EvalErr err, 
                        int position) {
  return;
}

flags::InterfaceCode TUI::Run() {

  std::cout << kWelcomeMessage;

  while (true) {
    std::cout << kMainMenuMessage;

    std::cin >> user_input_;

    if (user_input_ == "help") {
      std::cout << kHelpMessage;
    }

    else if (user_input_ == "history") {
      RunHistoryMenu();
    }

    else if (user_input_ == "vars") {
      // TODO (Jake): Add this function
      // DisplayVars();
    }

    else if (user_input_ == "savetovar") {
      std::cout << "Functionality not yet implemented :)\n";
    }

    else if (user_input_ == "removevar") {
      std::cout << "Functionality not yet implemented :)\n";
    }

    else if (user_input_ == "exit") {
      return flags::InterfaceCode::kCleanExit;
    }

    else if (user_input_ == "switchGUI") {
      std::cout << "Functionality not yet implemented :)\n";
      // return flags::kSwitchToGUI;
    }

    else {
      Eval(user_input_);
    }
  }

}

void TUI::Close() {
  return;
}

void TUI::RunHistoryMenu() {
  std::cout << "Current history:\n";
  DisplayHistory();
  std::cout << "Choose an option with corresponding number,"
  " or enter anything else to return to the main menu.\n";
  std::cin >> user_input_;
  if (user_input_ != "0") {
    std::cout << "Functionality not yet implemented :)\n";
  }
  return;
}

void TUI::DisplayHistory() {
  int num = 1;
  if (user_context_.history_len() == 0) {
    std::cout << "\t...History is empty...\n";
    return;
  }
  for (std::string expr : user_context_.get_history()) {
    std::cout << "\t" << num << ") " << expr << "\n";
    num++;
  }
  return;
}

TUI::TUI() {}
TUI::~TUI() {}
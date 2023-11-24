#include <iostream>
#include <string_view>
#include <string>
#include <vector>

#include "ui/tui/tui.hpp"
#include "util/flags.hpp"
#include "util/helper.hpp"
#include "user_context/user_context.hpp"

constexpr std::string_view kWelcomeMessage = 
"Welcome to the Arithmetic Expression Evaluator\n";

constexpr std::string_view kMainMenuMessage = 
"Enter an expression or command below, type \"help\" for help:\n";

constexpr std::string_view kHelpMessage = 
"Supported operators:\n"
"+, -, /, *, %, ^ (or **)\n"
"Current commands are:\n"
"- \"eval\": allows you to enter an expression to be evaluated\n"
"\t- alternvatively, enter \"eval <expression>\"\n"
"- \"graph\": enter an expression to graph (use graphing variable \"G\")\n"
"\t- alternvatively, enter \"graph <expression>\"\n"
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
  user_context_->add_history(expr);
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

    std::getline(std::cin, user_input_);

    helper::str_func::Trim(user_input_);

    std::vector<std::string> input = helper::str_func::Split(user_input_);

    if (input[0] == "help") {
      std::cout << kHelpMessage;
    }

    else if (input[0] == "history") {
      RunHistoryMenu();
    }

    else if (input[0] == "vars") {
      DisplayVars();
    }

    else if (input[0] == "savetovar") {
      std::cout << "Functionality not yet implemented :)\n";
    }

    else if (input[0] == "removevar") {
      std::cout << "Functionality not yet implemented :)\n";
    }

    else if (input[0] == "exit") {
      return flags::InterfaceCode::kCleanExit;
    }

    else if (input[0] == "switchGUI") {
      std::cout << "Functionality not yet implemented :)\n";
      // return flags::kSwitchToGUI;
    }

    else if ( )

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
  if (user_context_->history_len() == 0) {
    std::cout << "\t...History is empty...\n";
    return;
  }
  for (std::string expr : user_context_->get_history()) {
    std::cout << "\t" << num << ") " << expr << "\n";
    num++;
  }
  return;
}

void TUI::DisplayVars() {
  std::cout << "USER VARIABLES\n";
  auto const& var_list = user_context_->get_var_list();
  if (!var_list.size()) {
    std::cout << "\t...No user variables saved...\n";
    return;
  }
  for (auto const& var_val_pair : var_list) {
    std::cout << "Name: " << var_val_pair.first
              << "\n"
              << "Value" << var_val_pair.second
              << "\n\n";
  }
}


TUI::TUI(std::shared_ptr<UserContext> context) : AppInterface(context) {}
TUI::~TUI() {}


#include <iostream>
#include <string>
#include <vector>
// #include <chrono>
// #include <thread>

#include "ui/tui/tui.hpp"
#include "util/flags.hpp"
#include "util/helper.hpp"
#include "user_context/user_context.hpp"

const char kWelcomeMessage[] = 
"Welcome to the Arithmetic Expression Evaluator!\n";

const char* kMainMenuMessage = 
"Enter a command below, type \"help\" for help:\n";

const char* kHelpMessage = 
"Supported operators:\n"
"+, -, /, *, %, ^ (or **)\n"
"Current commands are:\n"
"- \"eval\": allows you to enter an expression to be evaluated\n"
"\t- alternvatively, enter \"eval <expression>\"\n"
// "- \"graph\": enter an expression to graph (use graphing variable \"G\")\n"
// "\t- alternvatively, enter \"graph <expression>\"\n"
"- \"exit\": exits program\n"
"- \"history\": displays history and allows selecting a previous expression\n"
// "- \"vars\": displays all user stored variables and their values\n"
// "- \"removevar <varname>\": removes variable with matching name\n"
// "- \"savetovar <varname>\": saves result of expression to <varname>\n"
// "- \"switchGUI\": switches to GUI version of program\n"
"- \"help\": displays this stuff\n";

// ===========REMOVED UNTIL FUTURE ITERATIONS==========

// void TUI::RunWelcomeAnimation() {
//   std::string cycle = "0123456789+-*/^%";
//   int cycle_ind = 0;
//   for (unsigned int i = 0;
//       i < (sizeof(kWelcomeMessage) / sizeof(char)) - 2; 
//       i++) {
//     for (unsigned int j = 0; j < 3; j++) {
//       cycle_ind = (cycle_ind + 1) % cycle.length();
//       std::this_thread::sleep_for(std::chrono::milliseconds(30));
//       std::cout << cycle[cycle_ind] << std::flush;
//       std::cout << "\b" << std::flush;
//     }
//     std::cout << kWelcomeMessage[i] << std::flush;
//   }
//   std::cout << std::endl;
// }

// =====================END REMOVED=================

void TUI::LoadFromHistory(int expr_num) {
  std::cout << "Functionality not yet implemented :)\n";
}

void TUI::Eval(std::string expr) {
  std::string result = "";
  // flags::EvalError result_code = parser_.Eval(expr, result);
  // if (result_code == flags::EvalError:kSuccess) {
  // user_context_->add_history(expr); 
  // }
  // DisplayEvalResults(result_code, result);
  std::cout << "Functionality not yet implemented :)\n";
}


void TUI::DisplayError(std::string expr, 
                        flags::EvalError err, 
                        int position) {
  return;
}

flags::InterfaceCode TUI::Run() {

  std::cout << kWelcomeMessage;

  while (true) {
    std::cout << kMainMenuMessage << std::flush;

    user_input_ = "";

    std::getline(std::cin, user_input_);

    helper::str_func::Trim(user_input_);

    std::vector<std::string> split_input = helper::str_func::Split(user_input_);

    if (split_input.size() == 0) {
      std::cout << "Input was not understood, please try again\n";
      continue;
    }

    if (split_input[0] == "help") {
      std::cout << kHelpMessage;
    }

    else if (split_input[0] == "history") {
      RunHistoryMenu();
    }

    // ===========REMOVED UNTIL FUTURE ITERATIONS==========
    // else if (split_input[0] == "vars") {
    //   DisplayVars();
    // }

    // else if (split_input[0] == "savetovar") {
    //   std::cout << "Functionality not yet implemented :)\n";
    // }

    // else if (split_input[0] == "removevar") {
    //   std::cout << "Functionality not yet implemented :)\n";
    // }

    // =====================END REMOVED=================

    else if (split_input[0] == "exit") {
      return flags::InterfaceCode::kCleanExit;
    }

    // ========REMOVED UNTIL FUTURE ITERATIONS==========

    // else if (split_input[0] == "switchgui") {
    //   std::cout << "Functionality not yet implemented :)\n";
    //   // return flags::kSwitchToGUI;
    // }

    // =====================END REMOVED=================

    else if (split_input[0] == "eval") {
      if (split_input.size() == 1) {
        RunEvalMenu();
      }
      else {
        std::string result = "";
        user_input_ = "";
        for (unsigned int i = 1; i < split_input.size(); i++) {
          user_input_ += split_input[i];
        }
        // flags::EvalError result_code = parser_.Eval(user_input_, result)
        // DisplayEvalResults(result_code, result);
        // if (result_code == flags::EvalError:kSuccess) {
        // user_context_->add_history(expr); 
        // }
        
      }

    }

    // ========REMOVED UNTIL FUTURE ITERATIONS==========

    // else if (split_input[0] == "graph") {
    //   if (split_input.size() == 1) {
    //     RunGraphMenu();
    //   }
    //   else {
    //     std::string result = "";
    //     user_input_ = "";
    //     for (unsigned int i = 1; i < split_input.size(); i++) {
    //       user_input_ += split_input[i];
    //     }
    //     flags::EvalError result_code = parser_.Eval(user_input_, result)
    //     DisplayEvalResults(result_code, result);
    //     if (result_code == flags::EvalError:kSuccess) {
    //     user_context_->add_history(expr); 
    //     }
    //   }
    // }

    // =====================END REMOVED=================

    else {
      std::cout << "Input was not understood, please try again\n";
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
  std::getline(std::cin, user_input_);
  if (user_input_ != "0") {
    std::cout << "Functionality not yet implemented :)\n";
  }
  return;
}

void TUI::RunEvalMenu() {
  std::cout << "Enter expression to be evaluated or type \"exit\" to exit.\n";
  user_input_ = "";
  std::getline(std::cin, user_input_);
  if (user_input_ == "exit") {
    return;
  }
  Eval(user_input_);
}

// ========REMOVED UNTIL FUTURE ITERATIONS==========

// void TUI::RunGraphMenu() {
//   std::cout << "Enter expression to be graphed or type \"exit\" to exit.\n";
//   user_input_ = "";
//   std::getline(std::cin, user_input_);
//   if (user_input_ == "exit") {
//     return;
//   }
//   Graph(user_input_);
// }

// =====================END REMOVED=================

void TUI::DisplayEvalResults(flags::EvalError result_code, 
                              std::string& result) {
  switch (result_code) {
    case flags::EvalError::kSuccess:
      std::cout << "Result is:\n" << result << std::endl;
      break;
    case flags::EvalError::kDivByZero:
      std::cout << "ERROR: Division by zero occurs in expression.\n";
      break;
    case flags::EvalError::kInvalidSyntax:
      std::cout << "ERROR: An unknown character or variable reference occurs"
                  "in expression.\n";
      break;
    case flags::EvalError::kMismatchedParentheses:
      std::cout << "ERROR: Mismatched parentheses within the expression.";
      break;
  }
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

// ========REMOVED UNTIL FUTURE ITERATIONS==========

// void TUI::DisplayVars() {
//   std::cout << "USER VARIABLES\n";
//   auto const& var_list = user_context_->get_var_list();
//   if (!var_list.size()) {
//     std::cout << "\t...No user variables saved...\n";
//     return;
//   }
//   for (auto const& var_val_pair : var_list) {
//     std::cout << "Name: " << var_val_pair.first
//               << "\n"
//               << "Value" << var_val_pair.second
//               << "\n\n";
//   }
// }

// =====================END REMOVED=================


TUI::TUI(std::shared_ptr<UserContext> context) : AppInterface(context) {}
TUI::~TUI() {}


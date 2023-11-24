// TUI (Text User Interface)
// Represents the command line user interface
//
// Author(s): 
// Jake Bernard [from 10/19/2023 - Present]
//
// Last update:
//  - 10/19/2023 (Jake):
//    Recreated and renamed file
//
#ifndef UI_TUI_TUI_H_
#define UI_TUI_TUI_H_

#include <memory>

#include "ui/interface.hpp"
#include "util/flags.hpp"

class TUI : public AppInterface {
  public:
    

    TUI(std::shared_ptr<UserContext> context);
    ~TUI();

  protected:

    // Runs the program.
    // Returns an InterfaceCode depending upon what the 
    // Control Module (main.cpp) should do:
    // InterfaceCodes:
    //  - kCleanExit
    //    - The program should exit
    //  - kSwitchGUI
    //    - The program should switch to GUI mode
    //  - kSwitchTUI
    //    - The program should switch to TUI mode (never returned here)
    flags::InterfaceCode Run() override;

    // Frees all memory taken up by the GUI/program
    void Close() override;

    // Currently re-evaluates a function from the history specified by a number.
    //
    // Later is planned to allow editing of the expression
    void LoadFromHistory(int expr_num) override;

    // Switches to the history menu, which displays the current history
    // and allows the user to pick an expression from the history to re-evaluate
    // or exit.
    void RunHistoryMenu();

    // Switches to the evaluation menu in which the user can input expressions
    // to be sent to the parser.
    void RunEvalMenu();

    // Switches to the graphing menu in which the user can input expressions
    // to be sent to the parser to create graphs of.
    void RunGraphMenu();

    // Displays the current history of the program to the terminal.
    void DisplayHistory();

    // Displays all current user vars and their values.
    void DisplayVars();

    // Sends an expression to the parser
    void Eval(std::string expr) override;

    // Displays what error occured to the terminal
    // Optionally takes a parameter for position of the error
    // initialized to -1 for errors that do not have a positional argument.
    void DisplayError(
                  std::string expr, 
                  flags::EvalErr err,
                  int position=-1) override;

                  
};


#endif
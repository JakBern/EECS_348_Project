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

    // used during savetovar -- if NULL, trigger error in saving var
    // std::unique_ptr<Value> last_expr_;

    flags::InterfaceCode Run() override;

    void Close() override;

    void LoadFromHistory(int expr_num) override;

    void RunHistoryMenu();

    void DisplayHistory();

    void Eval(std::string expr) override;

    void DisplayError(
                  std::string expr, 
                  flags::EvalErr err,
                  int position) override;

                  
};


#endif
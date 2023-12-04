// This is an base class representing a user interface and the window that 
// the application will be running in and should handle all I/O.
//
//
// Graphing interfaces are not yet implemented
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
//
//
// Last update:
//  - 11/30/2023 (Jake): Commented out unused functionality, removed functions
//    AddToVars, AddToHistory, etc (can be done easily in each UI)
//
#ifndef UI_INTERFACE_H_
#define UI_INTERFACE_H_

#include <string>
#include <memory>

#include "util/flags.hpp"
#include "user_context/user_context.hpp"
#include "parser/parser.hpp"

class AppInterface {
  public:
    // Creates and makes the interface visible
    //
    // Returns a code on the process being ended depending upon the condition
    // for ending. These codes are in flags.h, and signify either:
    //  - a clean exit, meaning the program is shutting down
    //  - a switch from the command line to GUI
    //  - a switch from the GUI to the command line
    // 
    // The = 0 denotes that this is a "pure virtual" function and that this is 
    // an abstract class which is never directly instantiated.
    virtual flags::InterfaceCode Run() = 0;

    // Frees all memory used by the interface and closes it
    //
    // Note that this is called when switching from GUI to command line as well
    // and the current history is transfered from one to the other
    // using a copy constructor.
    virtual void Close() = 0;

    AppInterface();
    AppInterface(std::shared_ptr<UserContext> context,
                  std::shared_ptr<Parser> parser);
    virtual ~AppInterface();

  protected:

    
    // Evaluates the current expression by calling the parser and passing
    // the expression by reference along with a reference to the user-defined
    // variables.
    //
    // If the evaluation is successful, the result is displayed and the
    // expression is added to the history.
    // 
    // If the evaluation is not successful, an error message should be displayed
    virtual void Eval(std::string expr) = 0;
    
    // ===========REMOVED UNTIL FUTURE ITERATIONS==========

    // If an expression has an error, this displays the error type, and where
    // it occurs in the evaluated expression.

    // virtual void DisplayError(
    //             std::string expr, 
    //             flags::EvalError err,
    //             int position) = 0;

    // =====================END REMOVED====================

    std::shared_ptr<UserContext> user_context_;
    std::shared_ptr<Parser> parser_;

    std::string user_input_;

};



#endif
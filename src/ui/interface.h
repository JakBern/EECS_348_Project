// This is an base class representing a user interface and the window that 
// the application will be running in and should handle all I/O.
//
//
// Graphing interfaces are not yet implemented
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
// YourName Here [from Blank - Blank]
//
// Last update:
//  - 10/19/2023 (Jake): 
//    Continued filling out file
//
#ifndef UI_INTERFACE_H_
#define UI_INTERFACE_H_

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

#include "util/flags.h"
#include "user_context/user_context.h"

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
    AppInterface(std::shared_ptr<UserContext> context);
    virtual ~AppInterface();

  protected:

    // Adds an expression to the front of the expression history.
    // If there are already the max amount of allowed expressions in the history
    // then the oldest expression is removed.
    virtual void AddToHistory(std::string expr);

    // Loads an expression from the history to be edited by the user.
    // Expressions will be enumerated based on their recency, eg the most recent
    // expression evaluated will be 1, then 2, etc.
    virtual void LoadFromHistory(int expr_num) = 0;

    // Adds a user-defined var to the list of user defined vars.
    //
    // Returns one of several codes depending upon how the process went:
    //  - kSuccess: the variable was successfully added
    //  - kOverwrite: the variable will overwrite another, get user input to
    //                make sure this is okay.
    //  - kFormatError: the variable was formatted wrong and could not be added
    //  - kReservedError: the variable was given a name already given to a
    //                    reserved keyword and could not be added
    //
    virtual flags::UserVarMsg AddToUserVars(
                                    std::string var, 
                                    int val /*Value val*/);

    // Removes the specified string from the user vars.
    //  
    // Returns false if the string does not exist in the user vars,
    // true if successful.
    bool RemoveFromUserVars(std::string var);

    
    // Evaluates the current expression by calling the parser and passing
    // the expression by reference along with a reference to the user-defined
    // variables.
    //
    // If the evaluation is successful, the result is displayed and the
    // expression is added to the history.
    // 
    // If the evaluation is not successful, an error message should be displayed
    virtual void Eval(std::string expr) = 0;

    // If an expression has an error, this displays the error type, and where
    // it occurs in the evaluated expression.
    virtual void DisplayError(
                std::string expr, 
                flags::EvalErr err,
                int position) = 0;

    // std::shared_ptr<Parser> parser_;
    std::shared_ptr<UserContext> user_context_;

    std::string user_input_;

};



#endif
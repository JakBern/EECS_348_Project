// Holds state and shared memory for the current instance of the program.
//
// Exists to be shared between the GUI and Program Logic modules of the program
//
// 
// Things stored in the User Context are:
//  - A limited history of the past evaluated expressions
//  - The max size of the list of history
//  - The value of the last expression evaluated
//  - A list of all reserved keywords
//  - A map of all current user variables to their values
//  - [TODO] A list of all currently opened graphs 
//
// Author(s): 
// Jake Bernard [from (est) 10/20/2023 - Present],
//
// Last update:
//  - 11/21/2023 (Jake): Commented file
//
#ifndef USER_CONTEXT_USER_CONTEXT_H_
#define USER_CONTEXT_USER_CONTEXT_H_

#include <vector>
#include <deque>
#include <string>
// #include <map>

#include "util/flags.hpp"

class UserContext {

  public:

    // Adds the expression given to it as a string to the history.
    // Note that new entries will delete old entries if the max history length 
    // is surpassed.
    void add_history(std::string expr);

    // Returns the amount of entries currently in the history
    std::size_t history_len();

    // Returns the history as an iterable (list) object
    std::deque<std::string>& get_history();

    // Returns a specific history item
    std::string get_history_item(int item_num);

    // ===========REMOVED UNTIL FUTURE ITERATIONS==========
    
    // Returns the stored user variables and values as map object
    // std::map<std::string, int>& get_var_list();

    // Adds a variable and its associated value to the variable storage 
    // Note: returns a flag signalling success or failure.
    // (assume flags::UserVarMsg:: is prepended to all flags)
    // Success flag is:
    //  - kSuccess
    // Failure flags include:
    //  - kVarNeedOverwrite
    //    - The variable will overwrite another, ask the user if they're sure.
    //  - kVarFormatError
    //    - The variable contains illegal characters or is incorrectly
    //      formatted.
    //  - kVarReservedError
    //    - The variable is a reserved keyword and could not be saved.
    // flags::UserVarMsg add_var(std::string var, int val);

    // Removes a variable from internal variable storage based its string.
    // Returns false if the variable doesn't exist.
    // bool remove_var(std::string var);

    // Check if a string exists in the reserved keywords
    // bool in_keywords(std::string var);

    // Check if a variable already exists
    // bool var_exists(std::string var);

    // Overwrites the value of a user_variable
    // void overwrite_var(std::string var, int val);

    // =====================END REMOVED====================

    UserContext() {}
    ~UserContext() {}


  protected:
    // Contains the history of all expressions evaluated during runtime
    // up to a set threshold (max_history_)
    std::deque<std::string> history_;

    // Specifies the maximum number of expressions that can exist in history.
    static const std::size_t max_history_len_ = 8;

    // will later use Value type instead of int
    // std::map<std::string, int> user_vars_;

    // holds last evaluated expression value
    // int last_expression_value_;

    // Checks if the user defined variable adheres to the format standards,
    // ie: only letters or underscores
    // bool var_format_correct(std::string var);

};

#endif
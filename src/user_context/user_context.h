#ifndef USER_CONTEXT_USER_CONTEXT_H_
#define USER_CONTEXT_USER_CONTEXT_H_

#include <vector>
#include <list>
#include <string>
#include <map>
#include <array>
#include <queue>

#include "util/flags.h"

class UserContext {

  public:

    void add_history(std::string expr);

    std::size_t history_len();

    std::list<std::string>& get_history();

    flags::UserVarMsg add_var(std::string var, int val);

    bool remove_var(std::string var);

    bool in_keywords(std::string var);

    bool var_exists(std::string var);


  protected:
    // Contains the history of all expressions evaluated during runtime
    // up to a set threshold (max_history_)
    std::list<std::string> history_;

    // Specifies the maximum number of expressions that can exist in history.
    std::size_t max_history_len_;

    std::array<std::string, 1> reserved_keywords_;
    std::map<std::string, int/*Value*/> reserved_vars_;
    std::map<std::string, int/*Value*/> user_vars_;

};

#endif